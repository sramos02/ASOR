//VM1
$ sudo -i
$ ip a add 192.168.0.1/24 dev eth0
$ ip link set eth0 up
$ ip route add default via 192.168.0.2

//VM2
$ sudo -i
$ ip a add 192.168.0.2/24 dev eth1
$ ip a add 10.0.0.2/24 dev eth1
$ ip link set eth0 up
$ ip link set eth1 up
$ nano /etc/quagga/ripd.conf
$ service ripd start
$ service zebra start
$ sysctl = 1

//VM3
$ sudo -i
$ ip a add 10.0.0.3/24 dev eth1
$ ip a add 172.16.0.2/24 dev eth0
$ ip link set eth0 up
$ ip link set eth1 up
$ nano /etc/quagga/ripd.conf
$ service ripd start
$ service zebra start

