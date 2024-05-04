/*
	Programa ilustrativo del uso de pipes y la redirección de entrada y salida estándar: "ls | sort"
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

	pipe(fd);	// Llamada al sistema para crear un pipe

	if ( (PID = fork()) < 0){
		perror("fork");
		exit(-1);
	}

	if (PID == 0){	// ls. Proceso hijo
		// Establece la dirección del flujo de datos en el cauce cerrando
		// el descriptor de lectura en el proceso hijo
		close(fd[0]);

		// Redirige la salida estándar para enviar datos al cauce
		close(STDOUT_FILENO);	// cierra salida estándar en el hijo

		// Duplica el descriptor de escritura en cauce en el descriptor
		// correspondiente a la salida estándar (stdout)
		dup(fd[1]);
		execlp("ls", "ls", NULL);
	
	}else{	// sort. Proceso padre
		// Establecer la dirección del flujo de datos en el cauce cerrando el 
		// descriptor de escritura del proceso padre
		close(fd[1]);

		// Redirige la entrada estándar para tomar los datos del cauce
		// Cerrar la entrada estándar del proceso padre
		close(STDIN_FILENO);

		// Duplica el descriptor de lectura de cauce en el descriptor
		// correspondiente a la entrada estándar (stdin)
		dup(fd[0]);

		execlp("sort", "sort", NULL);
	}

	return 0;
}