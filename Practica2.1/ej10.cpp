#include <iostream>
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>
using namespace std;

int main(){
    struct passwd *info;
    info = getpwuid(getuid());

    if(info == NULL){
   	perror("getInfo");
	return -1;
    }

    cout << "Tu nombre de usuario es: " << info->pw_name << "\n";
    cout << "Tu uid es: " << info->pw_uid << "\n";
    cout << "Directorio home: " << info->pw_dir << "\n";
    cout << "Descripción de usuario: " << info->pw_gecos << "\n";
    return 0;
}
