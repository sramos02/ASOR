#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	if(argc != 3){
		printf("Invalid arguments\n");
		return -1;
	}

	
	struct addrinfo hints;
	struct addrinfo *result;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
	hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
	hints.ai_protocol = 0;          /* Any protocol */
	
	getaddrinfo(argv[1], argv[2], &hints, &result);	
	int tcp = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    
	if (bind(tcp, result->ai_addr, result->ai_addrlen) != 0){
		perror("Bind error");
		return -1;	
	}
             
	freeaddrinfo(result);     	
	listen(tcp, 2); //Dos procesos simultaneos
	

	struct sockaddr_storage client_addr;
	socklen_t client_addrlen;
	char buf[256], host[NI_MAXHOST], port[NI_MAXSERV];
	int client_sd;

	while(1){
		client_sd = accept(tcp, (struct sockaddr *) &client_addr, &client_addrlen);

		pid_t act = fork();

		switch(act){
			case -1:
				perror("fork error");
				return -1;
			break;
			case 0: //HIJO
				getnameinfo((struct sockaddr *) &client_addr, client_addrlen, host, NI_MAXHOST, port, NI_MAXSERV, NI_NUMERICSERV);
				printf("[PID: %s], Conexión desde %s:%s\n", getpid(), host, port);

				while(1){
					ssize_t s = recv(client_sd, buf, 255, 0);
					buf[256] = '\0';

					if (*buf == 'Q') {
						printf("Conexión terminada\n");
						break;
					}
				
		  			send(client_sd, buf, s, 0);
				}
			break;
			default:
				close(client_sd);		
			break;
		}

		close(client_sd);
	}

	return 0;
}
