// -----------------------------------------------------------------------------
// Sistemas concurrentes y Distribuidos.
// Seminario 1. Programación Multihebra y Semáforos.
//
// Ejemplo 9 (ejemplo9.cpp)
// Calculo concurrente de una integral. Plantilla para completar.
//
// Historial:
// Creado en Abril de 2017
// -----------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <chrono>  // incluye now, time\_point, duration
#include <future>
#include <vector>
#include <cmath>

using namespace std ;
using namespace std::chrono;

const long m  = 1024l*1024l*1024l, // número de muestras (del orden de mil millones)
           n  = 4  ;               // número de hebras concurrentes (divisor de 'm')


// -----------------------------------------------------------------------------
// evalua la función $f$ a integrar ($f(x)=4/(1+x^2)$)
double f( double x )
{
  return 4.0/(1.0+x*x) ;
}
// -----------------------------------------------------------------------------
// calcula la integral de forma secuencial, devuelve resultado:
double calcular_integral_secuencial(  )
{
   double suma = 0.0 ;                        // inicializar suma
   for( long j = 0 ; j < m ; j++ )            // para cada $j$ entre $0$ y $m-1$:
   {  const double xj = double(j+0.5)/m ;     //      calcular $x_j$
      suma += f( xj );                        //      añadir $f(x_j)$ a la suma actual
   }
   return suma/m ;                            // devolver valor promedio de $f$
}

// -----------------------------------------------------------------------------
// función que ejecuta cada hebra: recibe $i$ ==índice de la hebra, ($0\leq i<n$)
double funcion_hebra( long ih )
{
   double sumap = 0.0;				//incializar suma parcial
   double b = m/n; 				//bloque a ejecutar por cada hebra
   for(int j = ih*b; j < (ih+1)*b-1; 	j++){ 	//recorrer m en bloques para cada hebra
   	sumap += f((j+double(0.5))/m);	//calcular x_j
   }						
   return sumap;				//devuelver la suma parcial
}

// -----------------------------------------------------------------------------
// calculo de la integral de forma concurrente
double calcular_integral_concurrente( )
{
   double suma = 0.0;				//incializar suma total
   future<double> futuros[n]; 		//vector de futuros que contiene las hebras
   
   for(int i = 0; i < n; i++)			//lanzar las hebras
      futuros[i] = async( launch::async, funcion_hebra, i);
  
   for(int i = 0; i < n; i++)			//Sumar los valores parciales
      suma += futuros[i].get();
     
  return suma/m;				//devolver valor promedio de f
}
// -----------------------------------------------------------------------------

int main()
{

  time_point<steady_clock> inicio_sec  = steady_clock::now() ;
  const double             result_sec  = calcular_integral_secuencial(  );
  time_point<steady_clock> fin_sec     = steady_clock::now() ;
  double x = sin(0.4567);
  time_point<steady_clock> inicio_conc = steady_clock::now() ;
  const double             result_conc = calcular_integral_concurrente(  );
  time_point<steady_clock> fin_conc    = steady_clock::now() ;
  duration<float,milli>    tiempo_sec  = fin_sec  - inicio_sec ,
                           tiempo_conc = fin_conc - inicio_conc ;
  const float              porc        = 100.0*tiempo_conc.count()/tiempo_sec.count() ;


  constexpr double pi = 3.14159265358979323846l ;

  cout << "Número de muestras (m)   : " << m << endl
       << "Número de hebras (n)     : " << n << endl
       << setprecision(18)
       << "Valor de PI              : " << pi << endl
       << "Resultado secuencial     : " << result_sec  << endl
       << "Resultado concurrente    : " << result_conc << endl
       << setprecision(5)
       << "Tiempo secuencial        : " << tiempo_sec.count()  << " milisegundos. " << endl
       << "Tiempo concurrente       : " << tiempo_conc.count() << " milisegundos. " << endl
       << setprecision(4)
       << "Porcentaje t.conc/t.sec. : " << porc << "%" << endl;
}
