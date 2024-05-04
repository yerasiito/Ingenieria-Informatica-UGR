/*
	Lo mismo que ejercicio 3 pero con la llamada dup2.
*/

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]){
	int fd[2];
	pid_t PID;

	pipe(fd);	// crea un pipe

	if ( (PID = fork()) < 0){
		perror("\nError en fork");
		exit(-1);
	}

	if (PID == 0){	// ls
		// Cierra el descriptor de lectura en el proceso hijo
		close(fd[0]);

		// Duplicar el descriptor de escritura en cauce en el descriptor
		// correspondiente a la salida estándar (stdout), 
		// que hemos cerrado antes
		dup2(fd[1], STDOUT_FILENO);
		execlp("ls", "ls", NULL);
	
	}else{			// sort. Proceso padre porque PID != 0
		// Cierra el descriptor de escritura en el padre
		close(fd[1]);

		// Duplicar el descriptor de lectura de cauce en el descriptor
		// correspondiente a la entrada estándar (stdin),
		// que hemos cerrado antes
		dup2(fd[0], STDIN_FILENO);
		execlp("sort", "sort", NULL);
	}

	return 0;
}