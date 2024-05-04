/*
	Reescribir el ejercicio 1 para que implemente un encauzamiento de dos órdenes pero utilizando fcntl.
	Admitirá 3 argumentos:
		1) Orden de linux
		2) Carácter "|"
		3) Orden de linux

	El programa debe redireccionar la salida de la orden indicada por el primer argumento hacia el cauce, 
	y redireccionar la entrada estándar de la segunda orden desde el cauce.
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

int main (int argc, char *argv[]){

	// Comprueba que los parámetros son correctos
	if (argc != 4){
		printf("Error en el nº parámetros. Formato: ./ejercicio2 <programa> <|> <programa>\n");
		exit(-1);
	};

	char *programa = argv[1],
		 *cauce = argv[2],
		 *programa2 = argv[3];

	pid_t PID;;
	int fd[2];

	if (strcmp(cauce, "|") == 0){
		pipe(fd);			// llamada al sistema para crear un cauce sin nombre

		if ( (PID = fork()) < 0){
			perror("Error en fork\n");
			exit(-1);
		}

		if (PID == 0){		// proceso hijo
			// Cierra el descriptor de lectura (el proceso hijo será escritor)
			close(fd[0]);
			close(STDOUT_FILENO);

			// Redirecciona la salida del programa
			if (fcntl(fd[1], F_DUPFD, STDOUT_FILENO) == -1){
				perror("Fallo en fcntl del hijo");
				exit(-1);
			}

			execlp(programa, programa, NULL);
		
		}else{				// proceso padre
			// Cierra el descriptor de escritura (el proceso hijo es escritor)
			close(fd[1]);
			close(STDIN_FILENO);

			// Redirecciona la entrada del programa
			if(fcntl(fd[0], F_DUPFD, STDIN_FILENO) == -1){
				perror("Fallo en fcntl del padre");
				exit(-1);
			}

			execlp(programa2, programa2, NULL);
		}
	}else{
		perror("El segundo parámetro tiene que ser el carácter de cauce entre comillas: \"|\" \n");
		exit(-1);
	}

	return 0;
}
