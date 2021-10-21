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

   errno = setuid(uid);

   if(errno == 0) cout << "Se ha completado la operación\n"; 
   else{
	cout << strerror(errno) << endl;
	//perror(errno);
   }
   return 1;
}
