#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>


int main(int argc, char* argv[]){
	if(argc != 2){
		perror("Argumentos: Segundos\n");
		return -1;
	}

	sigset_t set, pend;

	sigemptyset(&set); //Inicializamos el conjunto
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGTSTP);

	sigprocmask(SIG_BLOCK, &set, NULL); //BLoqueamos las señales, hay que desbloquearlas luego

	//char* s = getenv("SLEEP_SECS");
	sleep(atoi(argv[1]));


	sigpending(&pend);
	if (sigismember(&pend, SIGINT) == 1)
		printf("El proceso recibió SIGINT\n");
	else if (sigismember(&pend, SIGTSTP) == 1)
		printf("El proceso recibió SIGTSTP\n");
	else printf("El proceso no ha resibido señales\n");

	sigprocmask(SIG_UNBLOCK, &set, NULL);
	return 0;
}
