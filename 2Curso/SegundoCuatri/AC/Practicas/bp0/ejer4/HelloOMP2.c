/**
 * 
 Compilar con gcc –O2 –fopenmp HelloOMP.c –o HelloOMP
 * 
 */

#include <stdio.h>
#include <omp.h>

int main(void) {

#pragma omp parallel
  printf("(%d:!!!Hello)", 
           omp_get_thread_num());

  printf("(%d:world!!!)", 
           omp_get_thread_num());

  printf("\n");

return(0);

}
