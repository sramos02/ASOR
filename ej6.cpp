#include <iostream>
#include <unistd.h>
#include <string.h>
using namespace std;

int main(){
    long f1, f2, f3;

    f1 = sysconf(_SC_ARG_MAX);
    f2 = sysconf(_SC_CHILD_MAX);
    f3 = sysconf(_SC_OPEN_MAX);
    if(f1 < 0 || f2 < 0 || f3 < 0){
	perror("uname");
	return -1;
    }
    cout << "Long maxima argumentos: " << f1 << "\n";
    cout << "Num maximo de hijos: " << f2 << "\n";
    cout << "Num maximo de ficheros: " << f3 << "\n";
    return 0;
}
