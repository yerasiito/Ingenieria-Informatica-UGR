//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

//Introduce las temperaturas e imprime su frecuencia

#include <iostream>
#include <cmath>

using namespace std;

int main(){
   const double TERMINADOR = -273.15;
   const int CENTINELA = 0;
   double temperatura;
   double frecuencia = 1;        //Al menos se van a repetir 1 vez
   double copia;

   cin >> temperatura;
   copia = temperatura;

   while(temperatura > TERMINADOR){
      copia = temperatura;
      cin >> temperatura;

      while(temperatura == copia){
         frecuencia++;
         cin >> temperatura;
      }
      if(temperatura != copia){
         cout << frecuencia << " " << copia << " ";
         frecuencia=1;
      if(temperatura < TERMINADOR)
         cout << " " << CENTINELA << endl;
      }
   }

   return 0;

}

