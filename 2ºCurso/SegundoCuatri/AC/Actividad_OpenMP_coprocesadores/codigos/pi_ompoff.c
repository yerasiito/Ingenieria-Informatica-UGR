/**
 * 
PI paralelo con integración numérica.
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
/**
 * @file  pi.c 
 * @brief PI paralelo con integración numérica, área de rectángulos
 * @author Yeray Lopez Ramirez
 *  
 * **Compilación**
 * @code
 *  sbatch –pac4 –Aac --wrap “nvc -O2 -openmp -mp=gpu pi_ompoff.c -o pi_ompoff_GPU”
 *  sbatch –pac4 –Aac --wrap “nvc -O2 -openmp -mp=multicore pi_ompoff.c -o pi_ompoff_CPU”
 * @endcode
 * 
 *  **Ejecución**
 * ~~~~~~~~~~~~~~~~~~~~~
 * srun -pac4 -Aac pi_ompoff 0
 * ~~~~~~~~~~~~~~~~~~~~~
 * 
*/
int main(int argc, char **argv)
{
  register double width;
  double sum;
  double PI25DT = 3.141592653589793238462643;
  double t0,t1,t2,t3;
  register long intervals,i;
   
  //Los procesos calculan PI en paralelo
  if (argc<2) {printf("Falta número de intevalos");exit(-1);}
  intervals=atol(argv[1]);
  if (intervals<1) {intervals=10000000; printf("Intervalos=%d.\n",intervals);}
  width = 1.0 / intervals;
  sum = 0;
  
  printf("Hay %i dispositivos de GPU.\n", omp_get_num_devices());
  t0 = omp_get_wtime();
  #pragma omp target enter data map(to: intervals,width) //transferencia de datos a la gpu
  t1 = omp_get_wtime();

  #pragma omp target teams distribute parallel for reduction(+:sum)
  for (i=0; i<intervals; i++) {
    register double x = (i + 0.5) * width;
    sum += 4.0 / (1.0 + x * x);
  }
  sum *= width;
  t2 = omp_get_wtime();
  #pragma omp target exit data map(delete: intervals, width)
  t3 = omp_get_wtime();

  printf("Tiempo de transferencia de datos hacia la GPU: %8.6fs.\n", t1-t0);
  printf("Intervalos:%d \tPI:%26.24f. \tError:%26.24f.\n", intervals, sum, fabs(sum - PI25DT));
  printf("Tiempo de cálculo: %8.6fs.\n", t2-t1);
  printf("Tiempo de transferencia de datos desde la GPU: %8.6fs.\n", t2-t1);
  printf("Tiempo total: %8.6fs\n", t3-t0);
  return(0);
}
