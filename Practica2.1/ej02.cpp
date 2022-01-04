#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
using namespace std;

int main() {
   int uid;
   cout << "Introduzca el nuevo uid: ";
   cin >> uid;

   errno = 

   if(setuid(uid) != 0) {
	cout << strerror(errno) << endl;
   	return 1;
   }
	
   cout << "Se ha completado la operación\n";
   return 0;
}
