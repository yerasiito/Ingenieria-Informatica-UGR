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
    int anio;
    bool b_anio;

    cout << "\nEste programa comprueba si es un anio bisiesto o no\n\n";

    cout << "Introduce un anio: ";
    cin >> anio;

    b_anio = false;

    if(anio%4==0)
    {
        b_anio = true;

        if(anio%100==0)
            b_anio=false;
    }

    if(anio%400==0)
        b_anio = true;

    if(b_anio)
        cout << "Es un anio bisiesto.";
    else
        cout << "No es un anio bisiesto.";

}

