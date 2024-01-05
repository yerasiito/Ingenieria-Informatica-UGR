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
    const double tarifa_base=150;
    double tarifa_variable,tarifa_final;
    int puntos;
    double km;

    cout << "Este programa calcula el precio final de un vuelo convencional.\n\n";

    cout <<"Introduce la distancia a su destino(en km):";
    cin >>km;
    cout << "Introduzca sus puntos: ";
    cin >>puntos;

    tarifa_variable=(km-300)*0.1;

    if(km>300)
        tarifa_final=tarifa_base + tarifa_variable;
    else
        tarifa_final=tarifa_base;
    if(puntos>=100)
    {
        if(puntos>=200)
            tarifa_final = tarifa_final*0.96;       //descuento 4%
        else
            tarifa_final = tarifa_final*0.97;       //descuento 3%
    }
    if(km>=700)
        tarifa_final = tarifa_final*0.98;           //desuento 2%

    cout << "El precio final es: " << tarifa_final << endl;
}


