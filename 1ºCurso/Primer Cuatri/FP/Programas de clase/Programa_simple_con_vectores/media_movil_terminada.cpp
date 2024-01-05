//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

//media movil

  /* Un ejemplo de ejecución, con N valiendo 5, es:
  *     1 2 3 4 5 6 7 8 9 -300
  *     3 4 5 6 7 -300
  * donde la primera línea es la entrada y la segunda la salida.
  *
  * Otra ejemplo, ahora con N valiendo 3, es:
  *     -0.04 -0.05 -0.09 -0.06 -0.07 -0.01 0.09 0.07 0.02 0.12 0.15 -300
  *     -0.06 -0.0666667 -0.0733333 -0.0466667 0.00333333 0.05 0.06 0.07 0.0966667 -300
  *
  */

#include <iostream>
using namespace std;

int main(){
   const int MAX_DATOS = 1000;
   const double TERMINADOR = -273.15;
   double v[MAX_DATOS];
   double datos = 0;
   int N;
   int util = 0;
   double suma = 0;
   double media[MAX_DATOS];

   cin >> datos;
   while(datos > TERMINADOR){
      cin >> datos;
      v[util] = datos;
      util++;
   }

   cout << "Introduce el N: ";
   cin >> N;

   //Computo

   int iter;

   for(iter = 0; N + iter < util; iter++){
      for(int i = iter; i < N + iter; i++)
         suma += v[i];

      media[iter] = suma / N;
      suma = 0;
   }

   media[iter] = datos;

   //Salida de Datos

   for(int i=0; i <= iter ; i++)
      cout << media[i] << " ";
}




