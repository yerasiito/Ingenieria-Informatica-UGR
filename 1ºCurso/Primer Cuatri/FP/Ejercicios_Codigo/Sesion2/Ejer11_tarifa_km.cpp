#include <iostream>
using namespace std;

const double tarifa_fija=150;
double km;

int main()
{
    cout << "Este programa calcula el precio final de un vuelo convencional.\n\n";

    cout <<"Introduce la distancia a su destino(en km):";
    cin >>km;

    cout <<"El precio de su vuelo es de " <<tarifa_fija+km*0.10 << " euros";
}
