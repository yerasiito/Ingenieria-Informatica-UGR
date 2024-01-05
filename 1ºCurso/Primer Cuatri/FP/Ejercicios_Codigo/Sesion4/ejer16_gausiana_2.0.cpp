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

double x,media,desviacion,minim,maxim, incremento;
const double PI = 6 * asin(0.5);

int main(){

    cout <<"ESTE PROGRAMA CALCULA LA GAUSSIANA\n";
    cout <<"----------------------------------\n\n";

    cout <<"Introduce la Media: ";
    cin >> media;

    do{
        cout <<"\nIntroduce la Desviacion: ";
        cin >> desviacion;
    }while(desviacion<0);

    cout <<"\nIntroduce el valor Minimo de abcisa: ";
    cin >> minim;
    cout <<"\nIntroduce el valor Maximo de abcisa: ";
    cin >> maxim;
    cout <<"\nIntroduce el Incremento: ";
    cin >> incremento;

    cout << "\n        SOLUCIONES\n";
    cout << "       ------------" << endl << endl;
    while(minim<=maxim){
    x = (1/(desviacion*sqrt(2*PI)))*exp(-0.5*((minim - media)/desviacion)*((minim - media)/desviacion));
    cout <<"Gaussiana(" << minim << ") es " << x << endl;
    minim = minim + incremento;
    }
}
