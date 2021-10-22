#include <iostream>
#include <time.h>
using namespace std;

int main(){
    const time_t t = time(0);
    struct tm * act = localtime(&t);

    cout << "Estamos en el año " << act->tm_year + 1900 << "\n";
    return 0;
}
