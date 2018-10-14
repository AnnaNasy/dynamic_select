Transactions:		        2550 hits
Availability:		      100.00 %
Elapsed time:		       14.63 secs
Data transferred:	      364.97 MB
Response time:		        1.15 secs
Transaction rate:	      174.30 trans/sec
Throughput:		       24.95 MB/sec
Concurrency:		      200.14
Successful transactions:        2550
Failed transactions:	           0
Longest transaction:	        6.23
Shortest transaction:	        0.01


Transactions:		        2550 hits
Availability:		      100.00 %
Elapsed time:		       12.56 secs
Data transferred:	      364.97 MB
Response time:		        0.81 secs
Transaction rate:	      203.03 trans/sec
Throughput:		       29.06 MB/sec
Concurrency:		      164.29
Successful transactions:        2550
Failed transactions:	           0
Longest transaction:	        7.22
Shortest transaction:	        0.02

Transactions:		        2550 hits
Availability:		      100.00 %
Elapsed time:		       10.72 secs
Data transferred:	      364.97 MB
Response time:		        0.76 secs
Transaction rate:	      237.87 trans/sec
Throughput:		       34.05 MB/sec
Concurrency:		      181.86
Successful transactions:        2550
Failed transactions:	           0
Longest transaction:	        5.52
Shortest transaction:	        0.01


Transactions:		        2550 hits
Availability:		      100.00 %
Elapsed time:		       17.95 secs
Data transferred:	      364.97 MB
Response time:		        0.92 secs
Transaction rate:	      142.06 trans/sec
Throughput:		       20.33 MB/sec
Concurrency:		      130.66
Successful transactions:        2550
Failed transactions:	           0
Longest transaction:	       15.84
Shortest transaction:	        0.01

100并发量

Transactions:		        1000 hits
Availability:		      100.00 %
Elapsed time:		        4.52 secs
Data transferred:	      143.13 MB
Response time:		        0.33 secs
Transaction rate:	      221.24 trans/sec
Throughput:		       31.67 MB/sec
Concurrency:		       72.72
Successful transactions:        1000
Failed transactions:	           0
Longest transaction:	        3.08
Shortest transaction:	        0.01

Transactions:		        1000 hits
Availability:		      100.00 %
Elapsed time:		        4.15 secs
Data transferred:	      143.13 MB
Response time:		        0.31 secs
Transaction rate:	      240.96 trans/sec
Throughput:		       34.49 MB/sec
Concurrency:		       73.57
Successful transactions:        1000
Failed transactions:	           0
Longest transaction:	        2.02
Shortest transaction:	        0.01

Transactions: siege对服务器的访问次数。如果页面发生了redirect，那么siege会将跳转过的请求算成是另一个transaction

· Availability: socket连接的成功率。算法是，如果页面发生了timeout,4xx,5xx，那么该请求算是失败请求，成功率就等于(所有请求-失败请求) / 总请求数

· Elapsed time: 所有请求耗费的时间

· Data transferred: 所有请求传输的数据量，包括请求的headers和content。所以这个数值可能比server端统计的数值要大一点

· Response time: 平均响应时间

· Transaction rate: Transactions / Elapsed time，事务率

· Throughput: 吞吐量，每秒平均传输的数据量

· Concurrency: 平均并发的请求数

· Successful transactions: 所有status code < 400的transactions数量

· Failed transactions: 所有status code >= 400的transactions数量

· Longest transaction: 最耗时的请求时间

· Shortest transaction: 最短单个请求时间

100并发量 重复1次 动态选择

Transactions:		        1000 hits
Availability:		      100.00 %
Elapsed time:		        3.78 secs
Data transferred:	      143.13 MB
Response time:		        0.27 secs
Transaction rate:	      264.55 trans/sec
Throughput:		       37.86 MB/sec
Concurrency:		       71.69
Successful transactions:        1000
Failed transactions:	           0
Longest transaction:	        2.11
Shortest transaction:	        0.02

