#include <iostream>
#include <errno.h>
#include <string.h>
using namespace std;

int main() {
   for(int i = 0; i < 255; i++){
	errno = i;
  	perror("setuid error");
   }
   return 0;
}
