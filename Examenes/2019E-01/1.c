
Parte A
------------------------------------------------------
//VM1
$ sudo -i
$ ip a add FD00:1:1:A::1/64 dev eth0
$ ip link set eth0 up

//VM2
$ sudo -i
$ ip a add FD00:1:1:B::1/64 dev eth0
$ ip link set eth0 up

//VM3
$ sudo -i
$ ip a add FD00:1:1:A::2/64 dev eth0
$ ip a add FD00:1:1:B::2/64 dev eth1
$ ip link set eth0 up
$ ip link set eth1 up
$ sysctl = 1

Parte B
------------------------------------------------------
//VM3 
$ sudo nano /etc/quagga/zebra.conf

interface eth0
	no ipv6 nd supress-ra
	ipv6 nd prefix FD00:1:1:A::/64
	
$ service zebra start

Parte C
------------------------------------------------------

//VM1
$ ip -6 route add default via FD00:1:1:A::2

//VM2
$ ip -6 route add default via FD00:1:1:B::2























