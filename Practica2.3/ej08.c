#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	if(argc < 2){
		perror("Argumentos invalidos");
		return -1;
	}

	int ret;

	char* buf = get_current_dir_name();
	strcat(buf, "/tmp/daemon.out");
	printf("%s\n",buf);
        int fd = open(buf, O_CREAT);
        dup2(fd,1);
        close(fd);


	pid_t pid = fork();
	int status; //Para el hijo
	pid_t hijo;

	switch(pid){
		case -1:
			perror("Fork");
			ret = -1;
			break;
		case 0:
			//HIJO
			execvp(argv[1], argv+1);
			printf("El comando terminó de ejecutarse\n");
			ret = 1;
			break;
		default:
			hijo = waitpid(0, &status, 0);
			ret = 0;
			break;
	}

	return ret;
}
