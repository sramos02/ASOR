#include <iostream>
#include <time.h>
using namespace std;

int main(){
    time_t hora;

    hora = time(0); //Actual time in seconds (since EPOCH)
    if(hora < 0){
	perror("Hora");
	return -1;
    }

    cout << hora << "\n";
    return 0;
}
