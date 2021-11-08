#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	int ret = open("ej5.txt", O_CREAT, 0645);
	if(ret == -1){
		perror("Creación");
		return -1;
	}
	close(ret);
}
