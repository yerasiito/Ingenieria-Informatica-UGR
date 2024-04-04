#include <omp.h>
#include <stdio.h>

int main(){
    int suma = 0;
    #pragma omp parallel
    {
        printf("Hebra: %i\n", omp_get_thread_num());
        #pragma omp critical
        suma++;
    }

    printf("Suma: %i\n", suma);
    return 0;

}
