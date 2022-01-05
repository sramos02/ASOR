#include <stdio.h>

#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

int main(int argc, char* argv[]){
	if(argc < 2){
		perror("Argumentos invalidos");
		return -1;
	}

	pid_t pid = fork();
	switch(pid){
		case -1:;
			perror("Fork");
			exit(1);
			break;
		case 0:; //HIJO
      		if(setsid() == -1){ //Creamos una nueva sesión
				perror("Sid change");
				return -1;
			}
			int fd = open("/tmp/daemon.out", O_CREAT | O_RDWR, 0777);
			int fderr = open("/tmp/daemon.err", O_CREAT | O_RDWR, 0777);
			
			dup2(fd, 2); //Salida std
			dup2(fderr, 1); //Salida error
			
			printf("Ejecutando comando...\n");
			if (execvp(argv[1], argv+1) == -1){
				perror("Execvp");
				return -1;
			}
			break;
		default:;
			
	        printf("El proceso se ha ejecutado correctamente\n");
			break;
	}

	return 0;
}
