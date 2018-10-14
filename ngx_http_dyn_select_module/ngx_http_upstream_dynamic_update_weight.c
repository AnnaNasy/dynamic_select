#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <stdlib.h>
#include "query_memcache_ip.c"


typedef struct {
    /* the round robin data must be first */
    ngx_http_upstream_rr_peer_data_t   rrp;

    ngx_event_get_peer_pt              get_rr_peer;
} ngx_http_upstream_dyn_select_peer_data_t;


static char* ngx_http_upstream_dyn_select(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
static ngx_int_t ngx_http_upstream_init_dyn_select_peer(ngx_http_request_t *r,
    ngx_http_upstream_srv_conf_t *us);
static ngx_int_t ngx_http_upstream_get_dyn_select_peer(ngx_peer_connection_t *pc, void *data);
static ngx_http_upstream_rr_peer_t* update_weight_peer(ngx_http_upstream_dyn_select_peer_data_t *dynp, ngx_peer_connection_t *pc);
void initStaticWeight(ngx_http_upstream_srv_conf_t *us);


/*定义模块的配置指令*/
static ngx_command_t ngx_http_upstream_dyn_select_module_commands[] = {
	{
		ngx_string("dyn_select"),
		NGX_HTTP_UPS_CONF|NGX_CONF_NOARGS,
		ngx_http_upstream_dyn_select,
		0, /*NGX_HTTP_MAIN_CONF_OFFSET*/
		0,
		NULL
	},
	ngx_null_command
};


static ngx_http_module_t  ngx_http_upstream_dyn_select_module_ctx = {
    NULL,                                  /* preconfiguration */
    NULL,                                  /* postconfiguration */

    NULL,                                  /* create main configuration */
    NULL,                                  /* init main configuration */

    NULL,                                  /* create server configuration */
    NULL,                                  /* merge server configuration */

    NULL,                                  /* create location configuration */
    NULL                                   /* merge location configuration */
};

/*模块的定义*/
ngx_module_t  ngx_http_upstream_dyn_select_module = {
    NGX_MODULE_V1,
    &ngx_http_upstream_dyn_select_module_ctx,				/* module context */
    ngx_http_upstream_dyn_select_module_commands,    		/* module directives */
    NGX_HTTP_MODULE,                       					/* module type */
    NULL,                                  					/* init master */
    NULL,                                  					/* init module */
    NULL,                                  					/* init process */
    NULL,                                  					/* init thread */
    NULL,                                  					/* exit thread */
    NULL,                                  					/* exit process */
    NULL,                                  					/* exit master */
    NGX_MODULE_V1_PADDING
};


/*初始化配置*/
static ngx_int_t
ngx_http_upstream_init_dyn_select(ngx_conf_t *cf, ngx_http_upstream_srv_conf_t *us)
{
    if (ngx_http_upstream_init_round_robin(cf, us) != NGX_OK) {
        return NGX_ERROR;
    }

    us->peer.init = ngx_http_upstream_init_dyn_select_peer;
    initStaticWeight(us); //初始化权重
    
    return NGX_OK;
}


/*初始化静态权重*/
void initStaticWeight(ngx_http_upstream_srv_conf_t *us) {
    ngx_http_upstream_rr_peers_t  *peers;
    ngx_uint_t i;
    int ret;
    peers = us->peer.data;
    initWeight_t staticWeight; 
    ret = getWeight(&staticWeight);
    if (ret == 0) {
        return;
    }
    for (i = 0; i < peers->number; i++) {
        peers->peer[i].weight = (ngx_uint_t)(*((int32_t*)&staticWeight+i));
        peers->peer[i].effective_weight = peers->peer[i].weight;
        peers->peer[i].current_weight = 0;
    }

}

static ngx_int_t
ngx_http_upstream_init_dyn_select_peer(ngx_http_request_t *r, ngx_http_upstream_srv_conf_t *us)
{
    ngx_http_upstream_dyn_select_peer_data_t  *dynp;

    dynp = ngx_palloc(r->pool, sizeof(ngx_http_upstream_dyn_select_peer_data_t));
    if (dynp == NULL) {
        return NGX_ERROR;
    }

    r->upstream->peer.data = &dynp->rrp;

    if (ngx_http_upstream_init_round_robin_peer(r, us) != NGX_OK) {
        return NGX_ERROR;
    }

    r->upstream->peer.get = ngx_http_upstream_get_dyn_select_peer;

    dynp->get_rr_peer = ngx_http_upstream_get_round_robin_peer;

    return NGX_OK;
}


static ngx_int_t
ngx_http_upstream_get_dyn_select_peer(ngx_peer_connection_t *pc, void *data) {

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, pc->log, 0, "ngx_http_upstream_get_dyn_select_peer");

    ngx_http_upstream_dyn_select_peer_data_t  *dynp = data;
    ngx_http_upstream_rr_peer_t *selected_peer = NULL;
     
    selected_peer = update_weight_peer(dynp, pc); //获得最好的服务器
    if (selected_peer == NULL) {
        return dynp->get_rr_peer(pc, &dynp->rrp); /*退回到默认轮询*/
    }

    pc->sockaddr = selected_peer->sockaddr;
    pc->socklen = selected_peer->socklen;
    pc->name = &selected_peer->name;
    pc->cached = 0;
    pc->connection = NULL;

    return NGX_OK;
}

static ngx_http_upstream_rr_peer_t *
update_weight_peer(ngx_http_upstream_dyn_select_peer_data_t *dynp, ngx_peer_connection_t *pc) {

    ngx_http_upstream_rr_peer_t  *peer, *selected_peer;
    ngx_http_upstream_rr_peers_t *peers;
    time_t now;
    ngx_int_t total;

    total = 0;
    selected_peer = NULL;
    now = ngx_time();
    peers = dynp->rrp.peers;

    ngx_uint_t i;

    initWeight_t staticWeight;
    int ret;
    ret = getWeight(&staticWeight);
    if (ret == 0) {
        goto RR;
    }
    for (i = 0; i < peers->number; i++) {
        peers->peer[i].effective_weight = (ngx_uint_t)(*((int32_t*)&staticWeight+i));
    }

RR:
    for (i = 0; i < peers->number; i++) {

        peer = &peers->peer[i];

        peer->current_weight += peer->effective_weight;
        total += peer->effective_weight;

        if (peer->effective_weight < peer->weight) {
            peer->effective_weight++;
        }

        if (selected_peer == NULL || peer->current_weight > selected_peer->current_weight) {
            selected_peer = peer;
        }
    }

    if (selected_peer == NULL) {
        return NULL;
    }

    selected_peer->current_weight -= total;
    selected_peer->checked = now;

    
    for (i = 0; i < peers->number; i++) {
        peer = &peers->peer[i];
        ngx_log_debug2(NGX_LOG_DEBUG_HTTP, pc->log, 0, "name: %V weight:%d", &peer->name, peer->effective_weight);
    }
    
    
    return selected_peer;
}



static char *
ngx_http_upstream_dyn_select(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_upstream_srv_conf_t  *uscf;

    uscf = ngx_http_conf_get_module_srv_conf(cf, ngx_http_upstream_module);

    uscf->peer.init_upstream = ngx_http_upstream_init_dyn_select;

    uscf->flags = NGX_HTTP_UPSTREAM_CREATE
                  |NGX_HTTP_UPSTREAM_WEIGHT
                  |NGX_HTTP_UPSTREAM_MAX_FAILS
                  |NGX_HTTP_UPSTREAM_FAIL_TIMEOUT
                  |NGX_HTTP_UPSTREAM_DOWN;

    return NGX_CONF_OK;
}