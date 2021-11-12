#include <stdio.h>
#include <sys/file.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	if(argc != 2){
		printf("Numero incorrectos de parametros [RUTA]\n");
		return -1;
	}
	int fd = open(argv[1], O_WRONLY |  O_CREAT);

	int state = lockf(fd, F_TEST, 0);
	if(state == 0){
		printf("File is unlocked\n");
		int ret = lockf(fd, F_LOCK, 0);
		if(ret < 0){
			perror("Lock: ");
			return -1;
		}

		const time_t t = time(0);
		struct tm *now = localtime(&t);
		printf("%d:%d:%d\n", now->tm_hour, now->tm_min, now->tm_sec);
		sleep(30);

		ret = lockf(fd, F_ULOCK,0);
		if(ret < 0){
			perror("Lock: ");
			return -1;
		}
	}
	else{
		printf("File is locked\n");
	}

	return 0;
}
