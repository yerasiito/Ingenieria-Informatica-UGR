//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
////////////////////////////////////////////////////////////////////////+

   /*[Aproximación de PI por Madhava sin usar pow] En el siglo XIV el matemático indio
   Madhava of Sangamagrama calculó el arco tangente a través de un desarrollo de
   Taylor (este tipo de desarrollos se ve en la asignatura de Cálculo)

   arctan(x) = ((-1)^i·x^(2i+1))/(2i+1)

   Usando como x el valor 1, obtenemos la serie de Leibniz vista en el ejercicio 26:

   arctan(x)= pi/4 = ((-1)^i)/(2i+1)

   Usando como x el valor 1/sqrt(3), obtenemos:

   arctan(1/sqrt(3))= pi/6 = ((-1)^i·(1/sqrt(3))^(2i+1))/(2i+1)

   Por lo tanto, podemos usar la siguiente aproximación:

   pi/6 = ((-1)^i·(1/sqrt(3))^(2i+1))/(2i+1)

      Construya un programa que lea el valor tope obligando a que esté entre 1 y cien
   mil, calcule la aproximación de PI mediante la anterior serie e imprima el resultado en
   pantalla.
   Importante: En la implementación de esta solución NO puede usar la función pow ni
   ningún condicional if. Se le pide expresamente que para el cómputo de cada término,
   intente aprovechar los cómputos realizados en la iteración anterior.
   Ejemplo de entrada: 1000 -- Salida correcta: 3.14159265358979
   Ejemplo de entrada: 100000 -- Salida correcta: 3.14159265358979
   */

#include <iostream>
#include <cmath>

using namespace std;

int main(){
   int tope;
   int i=0;
   int signo = 1;
   double numerador,denominador;
   double serie = 0;
   double pi_aprox;
   const int CAMBIO_SIGNO=-1;
   const double raiz= (1/sqrt(3));

   do{
   cout << "Introduce el tope: ";
   cin >> tope;
   }
   while(tope<0 || tope>1e+5);

   numerador= raiz;
   denominador=1.0;

   for(i=0;i<=tope;i++){

         serie += signo*numerador/denominador;

         signo *= CAMBIO_SIGNO;
         denominador+= 2;
         numerador*=raiz*raiz;
   }
   pi_aprox= 6*serie;

   cout.precision(15);
   cout << "La aproximacion de PI por madhava es: " << pi_aprox << endl;
}


