#include <iostream>
#include <unistd.h>
#include <sys/types.h>
using namespace std;

int main(){
    cout << "Tu uid es: " << getuid() << "\n";
    return 0;
}
