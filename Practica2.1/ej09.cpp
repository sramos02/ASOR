#include <iostream>
#include <unistd.h>
#include <sys/types.h>
using namespace std;

int main(){
    cout << "Tu uid es: " << getuid() << "\n";
    // si el fichero de programa tiene los bits setuid o setgid activos, 
    // el EUID o el EGID del proceso creado se cambian al usuario o grupo del fichero
    return 0;
}
