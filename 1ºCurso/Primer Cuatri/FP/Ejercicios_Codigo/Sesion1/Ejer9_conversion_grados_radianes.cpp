#include <iostream>
#include <cmath>
double g;                           //g son los grados.
const double PI=6*asin(0.5);        //Se calcula pi usando el arcoseno ya que pi/6=arcsen(0.5), despejando queda pi=6*arcsen(0.5)
int main()
{
    cout << "Este programa convierte los grados en radianes.\n\n";

    cout << "Introduzca los grados(dos numeros enteros):";
    cin >> g;

    cout <<"\n   |" << g << " grados son " << g*(PI/180) << " radianes \n" ;
}
