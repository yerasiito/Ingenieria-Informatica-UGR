//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

//Introduce la frecuencia y la temperatura e imprime las temperaturas en función de su frecuencia

#include <iostream>
#include <cmath>

using namespace std;

int main(){
   const int CENTINELA=0;
   const int TERMINADOR=-300;
   double frecuencia, temperatura;
   bool error;

   cin >> frecuencia;
   cin >> temperatura;

   while(frecuencia!=CENTINELA && error==false){

      for(int i=0; i<frecuencia; i++)
         cout << temperatura << " ";

      cin >> frecuencia;

      if(frecuencia!=trunc(frecuencia)){
         cout << "Error inesperado. Frecuencia decimal." << endl;
         error=true;
      }
      else if(frecuencia<0){
         cout << "Error inesperado. Frecuencia sin sentido." << endl;
         error=true;
      }
      else if(frecuencia!=CENTINELA)
         cin >> temperatura;
   }

   cout << TERMINADOR << " ";
}

