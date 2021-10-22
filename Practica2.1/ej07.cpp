#include <iostream>
#include <unistd.h>
using namespace std;

int main(){
    long f1,f2,f3;

    f1 = pathconf("/", _PC_LINK_MAX);
    f2 = pathconf("/", _PC_PATH_MAX);
    f3 = pathconf("/", _PC_NAME_MAX);
    if(f1 < 0){
 	perror;
 	return -1;
    }

    cout << "Num maximo  de enlaces: " << f1 << "\n";
    cout << "Tam maximo de una ruta: " << f2 << "\n";
    cout << "Tam maximo nombre fichero: " << f3 << "\n";
    return 0;
}