Transactions:		        1000 hits
Availability:		      100.00 %
Elapsed time:		        4.70 secs
Data transferred:	      143.13 MB
Response time:		        0.29 secs
Transaction rate:	      212.77 trans/sec
Throughput:		       30.45 MB/sec
Concurrency:		       60.68
Successful transactions:        1000
Failed transactions:	           0
Longest transaction:	        3.08
Shortest transaction:	        0.01


200并发量 重复1次 动态选择

Transactions:		        2000 hits
Availability:		      100.00 %
Elapsed time:		        7.43 secs
Data transferred:	      286.25 MB
Response time:		        0.53 secs
Transaction rate:	      269.18 trans/sec
Throughput:		       38.53 MB/sec
Concurrency:		      142.64
Successful transactions:        2000
Failed transactions:	           0
Longest transaction:	        3.40
Shortest transaction:	        0.01

Transactions:		        2000 hits
Availability:		      100.00 %
Elapsed time:		        9.38 secs
Data transferred:	      286.25 MB
Response time:		        0.58 secs
Transaction rate:	      213.22 trans/sec
Throughput:		       30.52 MB/sec
Concurrency:		      124.16
Successful transactions:        2000
Failed transactions:	           0
Longest transaction:	        3.31
Shortest transaction:	        0.01


300并发量 重复1次 动态选择

Transactions:		        3000 hits
Availability:		      100.00 %
Elapsed time:		       11.10 secs
Data transferred:	      429.38 MB
Response time:		        0.74 secs
Transaction rate:	      270.27 trans/sec
Throughput:		       38.68 MB/sec
Concurrency:		      200.27
Successful transactions:        3000
Failed transactions:	           0
Longest transaction:	        3.42
Shortest transaction:	        0.01

Transactions:		        3000 hits
Availability:		      100.00 %
Elapsed time:		       13.13 secs
Data transferred:	      429.38 MB
Response time:		        0.82 secs
Transaction rate:	      228.48 trans/sec
Throughput:		       32.70 MB/sec
Concurrency:		      186.94
Successful transactions:        3000
Failed transactions:	           0
Longest transaction:	        3.68
Shortest transaction:	        0.02


400并发量 重复1次

Transactions:		        4000 hits
Availability:		      100.00 %
Elapsed time:		       14.35 secs
Data transferred:	      572.51 MB
Response time:		        0.98 secs
Transaction rate:	      278.75 trans/sec
Throughput:		       39.90 MB/sec
Concurrency:		      274.44
Successful transactions:        4000
Failed transactions:	           0
Longest transaction:	        4.23
Shortest transaction:	        0.02

Transactions:		        4000 hits
Availability:		      100.00 %
Elapsed time:		       15.78 secs
Data transferred:	      572.51 MB
Response time:		        1.05 secs
Transaction rate:	      253.49 trans/sec
Throughput:		       36.28 MB/sec
Concurrency:		      266.11
Successful transactions:        4000
Failed transactions:	           0
Longest transaction:	        6.23
Shortest transaction:	        0.01


500并发量

Transactions:		        5000 hits
Availability:		      100.00 %
Elapsed time:		       18.43 secs
Data transferred:	      715.63 MB
Response time:		        0.79 secs
Transaction rate:	      271.30 trans/sec
Throughput:		       38.83 MB/sec
Concurrency:		      213.35
Successful transactions:        5000
Failed transactions:	           0
Longest transaction:	        4.48
Shortest transaction:	        0.01


Transactions:		        5000 hits
Availability:		      100.00 %
Elapsed time:		       19.45 secs
Data transferred:	      715.63 MB
Response time:		        0.96 secs
Transaction rate:	      257.07 trans/sec
Throughput:		       36.79 MB/sec
Concurrency:		      245.88
Successful transactions:        5000
Failed transactions:	           0
Longest transaction:	        7.81
Shortest transaction:	        0.01



600并发量

Transactions:		        6000 hits
Availability:		      100.00 %
Elapsed time:		       23.70 secs
Data transferred:	      858.76 MB
Response time:		        1.07 secs
Transaction rate:	      253.16 trans/sec
Throughput:		       36.23 MB/sec
Concurrency:		      272.13
Successful transactions:        6000
Failed transactions:	           0
Longest transaction:	        8.66
Shortest transaction:	        0.01

