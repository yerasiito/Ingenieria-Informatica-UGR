/**
   @file Cálculo de la sucesión de Fibonacci
*/

   
#include <iostream>
using namespace std;
#include <ctime>

#include<chrono>
using namespace chrono;


high_resolution_clock::time_point tantes, tdespues;
duration<double> transcurrido;

/**
   @brief Calcula el término n-ésimo de la sucesión de Fibonacci.

   @param n: número de orden del término buscado. n >= 1.

   @return: término n-ésimo de la sucesión de Fibonacci.
*/
int fibo(int n)
{
  if (n < 2)
    return 1;
  else
    return fibo(n-1) + fibo(n-2);
}


int main(int argc, char * argv[])
{

  int n;
  int f;
 
  //cout << "¿Número del término: ";
  n = atoi(argv[1]);

  tantes = high_resolution_clock::now(); // Tiempo de inicio

  f = fibo(n);

  tdespues = high_resolution_clock::now();    // Anotamos el tiempo de finalización

  transcurrido = duration_cast<duration<double>>(tdespues - tantes); //Calculamos la diferencia

  //cout << "El término " << n << "-ésimo es: " << f << endl;

  //Mostrar resultados
  cout << n << "\t" << transcurrido.count() << endl;

  return 0;
}
