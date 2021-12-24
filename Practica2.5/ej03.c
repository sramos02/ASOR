#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


int main(int argc, char* argv[]){

	if (argc != 2) {
		perror("Invalid arguments\n");
		return(-1);
	}

	//argv[0]: Direccion	argv[1]: Puerto	    argv[2]: Comando
	//192.168.0.1		3000		    t

	struct addrinfo hints;
	struct addrinfo *result;
	
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
	hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
	hints.ai_protocol = 0;          /* Any protocol */	

	if(getaddrinfo(argv[1], argv[2], &hints, &result) != 0){
		perror("Getaddrinfo error\n");
		return -1;
	}

 	int sck = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	
	if(bind(sck, result->ai_addr, result->ai_addrlen) != 0){
		perror("Bind error\n");
		return -1;	
	}
	
	freeaddrinfo(result);
	
	char host[NI_MAXHOST], service[NI_MAXSERV];
	char buf[2];
	struct sockaddr_storage client_addr;
	size_t client_len = sizeof(client_addr);
	while(1){

		sendto(sck, argv[3][0], 1, 0, (struct sockaddr *) &client_addr, client_len);
	
		s = getnameinfo((struct sockaddr *) &peer_addr, peer_addr_len, host, NI_MAXHOST,	 service, NI_MAXSERV, NI_NUMERICSERV);




		switch(argv[3]){
			case
		}
	}
	

}
