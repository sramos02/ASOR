
Parte A
------------------------------------------------------
//VM1
$ sudo -i
$ ip a add 192.168.0.1/24 dev eth0
$ ip link set eth0 up

//VM2
$sudo -i
$ ip a add 192.168.0.2/24 dev eth0
$ ip link set eth0 up

Parte B
------------------------------------------------------
$ nano /etc/named.conf

zone "examen.es"{
	type master;
	file "db.examen.es";
};

$ nano /var/named/db.examen.es

$TTL 3h
examen.es.	IN	SOA	ns.examen.es.	contact.examen.es.(
				2312211027	;serial
				1h			;refresh
				15M			;update try
				1W12h		;expire
				2h			;nx ttl
				)
				
				IN		NS		ns
				IN		MX	1	mail.examen.es.
				
www				IN		A	 	192.168.0.200
mail			IN		A		192.168.0.250
servidor		IN		CNAME	mail
				
$ named-checkconf
$ named-checkzone
$ service named start

Parte C
------------------------------------------------------	

$ nano /etc/resolv.conf

search ns.examen.es
nameserver 192.168.0.1


$ dig examen.es









				
				
				
				
				
				
