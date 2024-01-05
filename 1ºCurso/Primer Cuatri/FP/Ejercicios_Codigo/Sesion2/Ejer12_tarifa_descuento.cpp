#include <iostream>
using namespace std;

double billete;
const double desc_puntos=0.96;           //4% descuento.
const double desc_vuelo_largo=0.98;      //2% descuento.
int main()
{
    cout << "Este programa calcula el precio de su billete aplicando un descuento.\n\n";

    cout << "Introduzca el precio de su billete:";
    cin >> billete;

    cout << "El precio de su billete es " << billete*desc_puntos << " " << billete*desc_vuelo_largo ;
}
