//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////


/*[Mayor nota media] (Examen Prácticas Noviembre 2019)
Se quiere calcular la máxima nota media de evaluación continua de un conjunto de
alumnos. Para ello, se anota en un fichero un número entero con el código del alumno
y las notas que ha conseguido. El número de notas puede variar de un alumno a otro,
por lo que se terminará la introducción de las notas con un -1. La entrada de datos
finaliza con el código de alumno 0.
Cree un programa que lea las notas desde la entrada por defecto, y calcule el alumno
con mayor nota media. Puede suponer que los datos de entrada son siempre correctos.
Por ejemplo, para el siguiente registro de entradas, el alumno con máxima nota es el
que tiene identificador 17 con una nota media de 9.5

11    8 7 6 -1
14    3 -1
7     9 9 8 7 -1
17    10 9 -1
8     9 9 -1
15    6 7 5 -1
5     8 -1
0

*/

#include <iostream>
#include <cmath>

using namespace std;

int main(){

   int identificador=1;
   int i;
   const int terminador_identificador=0;
   const int terminador_notas=-1;
   double notas;
   double acumulador;
   double media;
   double mejor_alumno=0;
   double mejor_nota=0;

   cout << "Introduce el identificador del alumno: ";
   cin >> identificador;

   while(identificador!= terminador_identificador){
      //inicializamos los datos
      acumulador=0.0;
      i=-1;
      notas=1.0;

      cout << "Introduce las notas del alumno: ";
      cin >> notas;

      while(notas!=terminador_notas){
         cin >> notas;
         acumulador+= notas;
         i++;
      }

      media = acumulador/i;
      cout << identificador << "\t" << media << endl;

      if(media>mejor_nota){
         mejor_nota=media;
         mejor_alumno=identificador;
      }
      cout << "Introduce el identificador del alumno: ";
      cin >> identificador;
   }
   cout << "----------------------------------------" << endl;
   cout << mejor_alumno << "\t" << mejor_nota << endl;
}





