#! /usr/local/bin/python3
# coding=utf8

from ServerInfo import server_infos
from config import *
import time, json

is_start = False #是否开始过
is_stop = False  #是否是暂停，代表之前开始过，后来停止了
cur_req_nums = "0"


def get_info():
	global is_start, is_stop
	info_dic = {
		#"model_name"	:	server_infos.get_cpu_info(category="model name"),
		"cpu_usage"		:	server_infos.get_cpu_usage_info(), 
		"mem_usage"		:	server_infos.get_mem_usage_info(),
		"net_usage"		:	server_infos.get_net_usage_info(), 
		"io_usage"		:	server_infos.get_io_usage_info(), #need sleep(1)
		"request_time"	:	server_infos.get_request_time(),
		"time_stamp"	:	time.time(),
	}
	if not is_start and info_dic["request_time"]: is_start = True
	elif is_start and not info_dic["request_time"]: 
		is_start = False
		is_stop = True

	return info_dic

def send_info(info_dic):
	write_debug(info_dic)
	info_dic = json.dumps(info_dic)
	MEMCACHE_CONN.set(LOCAL_FLAG, info_dic)


def write_debug(info_dic):
	msg = '''[%s] => cpu:%7.3f\tmem:%7.3f\tnet:%7.3f\tio:%5.2f\trequest_time:%.3f\ttime_stamp:%.3f\treq_nums:%s''' % (
			LOCAL_IP[-3:], info_dic["cpu_usage"], info_dic["mem_usage"], info_dic["net_usage"], info_dic["io_usage"], info_dic["request_time"] or 0.000, info_dic["time_stamp"], cur_req_nums
			)
	print(msg)



while 1:
	info = get_info()
	send_info(info)
	
	if is_stop: 
		cur_req_nums = server_infos.get_cur_req_numbers()
		#server_infos.clear_access_log()
		is_stop = False
	
	time.sleep(0.2)

