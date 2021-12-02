#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]){

	int p_h[2], h_p[2];
	if(pipe(p_h) == -1 || pipe(h_p)){
		perror("Pipe");
		return -1;
	}

	pid_t pid = fork();
	switch(pid){
	case -1:
		perror("Fork");
		return -1;

	case 0: //HIJO
		close(p_h[1]);
		close(h_p[0]);

		char msg[32];
		for(int i = 0; i < 10; i++) {
			read(p_h[0], msg, 256);
			msg[256] = '\0';

			printf("Mensaje %d: %s", i+1, msg);
			sleep(1);

			if(i != 9) write(h_p[1], '0', 1);
			else write(h_p[1], 'q', 1);
		}

		close(p_h[0]);
		close(h_p[1]);
		break;

	default: //PADRE
		close(p_h[0]);
		close(h_p[1]);

		char hijo = '0';
		char msgp[256];

		sleep(1);
		printf("Introduzca un mensaje: \n");
		read(0, msgp,255);
		msgp[32] = '\0';

		write(p_h[1], msgp, 256);
		while(hijo != '0' && hijo != 'q')
			read(h_p[0], hijo, 1);

		close(p_h[1]);
		close(h_p[0]);
		break;
	}
	return 0;
}
