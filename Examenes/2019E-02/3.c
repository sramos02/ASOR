#include <stdio.h>

#include <sys/types.h>
#include <unistd.h>
#include <limits.h>

#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char* argv[]){

	if(argc < 3){
		//Argumentos Comando 1 | Comando 2 [Args]
		perror("Invalid arguments\n");
		return -1;
	}

	int fd[2]; //Pipe [Entrada | Salida]
	if(pipe(fd) == -1){
		perror("Error pipe\n");
		return -1;
	}
	
	pid_t act = fork();
	
	switch(act){
		case -1:
			perror("Fork error\n");
			return -1;
			
		case 0: //HIJO
			printf("Comando 2: %s\t\tPID: %d\n", argv[2], getpid());

			close(fd[1]);
			dup2(fd[0], 0); //Copy std input to pipe in
			close(fd[0]);

			execlp(argv[2], argv[2], argv[3], NULL);
		break;
		
		default: //PADRE
			printf("Comando 1: %s\t\tPID: %d\n", argv[1], getpid());

			close(fd[0]);
			dup2(fd[1], 1); //Copy std output to pipe out 			
			close(fd[1]);

			system(argv[1]); //execlp(argv[1], argv[1], NULL);
		break;
	}

	return 0;
}
