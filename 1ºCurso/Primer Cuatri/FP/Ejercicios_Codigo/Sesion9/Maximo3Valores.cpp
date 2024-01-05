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

int Max2(int uno,int otro){
   if(uno > otro)
      return uno;
   else
      return otro;
}

int Max3(int uno,int otro,int otro_mas){
   int maximo = Max2(uno,otro);
   if( maximo > otro_mas)
      return maximo;
   else
      return otro_mas;
}

int main(){
   int entero1,entero2,entero3;
   int maximo;

   cin >> entero1 >> entero2 >> entero3;

   maximo = Max2(entero1,entero2);
   maximo = Max3(entero1,entero2,entero3);

   cout << maximo << endl;
}

