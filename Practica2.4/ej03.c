#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]){

	char *name = "03pipe";

	if(mkfifo(name, 0644) == -1){
		perror("Pipe creation");
		return -1;
	}

	execlp("stat", "stat", name);

	//to write echo "Prueba" > 03pipe

	//to see info use tail -f 03pipe
	return 0;
}
