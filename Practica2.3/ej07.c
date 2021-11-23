#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	char string[256] = "";
	int i = 2;

	strcpy(string,  argv[1]);
	while(i < argc){
		strcat(string, " ");
		strcat(string, argv[i]);
		i++;
	}

	int ret = system(string);
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
	//return execl(argc, argv);
	return sys(argc, argv);
}
