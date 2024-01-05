#include <iostream>
using namespace std;

double caja_izda;
double caja_dcha;
double intercambio;      //variable auxiliar

int main()
{
    cout << "Este programa intercambia el valor de dos cajas, sin confundir al usuario.\n\n";

    cout << "Introduzca el valor de la caja izquierda: ";
    cin >> caja_izda;
    cout << "Introduzca el valor de la caja derecha: ";
    cin >> caja_dcha;

    intercambio = caja_dcha;        //guardamos el valor de una de las cajas en la variable intercambio
    caja_dcha = caja_izda;
    caja_izda = intercambio;        //usando la variable intercambio, intercambiamos el valor de las cajas

    cout << "\nLa caja izquierda vale " << caja_izda << "\n";
    cout << "La caja derecha vale " << caja_dcha;
}

