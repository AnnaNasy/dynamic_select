#include <stdio.h>
#include <stdlib.h>  
#include <time.h>  
#include <unistd.h>
#include <string.h>
#include <libmemcached/memcached.h>
#include "cJSON.h"


#define IP_LEN 16
static char best_ip[IP_LEN];
static memcached_st *memc = NULL;  
static memcached_return_t rc;  
static memcached_server_st *server;  

static time_t expiration = 0;  
static uint32_t flags = 0; 


typedef struct initWeight {
    int32_t ser1Weight;
    int32_t ser2Weight;
    int32_t ser3Weight;
}initWeight_t;

static const char *init_key = "weight"; // init weight
static const size_t init_keylen = 7;
static size_t init_valuelen = 100;

static void freeMemc() {
    memcached_free(memc);
    memc = NULL;
}

static int init() {
    if (memc != NULL) {
        //printf("memc != NULL\n");
        return 0;
    }
    //printf("memc == NULL\n");
    memc = memcached_create(NULL);  /*失败返回NULL*/
    if (memc == NULL) {
        //printf("memcached_create error");
        return -1;
    }
    server = memcached_server_list_append(NULL, "192.168.128.128", 10240, &rc);
    if (MEMCACHED_SUCCESS != rc) {
        //printf("memcached_server_list_append error\n");
        freeMemc();
        return -2;
    }

    rc = memcached_server_push(memc, server);
    if (MEMCACHED_SUCCESS != rc) {
        //printf("memcached_server_push error\n");
        freeMemc();
        return -3;
    }
    memcached_server_list_free(server);
    return 0;
}


static int getWeight(initWeight_t *staticWeight) {
    int ret = init();
    if ( ret != 0 ) {
        return 0;
    }

    char *result = memcached_get(memc, init_key, init_keylen, &init_valuelen, &flags, &rc);  
    if(MEMCACHED_SUCCESS == rc) {  
        //printf("Get value:%s successfully\n", result);

        cJSON *root, *item;
        root = cJSON_Parse(result); // parse json string

        item = cJSON_GetObjectItem(root,"ser1Weight");
        staticWeight->ser1Weight = (int32_t)item->valueint;

        item = cJSON_GetObjectItem(root,"ser2Weight");
        staticWeight->ser2Weight = (int32_t)item->valueint;

        item = cJSON_GetObjectItem(root,"ser3Weight");
        staticWeight->ser3Weight = (int32_t)item->valueint;

        free(result);
        cJSON_Delete(root);
        return 1;
    } else {
        //printf("查询结果失败\n");
        return 0;
    }   

}

