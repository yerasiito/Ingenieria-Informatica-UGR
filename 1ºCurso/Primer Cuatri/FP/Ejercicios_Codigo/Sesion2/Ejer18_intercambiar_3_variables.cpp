#include <iostream>
#include <cmath>
using namespace std;

int main(){

    double x,y,z;
    double contenedor;

    cout << "Este programa intercambia el valor de tres variables.\n\n";

    cout <<"Introduce la variable x:";
    cin >> x;
    cout <<"Introduce la variable y: ";
    cin >> y;
    cout <<"Introduce la variable z: ";
    cin >> z;

    contenedor = x + y + z;
    x = contenedor - x - y;
    y = contenedor - y - z;
    z = contenedor - x - y;

    cout << " " << x << " " << y << " " << z;

}

