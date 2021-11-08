#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>

int main(int argc, char *argv[]){
	struct stat sb;

	if (argc != 2) {
		fprintf(stderr, "ncorrect number of parameters\n");
      		return -1;
   	}

	if (lstat(argv[1], &sb) == -1) {
		perror("lstat");
		return -1;
	}

    	printf("Major number: %lx\n", (long) major(sb.st_dev));
   		printf("Minor number: %lx\n", (long) minor(sb.st_dev));
	printf("I-Node: %ld\n", (long) sb.st_ino);
	printf("File type : ");

	switch (sb.st_mode & S_IFMT) {
	   case S_IFBLK:  printf("block device\n");            break;
           case S_IFCHR:  printf("character device\n");        break;
           case S_IFDIR:  printf("directory\n");               break;
           case S_IFIFO:  printf("FIFO/pipe\n");               break;
           case S_IFLNK:  printf("symlink\n");                 break;
           case S_IFREG:  printf("regular file\n");            break;
           case S_IFSOCK: printf("socket\n");                  break;
           default:       printf("unknown?\n");                break;
	}

	printf("Last file access: %s\n", ctime(&sb.st_atime));
	return 0;
}
