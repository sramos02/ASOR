#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <limits.h>

volatile int stop = 0;

void handler(int signal){
	if(signal == SIGUSR1)
		printf("Usuario para el proceso\n");
		stop = 1; //No reentrante pero podría usar exit(0)
}

int main(int argc, char* argv[]){

	if(argc != 2){
		perror("Argumentos: Segundos\n");
		return -1;
	}


	//Bloqueamos todas las señales menos la que nos interesa
	sigset_t group;
	sigfillset(&group);
	sigdelset(&group, SIGUSR1);
	sigprocmask(SIG_BLOCK, &group, NULL);

	//Configuramos la señal para que pare el programa cuando la reciba
	struct sigaction act;
	sigaction(SIGUSR1, NULL, &act);
	act.sa_handler = handler;
	sigaction(SIGUSR1, &act, NULL);

	//Creamos un temporizador para borrar el ejecutable a los n segundos
	int i = 0;
	int s = atoi(argv[1]);
	while (i < s && stop == 0) {
   		i++;
    		sleep(1);
  	}

	if(stop == 0)
		unlink(argv[0]);
	return 0;
}
