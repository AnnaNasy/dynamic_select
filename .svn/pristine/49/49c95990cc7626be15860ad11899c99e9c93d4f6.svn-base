#! /bin/bash

server_arr=(
		"192.168.128.132"
		"192.168.128.133"
)

for ser in ${server_arr[@]};
do
		sudo rsync -vlre "ssh -p22" /usr/ root@${ser}:/usr
		sudo rsync -vlre "ssh -p22" /etc/alternatives/ root@${ser}:/etc/alternatives

done
