/*
Ejercicio 3.
Código para generar 20 procesos, donde cada uno imprima su PID y el del padre (PPID).

*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <wait.h>

int main(){
	const int num_procesos = 20;
	pid_t pid[num_procesos];

	for (int i = 0; i < num_procesos; i++){
		if ( (pid[i] = fork()) < 0){
			printf("\nError en fork\n");
			break;

		}else if (pid[i] == 0){
			// hijo
			printf("\nSoy el proceso %d hijo de %d\n", getpid(), getppid());
			break;
			
		}else{
			continue;
		};
	}

	return 0;
}

