#! /usr/local/bin/python3
# coding=utf-8

import threading, time, os
from urllib import request

def cpu_load():
	i = 0
	while True:
		i += 1
		if i % 50000 == 0:
			i = 0
			time.sleep(0.01)


def net_io_load():
	while 1:
		print("start downing...")
		ret = request.urlopen("http://distfiles.macports.org/py-setuptools/setuptools-2.0.tar.gz")
		with open("tempdown", "wb") as f:
			f.write(ret.read())

		print("down successful...")
		if os.path.exists("tempdown"):
			os.remove("tempdown")
			print("del successful...")
			time.sleep(0.5)
	
		


if __name__ == "__main__":
	t_cpu = threading.Thread(target=cpu_load, name="cpu_load_thread")
	t_cpu.start()

	t_net_io = threading.Thread(target=net_io_load, name="cpu_load_thread")
	t_net_io.start()

#t_cpu.join()
#t_net_io.join()


