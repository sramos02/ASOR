
Parte A
---------------------------------------------------
//VM1
$ sudo -i
$ ip a add 192.168.0.1/24 dev eth0
$ ip link set eth0 up
$ ip route add default via 192.168.0.2

//VM2
$ sudo -i
$ ip a add 172.16.0.1/16 dev eth0
$ ip link set eth0 up
$ ip route add default via 172.16.0.2

//VM3
$ sudo -i
$ ip a add 192.168.0.2/24 dev eth0
$ ip a add 172.16.0.2/16 dev eth0
$ ip link set eth0 up
$ ip link set eth1 up
$ sysctl = 1


Parte B
---------------------------------------------------
//VM1
$ ping 172.16.0.1


Parte C
---------------------------------------------------
//VM3
$ iptables -t NAT -A POSTROUTING -o eth0 -j MASQUERADE



