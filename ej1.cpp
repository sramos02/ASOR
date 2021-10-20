#include <iostream>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

int main() {
   if(setuid(0) < 0){
	perror("setuid error");
   }
  else  cout << "Se ha completado la operación\n";
   return 1;
}
