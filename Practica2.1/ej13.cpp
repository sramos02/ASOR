#include <iostream>
#include <sys/time.h>
using namespace std;

int main(){
    struct timeval ini, fin;

    int ret1 = gettimeofday(&ini, NULL);
    for(int i = 0; i < 1000000; i++);
    int ret2 = gettimeofday(&fin, NULL);

    if(ret1 < 0 || ret2 < 0){
	perror("getTime");
	return -1;
    }
    cout << "El bucle ha tardado " << fin.tv_usec - ini.tv_usec << " microsegundos\n";
    return 0;
}
