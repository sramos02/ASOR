#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	if(argc != 2){
		printf("Format error: [DIR ROUTE]\n");
		return -1;
	}

	char* path;
	char actualPath [PATH_MAX + 1];
	path = realpath(argv[1], actualPath);

	if(path == NULL){
		printf("Specified route does not exists");
		return -1;
	}

	DIR *dir;
	if((dir = opendir(path)) == NULL){
		perror("Directory error: ");
		return -1;
	}

	struct dirent *str;
	struct stat sb;
	long int size = 0;
	printf("Directory opened sucsesfully\n");
	while ((str = readdir(dir)) != NULL) {
		 stat(path, &sb);
		//It is a regular file
		if(S_ISREG(sb.st_mode)){
			printf("%s", str->d_name);
			size += sb.st_size;

			//It is executable
			if(sb.st_mode & S_IXUSR){
				printf("*\n");
			}

			//It is soft link
			if(S_ISLNK(sb.st_mode)){
				printf("->\n");
			}

			printf("\n");
		}
		//It is a directory
		else if(S_ISDIR(sb.st_mode)){
			printf("%s", str->d_name);
			printf("/\n");
		}
	}

	printf("All regular files occupied %ld kbits", size/1024);
	closedir(path);
	return 0;
}
