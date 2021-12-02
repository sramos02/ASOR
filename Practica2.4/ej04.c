#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]){

	char *name = "03pipe";

	if(argc != 2){
		perror("Arguments: File");
		return -1;
	}
	int fd = open(name, O_RDONLY);
	if(fd == -1){
		perror("Open file");
		return -1;
	}

	printf("Writing\n");
	write(fd, argv[1], strlen(argv[1]));
	close(fd);

	return 0;
}
