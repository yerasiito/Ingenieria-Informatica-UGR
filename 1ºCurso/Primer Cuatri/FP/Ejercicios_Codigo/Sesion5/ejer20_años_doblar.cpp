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

   double capital, interes;

   cout << "Introduce su capital: ";
   cin >> capital;
   cout << "Introduce el interes: ";
   cin >> interes;
   double anios=0;
   double tope_cap=(2*capital);

   do{
         capital = capital + capital*(interes/100);
         anios++;
   }
   while(capital<=tope_cap);

   cout << "\nPara doblar la cantidad inicial han de pasar " << anios << " anios" << endl;
   cout << "Al finalizar, se obtendra un total de " << capital << " euros" << endl;

}


