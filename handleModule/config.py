# conding=utf-8
import socket, hashlib
import memcache

upstream_server = (
	"192.168.128.131",
	"192.168.128.132",
	"192.168.128.133",
	)

def get_host_ip():
	try:
		s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		s.connect(('8.8.8.8', 80))
		ip = s.getsockname()[0]
		#print(ip)
	finally:
		s.close()
	#print(ip)
	return ip

def genearteMD5(str):
    # 创建md5对象
    h_md5 = hashlib.md5()
    h_md5.update(str.encode(encoding='utf-8'))
    return h_md5.hexdigest()

def generation_server():
	flags = {}
	for ser_ip in upstream_server:
		flags[genearteMD5(ser_ip)] = ser_ip
	return flags

def generation_infos():
	infos = {}
	for ser_ip in upstream_server:
		sererflag = genearteMD5(ser_ip)
		infos[sererflag] = {}
		infos[sererflag]["pre_time"] = None
		infos[sererflag]["weight"] = None
		infos[sererflag]["data"] = None
	return infos


SERVER_IP_PORT			=	"192.168.128.128:10240"
#LOCAL_IP				=	get_host_ip()
#LOCAL_FLAG				=	genearteMD5(LOCAL_IP)
UPSTREAM_SERVER_FLAGS	=	generation_server()
INFOS					=	generation_infos()
BEST_LOAD_IP_KEY		=	"best_server_ip"


MEMCACHE_CONN = memcache.Client([SERVER_IP_PORT], debug=True)

