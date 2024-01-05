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

    int edad, adivine, anio, velocidad;
    char car, vocal;
    bool b_car, b_edad, b_adivine, b_anio, b_velocidad, b_vocal;

    cout << "Este programa comprueba si la letra es minuscula o no\n\n";

    cout << "Introduce una letra minuscula: ";
    cin >> car;

    b_car = false;

    if(car>=97 && car<=124)
        b_car = true;

    cout << b_car << endl;

    //...

    cout << "\nEste programa comprueba si la edad es menor 18 o mayor que 65\n\n";

    cout << "Introduce la edad: ";
    cin >> edad;

    b_edad = false;

    if(edad<=18 | edad>=65)
        b_edad=true;

    cout << b_edad << endl;

    //...

    cout << "\nEste programa comprueba si el numero esta entre 1 y 100\n\n";

    cout << "Introduce un numero del 1 al 100: ";
    cin >> adivine;

    b_adivine = false;

    if(adivine>=1 && adivine<=100)
        b_adivine = true;

    cout << b_adivine;

    //...

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

    cout << b_anio << endl;

    //...

    cout << "\nEste programa comprueba si vas a mas de 100 km/h: ";

    cout << "Introduce una velocidad en km/h: ";
    cin >> velocidad;

    b_velocidad = false;

    if(velocidad>=100)
        b_velocidad = true;

    cout << b_velocidad << endl;

    //...

    cout << "Este programa comprueba si es vocal o consonante\n\n";

    cout << "Introduce una vocal: ";
    cin >> vocal;

    b_vocal = false;

    if(vocal=='a'| vocal=='e' | vocal=='i' | vocal=='o' | vocal=='u')
        b_vocal = true;

    cout << b_vocal << endl;
}
