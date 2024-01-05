//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

   /* [Aproximación de PI por Gregory-Leibniz] En el siglo XVII el matemático alemán Gottfried
   Leibniz y el matemático escocés James Gregory introdujeron una forma de calcular
   PI a través de una serie, es decir, de una suma de términos:

   pi/4 = pow(-1,i)/(2*n +1)

   Esta es una serie infinita, pues realiza la suma de infinitos términos. Como en Programación
   no podemos realizar un número infinito de operaciones, habrá que parar en
   un índice dado, llamémosle tope, obteniendo por tanto una aproximación al valor de
   PI. Usaremos el símbolo "aprox" para denotar esta aproximación:

   pi/4 aprox pow(-1,n)/(2*n +1) ... + pow(-1,tope)/(2*tope +1)

   Construya un programa que lea el valor tope obligando a que esté entre 1 y cien mil,
   calcule la aproximación de PI mediante la anterior serie e imprima el resultado en
   pantalla.
   Resuelva este problema de tres formas distintas (no hace falta que entregue tres ejercicios:
   baste con que incluya las dos primeras soluciones dentro de un comentario):

   a) Use la función pow (potencia) de cmath para implementar (-1)^n

   b) Para cada valor de n, calcule (-1)^n con un bucle, tal y como hizo en el ejercicio
   de la potencia (problema 18 [Factorial y Potencia] )

   c) De una forma más eficiente que las anteriores. Por ejemplo, observe que el valor
   de (-1)^n es 1 para los valores pares de i y -1 para los impares

   Recuerde que, para visualizar 15 cifras decimales, por ejemplo, debe incluir la sentencia
   cout.precision(15); antes de realizar la salida en pantalla.

   Ejemplo de entrada: 1000 -- Salida correcta: 3.14259165433954
   Ejemplo de entrada: 100000 -- Salida correcta: 3.14160265348972
   */
#include <iostream>
#include <cmath>

using namespace std;

int main(){


   int tope;
   int n;
   double sumando, suma;
   double pi_aprox;
   do
   {
     cout << "Introduce el tope de calculo: ";
     cin >>tope;
   }
    while(tope<0 || tope>1e+5);

   /* //Metodo (a):
   suma = 0;
   n = 0;

   while(n<=tope){

      sumando = pow(-1,n)/(2*n +1);
      // o directamente suma = suma + pow(-1, n) / (2*n + 1);
      suma = suma + sumando;
      n++;
   }

   pi_aprox = 4 * suma;             //Es porque se iguala a pi/4 por lo que para obtener pi, se le multiplica por 4
   cout.precision(15);
   cout << pi_aprox << endl;

   return 0;
   */


   /* //METODO (B)
   suma = 0;
   int signo = 1;
   const int CAMBIO_SIGNO = -1;
   for(n=0;n<tope;n++){
      sumando = signo/(2.0*n +1);
      suma = suma + sumando;
      signo= signo * CAMBIO_SIGNO;
   }
   pi_aprox = 4*suma;                //Es porque se iguala a pi/4 por lo que para obtener pi, se le multiplica por 4
   cout.precision(15);
   cout << pi_aprox << endl;

   return 0;
   */
   //METODO (c)
   suma = 0;
   int signo;

   for(n=0;n<tope;n++){
      if(n%2==0)
         signo=1;
      else
         signo=-1;

      sumando = signo/(2.0*n +1);
      suma = suma + sumando;
   }
   pi_aprox = 4*suma;                //Es porque se iguala a pi/4 por lo que para obtener pi, se le multiplica por 4
   cout.precision(15);
   cout << pi_aprox << endl;

   return 0;
}







