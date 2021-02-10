#!/bin/bash


basepath=$(pwd)

function route_configure
{
	echo ">>>>>>>>>>>>>>>>>>start>>>>>>>>>>>>>>>>>>>>>>>>>>>>"

	echo "ip route del default via 192.168.50.1 dev eno1"
	sudo ip route del default via 192.168.50.1 dev eno1

	echo "ip route del 192.168.50.0/24 via 0.0.0.0 dev eno1"
	sudo ip route del 192.168.50.0/24 via 0.0.0.0 dev eno1

	echo "ifconfig vlan4 172.20.30.2"
	sudo ifconfig vlan4 172.20.30.2

	echo "ifconfig vlan4 hw ether aa:bb:cc:dd:ee:01"
	sudo ifconfig vlan4 hw ether aa:bb:cc:dd:ee:01

	echo "ifconfig vlan4 -arp"
	sudo ifconfig vlan4 -arp

	echo "arp -s 172.20.30.244 aa:bb:cc:dd:ee:f3 -i vlan4"
	sudo arp -s 172.20.30.4 aa:bb:cc:dd:ee:03 -i vlan4

	echo "ip route add default via 172.20.30.244 dev vlan4"
	sudo ip route add default via 172.20.30.4 dev vlan4

	echo "ip route add 172.20.30.0/24 via 0.0.0.0 dev vlan4"
	sudo ip route add 172.20.30.0/24 via 0.0.0.0 dev vlan4
	
	echo "ip route del 172.20.0.0/16 via 0.0.0.0 dev vlan4"
	sudo ip route del 172.20.0.0/16 via 0.0.0.0 dev vlan4
	
	echo ">>>>>>>>>>>>>>>>>>end>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
}

