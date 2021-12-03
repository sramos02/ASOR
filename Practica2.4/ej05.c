#include <stdio.h>

//Mkfifo
#include <sys/types.h>
#include <sys/stat.h>

//Open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//Close
#include <unistd.h>

int main(int argc, char* argv[]){

	char *name1 = "pipe1";
	char *name2 = "pipe2";

	if(mkfifo(name1, 0644) == -1){
                perror("Pipe1 ya existe");
        }

	if(mkfifo(name2, 0644) == -1){
                perror("Pipe2 ya existe");
        }

	int pipe1 = open(name1, O_RDONLY);
	int pipe2 = open(name2, O_RDONLY);

	fd_set conjunto;
 	FD_ZERO(&conjunto);
 	FD_SET(pipe1, &conjunto);
  	FD_SET(pipe2, &conjunto);


	//Espera a que haya datos listo en alguna de las pipes
	char buffer1[256], buffer2[256];
	int numPipe, actPipe; //Init
	int cambios = 0;

	while(!cambios){
	    	int actPipe;

		//cambios ? (buffer1 == buffer2) = true : false;
		cambios = select((pipe1 < pipe2) ? pipe2 + 1 : pipe1 + 1, &conjunto, NULL, NULL, NULL);

		if (cambios){
			//Definimos en qué pipe nos encontramos.
			if (FD_ISSET(pipe1, &conjunto)) {
				numPipe = 1;
				actPipe = pipe1;
			}
 			else if (FD_ISSET(pipe2, &conjunto)) {
				numPipe = 2;
				actPipe = pipe2;
			}


			//Cierra la pipe y vuelve a abrirla
			if(numPipe == 1){
				close(pipe1);
				pipe1 = open(name1, O_RDONLY | O_NONBLOCK);
			}
			else{
				close(pipe2);
				pipe2 = open(name2, O_RDONLY | O_NONBLOCK);
			}
		}
	}
	return 0;
}
