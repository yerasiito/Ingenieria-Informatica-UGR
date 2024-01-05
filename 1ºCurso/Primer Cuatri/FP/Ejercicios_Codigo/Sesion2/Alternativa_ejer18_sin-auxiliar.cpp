#include <iostream>
#include <cmath>
using namespace std;

int main(){

    double x,y,z;

    cout << "Este programa intercambia el valor de tres variables.\n\n";

    cout <<"Introduce la variable x:";
    cin >> x;
    cout <<"Introduce la variable y: ";
    cin >> y;
    cout <<"Introduce la variable z: ";
    cin >> z;

    x = x + y + z; //aplicando un "truquillo" de restas y sumas, podemos intercambiar las variables sin añadir auxiliares
    y = x - y - z;
    z = x - y - z;
    x = x - y -z;


    cout << " " << x << " " << y << " " << z;



}