Transactions:		        6000 hits
Availability:		      100.00 %
Elapsed time:		       23.35 secs
Data transferred:	      858.76 MB
Response time:		        1.23 secs
Transaction rate:	      256.96 trans/sec
Throughput:		       36.78 MB/sec
Concurrency:		      315.40
Successful transactions:        6000
Failed transactions:	           0
Longest transaction:	        9.60
Shortest transaction:	        0.01


700并发量

Transactions:		        7000 hits
Availability:		      100.00 %
Elapsed time:		       24.91 secs
Data transferred:	     1001.89 MB
Response time:		        1.17 secs
Transaction rate:	      281.01 trans/sec
Throughput:		       40.22 MB/sec
Concurrency:		      327.77
Successful transactions:        7000
Failed transactions:	           0
Longest transaction:	       15.06
Shortest transaction:	        0.01

Transactions:		        7000 hits
Availability:		      100.00 %
Elapsed time:		       27.37 secs
Data transferred:	     1001.89 MB
Response time:		        1.27 secs
Transaction rate:	      255.75 trans/sec
Throughput:		       36.61 MB/sec
Concurrency:		      325.61
Successful transactions:        7000
Failed transactions:	           0
Longest transaction:	       11.23
Shortest transaction:	        0.01



800 并发量

Transactions:		        8000 hits
Availability:		      100.00 %
Elapsed time:		       28.99 secs
Data transferred:	     1145.01 MB
Response time:		        1.57 secs
Transaction rate:	      275.96 trans/sec
Throughput:		       39.50 MB/sec
Concurrency:		      432.43
Successful transactions:        8000
Failed transactions:	           0
Longest transaction:	        7.70
Shortest transaction:	        0.01

Transactions:		        8000 hits
Availability:		      100.00 %
Elapsed time:		       33.14 secs
Data transferred:	     1145.01 MB
Response time:		        1.61 secs
Transaction rate:	      241.40 trans/sec
Throughput:		       34.55 MB/sec
Concurrency:		      388.86
Successful transactions:        8000
Failed transactions:	           0
Longest transaction:	       14.40
Shortest transaction:	        0.01


900并发量

Transactions:		        9000 hits
Availability:		      100.00 %
Elapsed time:		       30.73 secs
Data transferred:	     1288.14 MB
Response time:		        1.54 secs
Transaction rate:	      292.87 trans/sec
Throughput:		       41.92 MB/sec
Concurrency:		      449.94
Successful transactions:        9000
Failed transactions:	           0
Longest transaction:	        7.96
Shortest transaction:	        0.01

Transactions:		        9000 hits
Availability:		      100.00 %
Elapsed time:		       34.20 secs
Data transferred:	     1288.14 MB
Response time:		        1.88 secs
Transaction rate:	      263.16 trans/sec
Throughput:		       37.66 MB/sec
Concurrency:		      494.56
Successful transactions:        9000
Failed transactions:	           0
Longest transaction:	       15.94
Shortest transaction:	        0.01


1000并发量

Transactions:		        9364 hits
Availability:		       93.64 %
Elapsed time:		       35.84 secs
Data transferred:	     1340.56 MB
Response time:		        2.16 secs
Transaction rate:	      261.27 trans/sec
Throughput:		       37.40 MB/sec
Concurrency:		      564.92
Successful transactions:        9364
Failed transactions:	         636
Longest transaction:	        8.82
Shortest transaction:	        0.02

Transactions:		        9488 hits
Availability:		       94.88 %
Elapsed time:		       36.48 secs
Data transferred:	     1358.25 MB
Response time:		        2.45 secs
Transaction rate:	      260.09 trans/sec
Throughput:		       37.23 MB/sec
Concurrency:		      636.21
Successful transactions:        9488
Failed transactions:	         512
Longest transaction:	       30.74
Shortest transaction:	        0.01








