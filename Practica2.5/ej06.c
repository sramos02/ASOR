#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <string.h>

int main(int argc, char* argv[]){
	if(argc != 3){
		printf("Invalid arguments\n");
		return -1;
	}

	struct addrinfo hints;
	struct addrinfo *result;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_STREAM;/* TCP socket */
	hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
	hints.ai_protocol = 0;          /* Any protocol */


   	if (getaddrinfo(argv[1], argv[2], &hints, &result) != 0){
		perror("getaddrinfo");
		return -1;
	}	

	int tcp = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	bind(tcp, result->ai_addr, result->ai_addrlen);

	freeaddrinfo(result);
	listen(tcp, 2);

	struct sockaddr_storage client_addr;
	socklen_t client_addrlen;
	char buf[50], host[NI_MAXHOST], port[NI_MAXSERV];
	int client_sd;

	while(1){
		client_sd = accept(tcp, (struct sockaddr *) &client_addr, &client_addrlen);

		while(1){
			getnameinfo((struct sockaddr *) &client_addr, client_addrlen, host, NI_MAXHOST, port, NI_MAXSERV, NI_NUMERICSERV);
			printf("Conexión desde %s:%s\n", host, port);

			ssize_t s = recv(client_sd, buf, 50, 0);

			if ((buf[0] == 'Q') && (s == 2)) {
        		printf("Conexión terminada\n");
				break;
			}
		
      		send(client_sd, buf, s, 0);
		}			
	}

	close(client_sd);
}
