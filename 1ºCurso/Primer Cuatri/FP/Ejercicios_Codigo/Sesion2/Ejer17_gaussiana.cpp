#include <iostream>
#include <cmath>
using namespace std;

double x,esperanza,desviacion,abcs_x;
const double PI = 6 * asin(0.5);

int main(){

    cout <<"Este progama calcula una gausiana\n\n";

    cout <<"Introduce la esperanza: ";
    cin >> esperanza;
    cout <<"\nIntroduce la desviacion: ";
    cin >> desviacion;
    cout <<"\nIntroduce el valor de abcisa: ";
    cin >> abcs_x;

    x = (1/(desviacion*sqrt(2*PI)))*exp(-0.5*((abcs_x - esperanza)/desviacion)*((abcs_x - esperanza)/desviacion));
    cout << x;
}

