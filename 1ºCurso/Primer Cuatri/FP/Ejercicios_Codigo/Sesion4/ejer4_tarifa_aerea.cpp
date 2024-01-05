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
    bool UMBRAL_KM;
    double km;

    cout << "Este programa calcula el precio final de un vuelo convencional.\n\n";

    cout <<"Introduce la distancia a su destino(en km):";
    cin >>km;

    UMBRAL_KM=km>=300;
    tarifa_variable=(km-300)*0.1;

    if(UMBRAL_KM)
        tarifa_final=tarifa_base + tarifa_variable;
    else
        tarifa_final=tarifa_base;

    cout << "El precio final es: " << tarifa_final << endl;
}


