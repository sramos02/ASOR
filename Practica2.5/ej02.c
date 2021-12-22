#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <time.h>

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
	//hints.ai_canonname = NULL;
	//hints.ai_addr = NULL;
	//hints.ai_next = NULL;


	if(getaddrinfo(argv[1], argv[2], &hints, &result) != 0){
		perror("Getaddrinfo error\n");
		return -1;
	}

	int udp = socket(result->ai_family, result->ai_socktype, result->ai_protocol);	
	bind(udp, result->ai_addr, result->ai_addrlen);

	//Comandos: t(time), d(date), q(quit)

	while(1){
		struct tm *act = localtime(time(0));

		char buf[2], host[128], port[3];
		struct sockaddr *client_addr;
		socklen_t client_addrlen = sizeof(client_addr);		

		recvfrom(udp, buf, 2, 0, client_addr, &client_addrlen);
		getnameinfo(client_addr, client_addrlen, host, 128, port, 3, NI_NUMERICHOST|NI_NUMERICSERV);

		printf("Recibidos mensaje %c de %s:%s\n", buf[0], host, port);

		char command = buf[0];
		char s[50];
		size_t max;

		switch(command){
			case 't':;
				size_t b = strftime(s, max, "%I:%M:%S %p", act);	
				s[b] = '\0';
       			sendto(udp, s, b, 0, client_addr, client_addrlen);
				//printf("%s:%s:%s\n", act->tm_hour, act->tm_min, act->tm_sec);

			break;
			case 'd':;
 	   	 	 	size_t b2 = strftime(s, max, "%Y-%m-%d", act);
				s[b2] = '\0';
       			sendto(udp, s, b, 0, client_addr, client_addrlen);
				//printf("%d %s de %s\n", act->tm_mday, act->tm_mon, act->tm_year+1900);
			break;
			case 'q':;
				return 0;
			break;
			default:;
		}
	}	
	return 0;
}
