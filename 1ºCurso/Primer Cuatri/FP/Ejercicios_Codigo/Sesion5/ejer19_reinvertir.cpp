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

int main(){

double C,I,tope_N;
double elev;
double N,M;

/*donde: C es el dinero original
I es el interes
M es el interes compuesto*/

   cout << "Introduce el capital: ";
   cin >> C;
   cout << "Introduce el interes: ";
   cin >> I;
   cout << "Introduce los anios a invetir: ";
   cin >> tope_N;

   for(N=0;N<tope_N;N++)
      {
      elev = pow((1 + I/100),N+1);
      M = C*elev;
      cout << "Capital obtenido transcurrido el anio numero " << N
           << " = " << M << endl;
   }

}


