#include <iostream>
#include <cmath>
double valor_inicial;
double valor_final;

int main()
 {
     cout <<"Este programa calcula la variacion porcentual de dos valores(inicial y final).\n\n";
    cout <<"Introduce el valor inicial: ";
    cin >> valor_inicial;
    cout <<"Introduce el valor final: ";
    cin >> valor_final;

    cout <<"\nLa variacion porcentual es de: " << abs(100*((valor_inicial - valor_final)/valor_inicial)) <<" %\n" ;
 }
