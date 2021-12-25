#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]){

	if (argc != 3) {
		printf("Invalid arguments\n");
		return(-1);
	}

	//argv[0]: Direccion	argv[1]: Puerto
	//fd00::a:0:0:0:1		2222	

	struct addrinfo hints;
	struct addrinfo *result;
	
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_STREAM; /* TCP socket */
	hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
	hints.ai_protocol = 0;          /* Any protocol */	

	if(getaddrinfo(argv[1], argv[2], &hints, &result) != 0){
		perror("Getaddrinfo error");
		return -1;
	}

 	int tcp = socket(result->ai_family, result->ai_socktype, result->ai_protocol);		
 	connect(tcp,(struct sockaddr *)result->ai_addr, result->ai_addrlen);
	freeaddrinfo(result);

	char buf[50] = "";
	
	while(1){
		read(0, buf, 50);
		send(tcp, buf, 50, 0);
		printf("enviado: %s", buf);		

		if (*buf == 'Q') {
			printf("Conexión terminada\n");
			break;
		}

		recv(tcp, buf, 50, 0);
		printf("recibido: %s\n", buf);		
	}

	close(tcp);
}
