/*
Ejercicio 4.
Modificación del ejercicio 3 implementando llamadas waitpid().

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

	// espera a que acaben
	for (int i = 0; i < num_procesos; i++){
		if (waitpid(pid[i], 0, 0) > 0){
			printf("\tAcaba de finalizar mi hijo con %d\n", pid[i]);
			printf("\tSolo me quedan %d hijos vivos\n", num_procesos - i);
		}
	}

	return 0;
}
