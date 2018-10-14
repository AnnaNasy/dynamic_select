import subprocess

obj = subprocess.run("ping taobao.com -t")

while 1:
	cmd_out = obj.stdout.read()
	print(cmd_out)

