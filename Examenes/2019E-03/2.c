#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]){

	if(argc < 2){
		perror("Invalid arguments\n");
		return -1;
	}

	pid_t hijo;
	int status;

	pid_t act =  fork();
	switch(act){
		case -1:
			perror("Fork error\n");
			return -1;
		break;
		
		case 0: //HIJO
			chdir("/tmp");
			printf("ID actual: %d\n", getpid());
			printf("ID padre : %d\n", getppid());
			printf("ID grupo : %d\n", getpgrp());
			printf("ID sesion: %d\n", getsid(getpid()));
			printf("------------------ /TMP -----------------\n");
			execvp(argv[1], argv+1);
			printf("------------------ /TMP -----------------\n");
		break;
		
		default:
			hijo = waitpid(0, &status, 0);
		break;
	}
	return 0;
}
