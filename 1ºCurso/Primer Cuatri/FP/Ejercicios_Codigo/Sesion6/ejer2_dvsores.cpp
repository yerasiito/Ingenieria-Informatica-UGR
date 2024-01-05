//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

/* 2. [Divisores] Recupere la solución del ejercicio 15 [Divisores de un entero] de la Relación
de Problemas II que puede encontrar en el siguiente enlace:
http://decsai.ugr.es/jccubero/FP/II_Divisores.cpp
Modifíquelo para separar los cómputos de las entradas y salidas de datos. Para ello,
se pide que cada vez que encuentre un divisor lo guarde en un vector divisores.
Una vez construido el vector, en un bucle aparte, debe imprimir sus componentes en
pantalla.
Ejemplo de entrada: 16 -- Salida correcta: 2, 4, 8
*/

#include <iostream>
using namespace std;

int main(){
   int entero, ultimo_divisor,divisor,util;
   const int LIMITE_DIVISORES=1000;
   int divisores[LIMITE_DIVISORES];

   cout << "Divisores de un entero\n\n";

//Entrada de datos...

   do{
      cout << "Introduce un numero entero mayor estricto que 0: ";
      cin >> entero;
   }while (entero <= 0);

//Cálculo de datos...

   ultimo_divisor = entero / 2;
   int i=0;

   for(divisor=2;divisor <= ultimo_divisor;divisor++){
      if(entero%divisor==0){
         divisores[i]= divisor;
         i++;
      }
   }
   util=i;

//Salida de datos...
   cout << "Los divisores son: ";
   for(int i=0;i<util;i++)
      cout << divisores[i] << " ";






}
