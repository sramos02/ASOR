#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]){

	for(int i = 0; i < argc; i++)
		printf("%s\n", argv[i]);

	if(argc != 5){
		perror("Input error: Command1 Command2");
		return -1;
	}

	int fd[2];
        int pipe = pipe(fd);

	pid_t act;
	act = fork();

	if(act == -1){
		perror("Fork");
		return -1;
	}
	else if (act == 0){ //HIJO
		close(fd[1]);
		dup2(fd[0],0); //Se cambia el descriptor a la entrada
		close(fd[0]);
		execlp(argv[3], argv[3], argv[4]); //Ejecuta el comando
	}
	else{ //PADRE
		close(fd[0]);
		dup2(fd[1],1);
		close(fd[1]);
		execlp(argv[1], argv[1], argv[2]);
	}
	return 0;
}
