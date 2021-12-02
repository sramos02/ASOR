#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]){

	if(argc != 5){
		perror("Input error: Command1 Command2");
		return -1;
	}

	int fd[2];
	if(pipe(fd) == -1){
		perror("pipe");
		return -1;
	}


	pid_t pid = fork();
	switch(pid){
	case -1:
		perror("Fork");
		return -1;

	case 0: //HIJO
		close(fd[1]);
		dup2(fd[0],0); //Se cambia el descriptor a la entrada
		close(fd[0]);
		execlp(argv[3], argv[3], argv[4], NULL); //Ejecuta el comando
		break;

	default: //PADRE
		close(fd[0]);
		dup2(fd[1],1);
		close(fd[1]);
		execlp(argv[1], argv[1], argv[2], NULL);
		break;
	}
	return 0;
}
