#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
using namespace std;

int main() {
   int uid;
   cout << "Introduzca el nuevo uid: ";
   cin >> uid;

   errno = setuid(uid);
  
   if(errno == 0) cout << "Se ha completado la operación\n";
   else perror("setuid error");
   return 1;
}
