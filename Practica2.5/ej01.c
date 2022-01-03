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

	struct addrinfo *it, *result;
	struct addrinfo hints;

	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = 0;


	if(getaddrinfo(argv[1], NULL, &hints, &result) != 0){
		perror("Getaddrinfo error\n");	
		return -1;
	}

	for(it = result; it != NULL; it = it->ai_next){
		switch(it->ai_family){
			case AF_INET:;
				struct sockaddr_in *info4 = it->ai_addr;
				char ipv4[32] = "";
				inet_ntop(AF_INET, &info4->sin_addr, ipv4, 32);
				printf("IP    : %s\n", ipv4);
				printf("Family: AF_INET\n");
			break;
			case AF_INET6:;
				struct sockaddr_in6 *info6 = it->ai_addr;
				char ipv6[128] = "";
				inet_ntop(AF_INET6, &info6->sin6_addr, ipv6, 128);
				printf("IP    : %s\n", ipv6);
				printf("Family: AF_INET6\n");
			break;
		}
		
		printf("Socket: %i\n", it->ai_socktype);
	}

	return 0;
}
