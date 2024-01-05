//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    char RADAR;
    double vel;
    long double vel_imputada;

    cout << "Este programa calcula la velocidad imputada de un vehiculo: \n\n";

    cout << "\n Introduzca el tipo de radar (F para fijo y otra letra para movil): ";
    cin >> RADAR;
    cout << " Introduzca la velocidad del vehiculo: ";
    cin >> vel;

    if(RADAR =='F')
    {
    vel_imputada = vel*0.95;
    }
    else
        vel_imputada = vel*0.93;

    cout << "\n   La velocidad imputada es " << vel_imputada << endl;

    return 0;
}


