#include <iostream>
#include <sys/utsname.h>
#include <string.h>
using namespace std;

int main(){
    struct utsname info;

    if(uname(&info) < 0){
	perror("uname");
	return -1;
    }

    cout << "Sys name: " << info.sysname << "\n";
    cout << "Node name: " << info.nodename << "\n";
    cout << "And all other values...\n";
    return 0;
}
