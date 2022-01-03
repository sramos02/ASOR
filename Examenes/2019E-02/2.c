#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <string.h>


int	main(int argc, char *argv[]){
	
	if (argc != 3) {
		printf("Invalid arguments\n");
		return -1;
	}
	
	struct addrinfo hints;
	struct addrinfo *result;
	
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
	hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
	hints.ai_protocol = 0;          /* Any protocol */
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;

	if (getaddrinfo(argv[1], argv[2], &hints, &result) != 0){
		perror("Getaddrinfo");
		return -1;
	}
	
	int tcp = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
              
	if(bind(tcp, result->ai_addr, result->ai_addrlen) != 0){
		perror("Bind");
		return -1;
	}
	
	freeaddrinfo(result);           /* No longer needed */
	listen(tcp, 5);
	
	struct sockaddr_storage client_addr;
	socklen_t client_addrlen;
	char host[NI_MAXHOST], port[NI_MAXSERV];
	char buf[256];
	int c, client_sd;
	
	while(1){
		client_sd = accept(tcp, (struct sockaddr *) &client_addr, &client_addrlen);
		getnameinfo((struct sockaddr *) &client_addr, client_addrlen, host, NI_MAXHOST, port, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
  
  		printf("Conexión desde %s:%s\n", host, port);
		while (c = recv(client_sd, buf, 256, 0)) { // Comprobar mensaje!	
			send(client_sd, buf, c, 0);
		}
		
		close(client_sd);
	}		
}
	
	
