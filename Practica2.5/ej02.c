#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <time.h>

#include <string.h>


int main(int argc, char* argv[]){
	if(argc != 3){
		perror("Invalid arguments\n");
		return -1;
	}

	//argv[1]: Direccion,   argv[2]: Puerto			
	//192.168.0.100         80					

	struct addrinfo hints, *result;	
	struct sockaddr *addr;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
	hints.ai_protocol = 0;          /* Any protocol */

	if(getaddrinfo(argv[1], argv[2], &hints, &result) != 0){
		perror("Getaddrinfo error\n");
		return -1;
	}

	int udp = socket(result->ai_family, result->ai_socktype, result->ai_protocol);	
	bind(udp, result->ai_addr, result->ai_addrlen);
	freeaddrinfo(result);

	//Comandos: t(time), d(date), q(quit)

	struct sockaddr_storage client_addr;
 	socklen_t client_addrlen = sizeof(client_addr);
	char buf[2], host[NI_MAXHOST], port[NI_MAXSERV];

	while(1){
		const time_t t = time(0);
		struct tm *act = localtime(&t);

		recvfrom(udp, buf, 2, 0, (struct sockaddr *) &client_addr, &client_addrlen);

		getnameinfo((struct sockaddr *) &client_addr, client_addrlen, host, NI_MAXHOST, port, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);

		printf("Recibido mensaje %c de %s:%s\n", buf[0], host, port);

		char s[50];

		switch(buf[0]){
			case 't':;
				size_t b = strftime(s, 50, "%I:%M:%S %p\n", act);	
				printf("%s\n",s);
       			sendto(udp, s, b, 0, (struct sockaddr *) &client_addr, client_addrlen);

			break;
			case 'd':;
 	   	 	 	size_t b2 = strftime(s, 50, "%d-%m-%Y\n", act);
				printf("%s\n",s);
       			sendto(udp, s, b, 0, (struct sockaddr *) &client_addr, client_addrlen);

			break;
			case 'q':;
				char msg[17] = "Fin de conexión\n";
       			sendto(udp, msg, 17, 0, (struct sockaddr *) &client_addr, client_addrlen);
				return 0;
			break;

			default:;
				char msg2[31] = "No se ha reconocido el comando\n";
				printf("%s\n", msg2);
       			sendto(udp, msg2, 31, 0, (struct sockaddr *) &client_addr, client_addrlen);
			break;
		}
	}	
	return 0;
}
