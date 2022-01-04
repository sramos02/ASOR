#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
using namespace std;

int main() {
   int uid;
   cout << "Introduzca el nuevo uid: ";
   cin >> uid;

   if(setuid(uid) != 0){
      perror("setuid error");
      return -1;
   }
   
   cout << "Se ha completado la operación\n";
   return 0;
}
