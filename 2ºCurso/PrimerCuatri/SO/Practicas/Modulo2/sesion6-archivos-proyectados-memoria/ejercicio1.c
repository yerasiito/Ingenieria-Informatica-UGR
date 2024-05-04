/*
	Implementa un programa que admita t argumentos.
	El primer argumento será una orden de Linux.
	El segundo, uno de los siguientes caracteres “<” o “>”
	El tercero el nombre de un archivo (que puede existir o no).

	El programa ejecutará la orden que se especifica como argumento primero e implementará la redirección especificada por el segundo argumento hacia el archivo indicado en el tercer argumento.
	Por ejemplo, si deseamos redireccionar la entrada estándar de sort desde un archivo temporal, ejecutaríamos:
	$> ./mi_programa sort “<” temporal
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main (int argc, char *argv[]){

	// Comprueba que los parámetros son correctos
	if (argc != 4){
		printf("Error en el nº parámetros. Formato: ./ejercicio1 <programa> <caracter> <archivo>\n");
		exit(-1);
	};

	char *programa = argv[1],
		 *archivo = argv[3];

	int fd;

	// Redirecciona la salida o entrada dependiendo del segundo parámetro recibido
	if (strcmp(argv[2], "<") == 0){

		// Redirección de entrada
		fd = open(archivo, O_RDONLY);
		close(STDIN_FILENO);
		if (fcntl(fd, F_DUPFD, STDIN_FILENO) == -1)
			perror("Error en fcntl\n");
	
	}else if (strcmp(argv[2],">") == 0){

		// Redirección de salida
		fd = open(archivo, O_CREAT|O_WRONLY);
		close(STDOUT_FILENO);
		if (fcntl(fd, F_DUPFD, STDOUT_FILENO) == -1)
			perror("Error en fcntl\n");
	
	}else{
		printf("El segundo parámetro debe ser \"<\" ó \">\"\n");
		exit(-1);
	}

	// Ejecuta el comando
	if ( (execlp(programa, "", NULL) < 0)){
		perror("Error en execlp\n");
		exit(-1);
	}

	// Cierra el fichero
	close(fd);

	return 0;
}