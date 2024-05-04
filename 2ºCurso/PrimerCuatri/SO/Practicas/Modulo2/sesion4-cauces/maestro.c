/*
	Construir un programa que siga el esquema maestro-esclavo, existen varios procesos 
	trabajadores idénticos y un único proceso que reparte trabajo y reúne resultados (maestro).
	
	Cada esclavo es capaz de realizar una computación que le asigne el maestro y enviar a este
	último los resultados para que sean mostrados en pantalla por el maestro.

	Consistirá en el cálculo de los números primos que hay en un intervalo.
	Habrá que construir 2 programas, maestro.c y esclavo.c

	1) El intervalo de números naturales donde calcular los números primos se pasará como
	argumento al maestro. El maestro creará dos esclavos y dividirá el intervalo en dos
	subintervalos de igual tamaño pasando cada subintervalo como argumento a cada programa
	esclavo.

	Si al maestro le proporcionamos el intervalo 1000 a 2000, un esclavo debe calcular entre
	1000 y 1500, y el otro esclavo entre 1501 y 2000.

	El maestro creará dos cauces sin nombre y se encargará de su redirección para comunicarse
	con los procesos esclavos. El maestro irá recibiendo y mostrando en pantalla (uno a uno)
	los números primos calculados por los esclavos en orden creciente.

	2) El esclavo tiene como argumentos el extremo inferior y superior del intervalo sobre el
	que buscará números primos. Para identificar un número primo utiliza el siguiente método:
	un número n es primo si no es divisible por ningún k tal que 2 < k <= sqrt(n)

	El esclavo envía al maestro cada primo encontrado como un dato entero (4B) que escribe en
	salida estándar, que tiene que encontrarse redireccionada a un cauce sin nombre.

	Los dos cauces sin nombre necesarios, para comunicar el maestro con sus dos esclavos, los
	creará el maestro inicialmente.

	Una vez el esclavo haya calculado y enviado todos los primos, terminará.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

const int num_hijos = 2;

int main(int argc, char *argv[]){

	// Comprueba que ha recibido los parámetros correctamente
	if (argc != 3){
		printf("Error en el número de parámetros. Formato de ejecución: ./maestro.c <limite_inferior> <limite_superior>\n");
		exit(-1);
	}

	int fd[num_hijos][2];
	int bytesLeidos[num_hijos], val[num_hijos];
	pid_t PID[num_hijos];

	int intervalos[6];
	char char_ini[10], char_fin[10];
	int inicio_intervalo[num_hijos], fin_intervalo[num_hijos];

	// Divide los intervalos para repartir el trabajo entre los dos hijos
	inicio_intervalo[0] = atoi(argv[1]);
	fin_intervalo[num_hijos-1] = atoi(argv[2]);
	inicio_intervalo[1] = (inicio_intervalo[0] + fin_intervalo[num_hijos-1]) / 2;
	fin_intervalo[0] = inicio_intervalo[1] - 1;
	
	// Crea dos cauces sin nombre
	for (int i = 0; i < num_hijos; i++)
		pipe(fd[i]);
	
	printf("\nNúmeros primos desde %d hasta %d :\n", inicio_intervalo[0], fin_intervalo[num_hijos-1]);

	// Crea el esclavo 1
	if ((PID[0] = fork()) == 0){		// proceso hijo 0
		close(fd[0][0]);				// cierra descriptor de lectura del hijo
		dup2(fd[0][1], STDOUT_FILENO);	// cauce de escritura en la salida estándar

		if (execl("./esclavo", "esclavo", char_ini, char_fin, NULL) < 0){
			perror("\nError en execl");
			exit(-1);
		}

	}else{	// proceso padre
		close(fd[0][1]);	// cierra el descriptor de escritura del padre

		// Lee los valores del cauce
		while((bytesLeidos[0] = read(fd[0][0], &val[0], sizeof(int))) > 0){
			printf("%d ", val[0]);
		}

		close(fd[0][0]);
		printf("\n");
	}

	// Crea el esclavo 2
	sprintf(char_ini, "%d", inicio_intervalo[1]);
	sprintf(char_fin, "%d", fin_intervalo[1]);

	if ((PID[1] = fork())== 0){			// proceso hijo 1
		close(fd[1][0]);				// cierra descriptor de lectura del hijo
		dup2(fd[1][1], STDOUT_FILENO);	// cauce de escritura en la salida estándar

		if (execl("./esclavo", "esclavo", char_ini, char_fin, NULL) < 0){
			perror("\nError en execl");
			exit(-1);
		}

	}else{	// proceso padre
		close(fd[1][1]);	// cierra el descriptor de escritura del padre

		// Lee los valores del cauce
		while((bytesLeidos[1] = read(fd[1][0], &val[1], sizeof(int))) > 0){
			printf("%d ", val[1]);
		}

		close(fd[1][0]);
		printf("\n");
	}

	return 0;
}