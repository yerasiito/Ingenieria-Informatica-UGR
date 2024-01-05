//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

//Este programa calcula si un numero es narcicista o no.

#include <iostream>
#include <cmath>

using namespace std;

int main(){
   long int num_digitos = 0;
   long int suma = 0;
   long int n, digito;
   long int guardado;
   cout << "Introduce un entero: ";
   cin >> n;

//computo...

   guardado = n;

   while(n>0){
      n = n/10;
      num_digitos++;
   }

   n=guardado;     //restauramos n

   for(int i=0;i<num_digitos;i++){
      digito = n%10;
      suma = suma + pow(digito,num_digitos);
      n = n / 10;
   }
   n=guardado;     //restauramos n

   if(suma==n)
      cout << "El numero es narcicista.";
   else
      cout << "El numero no es narcicista.";

}

