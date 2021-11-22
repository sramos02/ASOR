#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <limits.h>

int main(){
	pid_t pid = getpid();
	pid_t ppid = getppid();

	printf("PROCESO ACTUAL: %d\n", pid);
	printf("PROCESO PADRE: %d\n", ppid);

	pid_t pgid = getpgid(pid);
	printf("ID GRUPO: %d\n", pgid);

	pid_t sid = getsid(pid);
	printf("ID SESION: %d\n", sid);

	char * buffer;
	char * ret = getcwd(buffer, PATH_MAX);
	printf("DIRECTORIO ACTUAL: %s\n", buffer);

	struct rlimit act;
	int maxf = getrlimit(RLIMIT_NOFILE, &act);
	printf("MAX FICHEROS: %d\n", maxf);
	return 0;
}
