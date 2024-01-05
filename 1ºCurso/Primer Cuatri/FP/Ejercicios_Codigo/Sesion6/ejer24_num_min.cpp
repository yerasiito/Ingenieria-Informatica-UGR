//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

/*
24. [Mínimo de varios valores] Realice un programa que lea enteros desde teclado y calcule
cuántos se han introducido y cual es el mínimo de dichos valores (pueden ser
positivos o negativos). Se dejará de leer datos cuando el usuario introduzca el valor 0.
Realice la lectura de los enteros dentro de un bucle sobre una única variable llamada
dato. Es importante controlar los casos extremos, como por ejemplo, que el primer
valor leído fuese ya el terminador de entrada (en este caso, el cero).
Ejemplo de entrada: 0
   Salida correcta: Introducidos: 0. Mínimo: 0
Ejemplo de entrada: 1 3 -1 2 0
   Salida correcta: Introducidos: 4. Mínimo: -1
Ejemplo de entrada: 1 3 1 2 0
   Salida correcta: Introducidos: 4. Mínimo: 1
Una vez hecho el programa, indique qué cambios debería realizar si los valores a leer
son enteros negativos y el final de la entrada de datos lo marca la introducción de
cualquier valor positivo.
*/
#include <iostream>
#include <cmath>

using namespace std;

int main(){

   int dato, min_dato, i=-1;
   const int terminador = 0;

   cout << "Introduce una serie de numeros: ";
   cin >> dato;
   i++;
   min_dato = dato;
   do{
      cout << " ";
      cin >> dato;
      if(dato < min_dato && dato != 0)
         min_dato = dato;
      i++;
   }
   while(dato != terminador);

   cout << "--------------------------------------" << endl;
   cout << "\tEl numero mas pequenio es el " << min_dato << endl
        << "\t y hay " << i << " numeros" << endl;
}

