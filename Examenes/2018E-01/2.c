#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	
	if(argc != 2){
		printf("Invalid arguments\n");
		return -1;
	}

	if(chdir(argv[1]) != 0){
		perror("Chdir");
		return -1;
	}	
	

	DIR *path = opendir(argv[1]);
	
	struct dirent *act;
	
	
	while((act = readdir(path)) != NULL){
		struct stat info;
		stat(argv[1], &info);
		printf("Name: %s\nInode: %ld\nOwner:%d\nSize:%ld\n\n", act->d_name, act->d_ino, info.st_uid, info.st_size);
	}

	return 0;
}
