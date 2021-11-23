#include <stdio.h>
#include <stdlib.h>

int execl(int argc, char* argv[]){
	pid_t pid = fork();

	int status; //Para el hijo
	pid_t hijo;

	switch(pid){
		case -1:
			perror("Fork");
			return -1;
		case 0:
			//HIJO
			execvp(argv[1], argv+1);
			printf("El comando terminó de ejecutarse\n");
			return 1;
		default:
			hijo = waitpid(0, &status, 0);
			return 0;
	}
}

int sys(int argc, char* argv[]){
	int ret = system(argv[1]);
	if(ret == -1){
		perror("system");
		return -1;
	}
	printf("El comando terminó de ejecutarse\n");
	return 0;
}

int main(int argc, char* argv[]){

	if(argc < 2){
		perror("Argumentos invalidos");
		return -1;
	}
	return execl(argc, argv);
	//return sys(argc, argv);
}
