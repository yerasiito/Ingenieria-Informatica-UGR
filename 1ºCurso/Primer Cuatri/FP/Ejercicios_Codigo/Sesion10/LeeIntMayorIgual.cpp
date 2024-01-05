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

int LeeIntMayorIgual(int min) {
   int a_leer;
   do
      cin >> a_leer;
   while (min > a_leer);

   return a_leer;
}

int LeeIntRango(int min,int max){
   int dato = min -1;   //Para que siempre esté fuera del intervalo y entre en el bucle

   while(min > dato || max < dato)
      cin >> dato;

   return dato;

}

int main(){

   long min, max, dato;

   cout << "\nIntroduzca el valor mínimo y el máximo"
        << "\nA continuación introduzca enteros en el rango anterior\n";

   cin >> min;

   max = LeeIntMayorIgual(min);

   dato = LeeIntRango(min,max);

   cout << dato << " está en el intervalo [" << min << "," << max << "]" << endl;
}
