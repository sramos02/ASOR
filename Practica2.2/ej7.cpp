#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
       //Los valores por defecto son 644
	umask(0027); //Solo tien permiso de escritura el grupo y todos para el usuario normal
	int ret = open("ej7.txt", O_CREAT, 0777);
	if(ret == -1){
		perror("Creación");
		return -1;
	}
	close(ret);
}
