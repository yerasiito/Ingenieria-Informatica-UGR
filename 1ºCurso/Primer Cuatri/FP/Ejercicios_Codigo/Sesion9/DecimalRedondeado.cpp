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

double Redondeado(double numero,int cifra){
numero = round(numero * pow(10,cifra));
numero = numero / pow(10,cifra);
return numero;
}


int main(){
   double numero;
   int cifra;

   cin >> numero >> cifra;
   numero = Redondeado(numero,cifra);

   cout << "El numero redondeado es: "  << numero << endl;

   return 0;

}


