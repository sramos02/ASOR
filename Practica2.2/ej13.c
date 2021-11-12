#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	if(argc != 2){
		printf("Numero incorrectos de parametros [RUTA]");
		return -1;
	}

	int original_stdout = dup(1);
	int fd = open(argv[1], O_WRONLY |  O_CREAT);
	dup2(fd,1);
	close(fd);

	printf("Hello world\n");

	return 0;
}
