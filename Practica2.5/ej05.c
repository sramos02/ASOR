#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <time.h>
#include <string.h>

int main(int argc, char* argv[]){
	if(argc < 3){
		printf("Invalid arguments\n");
		return -1;
	}

	//argv[1]: Dir 		argv[2]: Port

	struct addrinfo *result;
	struct addrinfo hints;
	int udp;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
	hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
	hints.ai_protocol = 0;          /* Any protocol */

	if (getaddrinfo(NULL, argv[1], &hints, &result) != 0){
		perror("Getaddrinfo error");
		return -1;
	}

	udp = socket(result->ai_family, result->ai_socktype, result->ai_protocol);        
    bind(udp, result->ai_addr, result->ai_addrlen);

	freeaddrinfo(result);  

	struct sockaddr_storage client_addr;
	socklen_t client_addrlen = sizeof(client_addr);
	char host[NI_MAXHOST], port[NI_MAXSERV];
	char buf;
		
	int status;
	int i = 0;
	for(i; i < 2; i+=1){ //En este caso solo tenemos dos procesos concurrentes
		pid_t pid;
		pid = fork();

		if(pid == -1){
			perror("Fork error");
			return -1;	
		}
		else if (pid == 0) {
			const time_t t = time(0);
			struct tm *act = localtime(&t);
			char s[50];

			recvfrom(udp, buf, 1, 0, (struct sockaddr *) &client_addr, &client_addrlen);
            getnameinfo((struct sockaddr *) &client_addr, client_addrlen, host, NI_MAXHOST, port, NI_MAXSERV, NI_NUMERICSERV);

			printf("Recibido mensaje %c de %s:%s\n", buf, host, port);

			switch(buf){
				case 't':;
					size_t b = strftime(s, 50, "%I:%M:%S %p\n", act);	
					sendto(udp, s, b, 0, (struct sockaddr *) &client_addr, client_addrlen);

				break;
				case 'd':;
			 	 	size_t b2 = strftime(s, 50, "%d-%m-%Y\n", act);
					sendto(udp, s, b, 0, (struct sockaddr *) &client_addr, client_addrlen);

				break;
				case 'q':;
					char msg[17] = "Fin de conexión\n";
					sendto(udp, msg, 17, 0, (struct sockaddr *) &client_addr, client_addrlen);
					return 1;
				break;

				default:;
					char msg2[31] = "No se ha reconocido el comando\n";
					sendto(udp, msg2, 31, 0, (struct sockaddr *) &client_addr, client_addrlen);
				break;
			}
	
		}
		else{
			pid = wait(&status); //El hijo espera
		}	
	}			
	return 0;
}
