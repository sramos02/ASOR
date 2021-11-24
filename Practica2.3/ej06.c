#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>


void padre(){
	int status;
	pid_t hijo = waitpid(0, &status, 0);
	if(WIFEXITED(status))
		printf("El demonio ha terminado\n");
}

void hijo(){
	pid_t pid = getpid();
	pid_t ppid = getpid();

	printf("PROCESO ACTUAL: %d\n", pid);
	printf("PROCESO PADRE: %d\n", ppid);

	pid_t pgid = getpgid(pid);
	printf("ID GRUPO: %d\n", pgid);

	pid_t sid = getsid(pid);
	printf("ID SESION: %d\n", sid);

	char buffer[PATH_MAX];
	char * ret = getcwd(buffer, PATH_MAX);
	printf("DIRECTORIO ACTUAL: %s\n", buffer);

	struct rlimit act;
	int maxf = getrlimit(RLIMIT_NOFILE, &act);
	printf("MAX FICHEROS: %d\n", maxf);
}

int main(){

	pid_t pid = fork();

	switch(pid){
		case -1:
			perror("FORK");
			return -1;
		case 0:
			hijo();
			return 1;
		default:
			padre();
			return 0;
	}
}
