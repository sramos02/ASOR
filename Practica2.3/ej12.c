#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

volatile int intcount = 0;
volatile int tstpcount = 0;


void aux(int signal){
	if(signal == SIGINT) intcount += 1;
	if(signal == SIGTSTP) tstpcount += 1;
}

int main(int argc, char* argv[]){

	struct sigaction act;

	//Captures (update the value)
	sigaction(SIGINT, NULL, &act);
	act.sa_handler = aux;
	sigaction(SIGINT, &act, NULL);


	sigaction(SIGTSTP, NULL, &act);
	act.sa_handler = aux;
	sigaction(SIGTSTP, &act, NULL);

	sigset_t set;
	sigemptyset(&set);

	while(intcount + tstpcount < 10){
		sigsuspend(&set);
	}

	printf("Señales SIGINT: %d\n", intcount);
	printf("Señales SIGTSTP: %d\n", tstpcount);
	return 0;
}
