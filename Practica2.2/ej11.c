#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){
	if(argc != 2){
		printf("Incorrect number of parameters\n");
		return -1;
	}

	char name[100] = "soft-";
	strcat(name, argv[1]);

	int soft = symlink(argv[1], name);
	if(soft < 0){
		perror("Soft link");
		return -1;
	}

	printf("New soft link file created: %s\n", name);

	strcpy(name, "hard-");
	strcat(name, argv[1]);
	int hard = link(argv[1], name);
	;
	if(hard < 0){
		perror("Hard link");
		return -1;
	}

	printf("New hard link file created: %s\n", name);
	return 0;
}
