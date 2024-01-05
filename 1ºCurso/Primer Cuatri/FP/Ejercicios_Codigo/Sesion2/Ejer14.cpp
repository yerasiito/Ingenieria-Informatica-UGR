#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    //...
    cout <<"\n  Ejercicio 14.4\n";
    cout <<"  Este programa calcula el valor de PI\n\n";  /**Se calcula pi usando el arcoseno ya que pi/6=arcsen(0.5),
                                                        *despejando queda pi=6*arcsen(0.5)*/
    const double PI = 6*asin(0.5);

    cout << "  " << PI << "\n\n";

    //--------------------------------------------------------------------------------------------------------------------------------
    cout <<"\n  Ejercicio 14.3\n";
    cout << "  Este programa calcula el area y la longitud de una circunferencia.\n\n";

    double radio_cir;

    cout <<"   Introduce el radio de la circunferencia: ";
    cin >> radio_cir;

    cout <<"\n  -El area de la circunferencia es: " << PI*radio_cir*radio_cir <<" cm cuadrados.";
    cout <<"\n  -La longitud de la circunferencia es: " << 2*PI*radio_cir <<" cm.\n";

    //--------------------------------------------------------------------------------------------------------------------------------
    cout <<"\n  Ejercicio 14.9\n";
    cout << "  Este programa convierte los grados en radianes.\n\n";

    double g;                           //g son los grados.

    cout << "  Introduzca los grados(dos numeros enteros):";
    cin >> g;

    cout <<"\n   |" << g << " grados son " << g*(PI/180) << " radianes \n" ;

    //--------------------------------------------------------------------------------------------------------------------------------
    cout <<"\n  Ejercicio 14.11\n";
    cout << "  Este programa calcula el precio final de un vuelo convencional.\n\n";

    const double tarifa_fija=150;
    const double tarifa_variable=0.10;
    double km;

    cout <<"  Introduce la distancia a su destino(en km):";
    cin >>km;

    cout <<"\n  El precio de su vuelo es de " <<tarifa_fija + km*tarifa_variable << " euros \n";

    //--------------------------------------------------------------------------------------------------------------------------------
    cout <<"\n  Ejercicio 14.12\n";
    cout << "  Este programa calcula el precio de su billete aplicando dos descuentos.\n\n";

    double billete;
    const double desc_puntos=0.96;           //4% descuento.
    const double desc_vuelo_largo=0.98;      //2% descuento.

    cout << "  Introduzca el precio de su billete:";
    cin >> billete;

    cout << "\n  El precio de su billete es " << billete*desc_puntos << " euros y " << billete*desc_vuelo_largo << " euros\n" ;
}


