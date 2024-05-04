/*
Ejercicio 5.
Modificación del ejercicio 4 para que el proceso padre espera primero 
a los hijos impares y después a los hijos pares.

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
			// padre
			continue;
		};
	}
	
	int procesos_acabados = 0;

	// espera a que acaben los impares
	for (int i = 1; i < num_procesos; i += 2){
		if (waitpid(pid[i], 0, 0) > 0){
			printf("\tAcaba de finalizar mi hijo con %d\n", pid[i]);
			printf("\tSolo me quedan %d hijos vivos\n", num_procesos - procesos_acabados);
			procesos_acabados++;
		}
	}

	// espera a que acaben los pares
	for (int i = 0; i < num_procesos; i += 2){
		if (waitpid(pid[i], 0, 0) > 0){
			printf("\tAcaba de finalizar mi hijo con %d\n", pid[i]);
			printf("\tSolo me quedan %d hijos vivos\n", num_procesos - procesos_acabados);
			procesos_acabados++;
		}
	}

	return 0;
}
