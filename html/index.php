<?php
	/**1. 读取文件 2000整数，放到数组里 一个整数4B * 2000 = 8K 模拟每个请求消耗8K内存
	 * 2. 求和，模拟CPU计算负载。
	 * 3. 返回结果 模拟网络和磁盘消耗。
	 * 4. 关闭文件
	 */
	$ints_str = file_get_contents('randint.data');
	$myfile = fopen("test_io_perform.data", "w") or die("Unable to open file!");
	fwrite($myfile, $ints_str);
	fclose($myfile);
	$ints_arr = explode(' ', $ints_str);
	print_r($ints_arr);
	echo "</br>";

	$i = 0;
	while (1) {
		$i++;
		if ($i % 500000 == 0) {
			return 0;
		}
	}

	
	