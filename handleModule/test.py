import memcache
import time

#conn = memcache.Client(["192.168.128.128:10240"], debug=True)

#print(conn)

Transactions:		        2000 hits
Availability:		      100.00 %
Elapsed time:		       29.67 secs
Data transferred:	       15.17 MB
Response time:		        2.64 secs
Transaction rate:	       67.41 trans/sec
Throughput:		        0.51 MB/sec
Concurrency:		      177.64
Successful transactions:        2000
Failed transactions:	           0
Longest transaction:	       18.61
Shortest transaction:	        0.03

Transactions:		        1996 hits
Availability:		       99.80 %
Elapsed time:		       57.74 secs
Data transferred:	       15.14 MB
Response time:		        7.15 secs
Transaction rate:	       34.57 trans/sec
Throughput:		        0.26 MB/sec
Concurrency:		      247.22
Successful transactions:        1996
Failed transactions:	           4
Longest transaction:	       44.03
Shortest transaction:	        0.03

record = {
	"192.168.128.131":1,
	"192.168.128.132":2,
	"192.168.128.133":3,
}

def print_debug():
	print(
		'''
	----------------------------------\n
		%s 选择 %d 次\n
		%s 选择 %d 次\n
		%s 选择 %d 次\n
	----------------------------------

		''' % 
			(
			"192.168.128.131", record["192.168.128.131"], 
			"192.168.128.132", record["192.168.128.132"], 
			"192.168.128.133", record["192.168.128.133"], 
			)
		)

#print_debug()
#

with open("aaaaa", 'a') as f:
	f.write("aaaa")