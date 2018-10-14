#! /usr/local/bin/python3
# -*- coding:utf-8 -*-

import time, json, os
from config import *

run_recore = { #第一项代表读取未变次数，第二项代表被选次数, 第三项代表是否已经被强制减少权重
	"192.168.128.131" : [0, 0, 0],
	"192.168.128.132" : [0, 0, 0],
	"192.168.128.133" : [0, 0, 0],
}
w = {"cpu":0.375, "mem":0.375, "io":0.125, "net":0.125} #各项系数权重
t_cpu = 0.00 #全部服务器的cpu性能总和
t_mem = 0.00
t_io = 0.00
t_net = 0.00
is_start = False
is_balance = True
is_init_weight = False #是否已经初始化权重
cur_need_modify_server = None #当前需要修改的服务器
init_weight_value = {}

def write_debug():
	print("当前时间请方差值为%.3f 是否负载均衡：%s" % (server_is_balance(), is_balance))
	for ip in upstream_server:
		info = INFOS[genearteMD5(ip)]
		if run_recore[ip][2] == 1:
			os.system("echo %s >> handle.log" % ip)
		
		msg = '''[%s] => cpu:%7.3f\tmem:%7.3f\tnet:%7.3f\tio:%5.2f\trequest_time:%.3f\tweight:%12.3f\t读未变:%d''' % (
			ip[-3:], info["data"]["cpu_usage"], info["data"]["mem_usage"], info["data"]["net_usage"], info["data"]["io_usage"], info["data"]["request_time"] or 0.000, info["weight"], run_recore[ip][0]
			)

		print(msg)
	print("\n")


def server_is_balance():
	'''
		计算每台服务器请求时间的方差，用以判断是否均衡
	'''
	global is_balance
	fuwei = False #是否有服务器在复位中，即在已经均衡的情况下慢慢恢复到初始权重
	#先设置为第一台服务器
	server_flag = genearteMD5(upstream_server[0])
	server_time = INFOS[server_flag]["data"]["request_time"] or 0.000
	max_request_time_server = [server_flag, server_time] 

	time_list = [] #记录有多少台server返回了请求时间
	for server_flag in UPSTREAM_SERVER_FLAGS:
		info = INFOS[server_flag]
		cur_time = info["data"]["request_time"] or 0.000
		time_list.append(cur_time)
		if cur_time > max_request_time_server[1]:
			max_request_time_server = [server_flag, cur_time]

	time_avg = sum(time_list) / len(time_list)
	time_var = 0.00
	for t in time_list:
		time_var += (t-time_avg)**2
	time_var = time_var / len(time_list)
	INFOS["time_var"] = time_var
	INFOS["m_server"] = max_request_time_server[0]
	if time_var > 0.1: #大于临界值，则不平衡
		is_balance = False
		return time_var
	else:
		for server_flag in UPSTREAM_SERVER_FLAGS:
			info = INFOS[server_flag]
			if info["weight"] < init_weight_value[server_flag]:
				fuwei = True
				info["weight"] += 5
		if fuwei: calc_dyn_weight()
		
		is_balance = True
		return time_var


'''
	首次启动时，根据后端服务器的负载情况进行初始化权重
'''
def init_weight():
	global w, t_cpu, t_mem, t_io, t_net, init_weight_value
	weight_dic = {}
	for server_flag in UPSTREAM_SERVER_FLAGS:
		info = INFOS[server_flag]
		t_cpu += (100-info["data"]["cpu_usage"])
		t_io += (100-info["data"]["io_usage"])
		t_mem += (100-info["data"]["mem_usage"])
		t_net += (100-info["data"]["net_usage"])
	for server_flag in UPSTREAM_SERVER_FLAGS:
		info = INFOS[server_flag]
		real_ip = UPSTREAM_SERVER_FLAGS[server_flag]
		c_cpu = (100-info["data"]["cpu_usage"])
		c_io = (100-info["data"]["io_usage"])
		c_mem = (100-info["data"]["mem_usage"])
		c_net = (100-info["data"]["net_usage"])
		info["weight"] = int(1000 * (w["cpu"]*c_cpu/t_cpu + w["io"]*c_io/t_io + w["mem"]*c_mem/t_mem + w["net"]*c_net/t_net))
		item = "ser%sWeight" % real_ip[-1]
		weight_dic[item] = info["weight"]

	for server_flag in UPSTREAM_SERVER_FLAGS:
		info = INFOS[server_flag]
		read_ip = UPSTREAM_SERVER_FLAGS[server_flag]
		init_weight_value[server_flag] = info["weight"]
		print("%s 的初始权重为 %d" % (read_ip, info["weight"]))

	MEMCACHE_CONN.set("weight", json.dumps(weight_dic))


