//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

#include <iostream>

using namespace std;

int main(){
   int min;
   int max;
   int k;
   int divisor;
   double tope;

   divisor = 0;
   k = 0;
   max = 0;

//Entrada de Datos...

   cout << "Introduce un numero minimo: ";
   cin >> min;

   cout << "Introduce un numero maximo: ";
   while(max<min)
      cin >> max;

   cout <<"Introduce el limite de divisores: ";
   while(k<1)
      cin >> k;

//Cómputo...

   for(int i=min;i<=max;i++){
      tope=i/2;
      for(int j=2;j<tope;j++){
         if(i%j==0)
            divisor++;
      }
   if(divisor>=k)
      cout << i << "  ";

   divisor=0;
   }

}


