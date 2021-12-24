#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <string.h>


int main(int argc, char* argv[]){

	if (argc != 4) {
		perror("Invalid arguments\n");
		return(-1);
	}

	//argv[0]: Direccion	argv[1]: Puerto	    argv[2]: Comando
	//192.168.0.1		3000		    t

	struct addrinfo hints;
	struct addrinfo *result;
	
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
	hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
	hints.ai_protocol = 0;          /* Any protocol */	

	if(getaddrinfo(argv[1], argv[2], &hints, &result) != 0){
		perror("Getaddrinfo error");
		return -1;
	}

 	int sck = socket(result->ai_family, result->ai_socktype, result->ai_protocol);		
	sendto(sck, argv[3], 2, 0, result->ai_addr, result->ai_addrlen);
	freeaddrinfo(result);

	if(*argv[3] == 'd' || *argv[3] == 't'){
		struct sockaddr_storage client_addr;
		socklen_t client_addrlen = sizeof(client_addr);
		char s[50];

		recvfrom(sck, s, 50, 0, (struct sockaddr *) &client_addr, &client_addrlen);
		printf("%s\n", s);
	}

	

}
