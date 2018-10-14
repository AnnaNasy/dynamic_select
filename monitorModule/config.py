# conding=utf-8
import socket, hashlib
import memcache

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

SERVER_IP_PORT			=	"192.168.128.128:10240"
LOCAL_IP				=	get_host_ip()
LOCAL_FLAG				=	genearteMD5(LOCAL_IP)

MEMCACHE_CONN = memcache.Client([SERVER_IP_PORT], debug=True)
KEY_CPUINFO = "%s_cpu" % LOCAL_FLAG
KEY_MEMINFO = "%s_mem" % LOCAL_FLAG
KEY_NETINFO = "%s_net" % LOCAL_FLAG


