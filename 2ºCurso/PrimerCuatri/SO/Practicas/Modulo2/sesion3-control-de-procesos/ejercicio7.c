/*
	Ejercicio 7.
	Escribe un programa que acepte como argumentos el nombre de un programa, sus argumentos si los tiene,
	y opcionalmente la cadena "bg".
	
	Nuestro programa deberá ejecutar el programa pasado como primer	argumento en foreground
	si no se especifica la cadena "bg" y en background en caso contrario.
	
	Si el programa tiene argumentos hay que ejecutarlo con éstos.
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char **argv){
	if (argc < 2){
		printf("\nNº parámetros incorrecto\n");
		exit(-1);
	}

	bool background = false;
	int num_params = argc;
	char *nombre_programa = argv[1];
	char parametros[100];
	pid_t pid;

	// Comprueba si el último parámetro recibido es bg
	if (strcmp(argv[argc-1], "bg") == 0){
		background = true;
		num_params--;
	}

	// Extrae los parámetros
	for (int i = 2; i < num_params; i++){
		strcat(parametros, argv[i]);
		strcat(parametros, " ");
	}

	// Ejecución
	if (background){
		printf("Ejecutando %s en background\n", nombre_programa);

		if ((pid = fork()) < 0){
			printf("\nError en fork\n");
			exit(-1);
		}else if (pid == 0){
			// Si es el hijo ejecuta
			if (execlp(nombre_programa, parametros, parametros, NULL) < 0){
				printf("\nError en execl\n");
				exit(-1);
			}
		}

	}else{
		printf("Ejecutando %s en foreground\n", nombre_programa);

		if (execlp(nombre_programa, parametros, parametros, NULL) < 0){
			printf("\nError en execl\n");
			exit(-1);
		}
	}

	return 0;
}