def calc_dyn_weight():
	'''
		每次修改权重不用重新计算，只是在原有权重上做调整。 
		调整方法为负载最大服务器对应权重减去方差。
	'''
	global run_recore
	need_reset = 0
	weight_dic = {}
	'''
	for server_flag in UPSTREAM_SERVER_FLAGS:
		info = INFOS[server_flag]
		real_ip = UPSTREAM_SERVER_FLAGS[server_flag]
		c_cpu = (100-info["data"]["cpu_usage"])
		c_io = (100-info["data"]["io_usage"])
		c_mem = (100-info["data"]["mem_usage"])
		c_net = (100-info["data"]["net_usage"])
		info["weight"] = int(1000 * (w["cpu"]*c_cpu/t_cpu + w["io"]*c_io/t_io + w["mem"]*c_mem/t_mem + w["net"]*c_net/t_net))
		item = "ser%sWeight" % real_ip[-1]
		weight_dic[item] = info["weight"]	
	'''
	m_server = INFOS["m_server"]
	time_var = INFOS["time_var"]
	INFOS[m_server]["weight"] -= time_var**2
	if INFOS[m_server]["weight"] < 0:
		INFOS[m_server]["weight"] = 1


	'''
	for server_flag in UPSTREAM_SERVER_FLAGS:
		info = INFOS[server_flag]
		real_ip = UPSTREAM_SERVER_FLAGS[server_flag]
		cpu = info["data"]["cpu_usage"]
		mem = info["data"]["mem_usage"]
		item = "ser%sWeight" % real_ip[-1]
			
		
		if run_recore[real_ip][2] == 0: #如果未被强制修改权重
			if cpu >= 99 or mem >= 99:
				info["weight"] -= 100;
				weight_dic[item] = info["weight"]
				run_recore[real_ip][2] = 1 #标记该台服务器已经被强制减少权重

	
	for server_flag in UPSTREAM_SERVER_FLAGS:
		info = INFOS[server_flag]
		real_ip = UPSTREAM_SERVER_FLAGS[server_flag]
		need_reset += run_recore[real_ip][2]
		

	if need_reset == 3: #三台服务器都已经被强制修改过权重
		print("need_reset == 3")
		exit()
		for server_flag in UPSTREAM_SERVER_FLAGS:
			info = INFOS[server_flag]
			real_ip = UPSTREAM_SERVER_FLAGS[server_flag]
			item = "ser%sWeight" % real_ip[-1]
			info["weight"] += 100
			weight_dic[item] = info["weight"]
			run_recore[real_ip][2] = 0
	'''
	for server_flag in UPSTREAM_SERVER_FLAGS:
		info = INFOS[server_flag]
		real_ip = UPSTREAM_SERVER_FLAGS[server_flag]
		item = "ser%sWeight" % real_ip[-1]
		weight_dic[item] = info["weight"]


	MEMCACHE_CONN.set("weight", json.dumps(weight_dic))

def handle_infos():
	global run_recore, is_start, is_init_weight
	is_start = False
	# 0. 循环获取上游服务器的各项数据
	for server_flag in UPSTREAM_SERVER_FLAGS:
		real_ip = UPSTREAM_SERVER_FLAGS[server_flag]
		data = MEMCACHE_CONN.get(server_flag)
		info = INFOS[server_flag]
		if data: #非阻塞，如果没有get到立即返回None
			info["data"] = json.loads(data)
			if info["data"]["request_time"]: is_start = True
			if info["data"]["time_stamp"] == info["pre_time"]: run_recore[real_ip][0] += 1
			else:
				info["pre_time"] = info["data"]["time_stamp"]
		else:
			print("%s 监控模块未启动, 程序退出" % real_ip)
			exit()
	
	# 1. 如果没有初始化权重, 说明是首次启动，进行初始化权重
	if not is_init_weight: #如果请求没有开始且没有初始化权重
		is_init_weight = True #只需要初始化权重一次
		init_weight()
		return
	write_debug()

	if not is_start: return
	# 2. 计算响应时间方差，判断是否均衡
	#server_is_balance() 

	# 3. 如果失衡, 则调整, 未失衡, 则结束 
	if not is_balance:
		#pass
		calc_dyn_weight()
	





if __name__ == "__main__":
	while 1:
		handle_infos()
		time.sleep(0.5)


			
