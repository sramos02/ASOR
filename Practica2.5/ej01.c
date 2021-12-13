#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char* argv[]){
	if(argc < 2){
		perror("Invalid arguments\n");
		return -1;
	}


	struct addrinfo *aux, *result;
	struct hints;

	hints.ai_family = AF_UNSPEC;    //IPv4 or IPv6
	hints.ai_socktype = 0; 		//Datagram socket
	hints.ai_flags = AI_PASSIVE;    //For wildcard IP address 
	hints.ai_protocol = 0;          //Any protocol
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;

	if(getaddrinfo(argv[1], NULL, &hints, &result) != 0) {
		perror("Getaddrinfo error\n");
		return -1;
	}


 	for (aux = result; aux != NULL; aux = aux->ai_next) {
    		switch (aux->ai_family) {
     	 		case AF_INET:;
        			struct sockaddr_in *info = aux->ai_addr;
				char ipv4[32] = "";
				inet_ntop(&aux->ai_family, &info->sin_addr, ip, 32);
				printf("IP    : %s\n",ip);
				printf("Family: AF_INET\n"); 
			break;
			case AF_INET6:;
				struct sockaddr_in6 *info6 = aux->ai_addr;
        			char ipv6[128] = "";
        			inet_ntop(&aux->ai_family, &info6->sin6_addr, ipv6, 128);
				printf("IP    : %s\n",ipv6);
				printf("Family: AF_INET6\n"); 
		        break;
		}

		switch(aux->ai_socktype){
			case 1: printf("Socket: SOCK_STREAM\n");
			break;
			case 2: printf("Socket: SOCK_DGRAM\n");
			break;
			case 3: printF("Socket: SOCK_RAW\n");
			break;
		}
	}


	return 0;
}
