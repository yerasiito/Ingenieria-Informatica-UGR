#include <iostream>
#include <cmath>

using namespace std;

int main(){

    cout << "Este programa aproxima decimales con la funcion trunc\n\n";

    double r,n;
    double dsplz, num_redondeado;

    cout << "Introduce el numero a redondear: ";
    cin >> r;
    cout << "\nIntroduce el numero de decimales a truncar: ";
    cin >> n;

    dsplz = pow(10,n);
    num_redondeado = trunc(r*dsplz)/dsplz;

    cout << num_redondeado;

    //igual que en el ejercicio 10, no compila en C pero si en dev C++...
}
