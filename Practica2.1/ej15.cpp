#include <iostream>
#include <time.h>
using namespace std;

char* dia(int numDia){
    char* ret;
    switch(numDia){
	case 0: ret = "Domingo";
	break;
	case 1: ret = "Lunes";
	break;
	case 2: ret = "Martes";
	break;
	case 3: ret = "Miercoles";
	break;
	case 4: ret = "Jueves";
	break;
	case 5: ret = "Viernes";
	break;
	case 6: ret = "Sabado";
    }
    return ret;
}

char* mes(int numMes){
    char* ret;
    switch(numMes){
	case 0: ret = "Enero";
	break;
	case 1: ret = "Febrero";
	break;
	case 2: ret = "Marzo";
	break;
	case 3: ret = "Abril";
	break;
	case 4: ret = "Mayo";
	break;
	case 5: ret = "Junio";
	break;
	case 6: ret = "Julio";
	break;
	case 7: ret = "Agosto";
	break;
	case 8: ret = "Septiembre";
	break;
	case 9: ret = "Octubre";
	break;
	case 10: ret = "Noviembre";
	break;
	case 11: ret = "Diciembre";
    }
    return ret;
}



int main(){
    const time_t t = time(0);
    struct tm * act = localtime(&t);

    cout << dia(act->tm_wday) << ", " << act->tm_mday << " de " << mes(act->tm_mon) << " de " << act->tm_year + 1900 << ", " << act->tm_hour << ":" << act->tm_min << "\n";
    return 0;
}
