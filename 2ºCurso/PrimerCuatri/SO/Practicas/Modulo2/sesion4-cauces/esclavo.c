#include <sys/types.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>

int primo(int n){
	int es_primo = 1;	

	for (int i = 2; i <= sqrt(n) && es_primo; i++)
		if (n % i == 0)
			es_primo = 0;

	return es_primo;
}

int main(int argc, char *argv[]){

	if (argc != 3){
		printf("esclavo: número de parámetros incorrecto\n");
		exit(-1);
	}

	int inicio = atoi(argv[1]),
		fin = atoi(argv[2]);
	
	for (int i = inicio; i < fin; i++)
		if (primo(i))
			write(STDOUT_FILENO, &i, sizeof(int));

	return 0;
}