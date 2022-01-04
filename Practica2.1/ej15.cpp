#include <iostream>
#include <time.h>
using namespace std;

int main(){
    struct tm * act = localtime(time(0));
    char* t;
	
    strftime(t, 255, "%H:%M a %A, %d de %B");
    cout << t << "de " << act->tm_year + 1900;
    return 0;
}
