// consumidorFIFO.c

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#define ARCHIVO_FIFO "ComunicacionFIFO"

int main(void){
	int fd;
	char buffer[80]; 	// almacena el mensaje del cliente
	int leidos;

	// Crea cauce con nombre (FIFO) si no existe
	umask(0);
	mkfifo(ARCHIVO_FIFO, 0666);

	// Abre el cauce para lectura/escritura
	if ((fd = open(ARCHIVO_FIFO, O_RDWR)) < 0){
		perror("open");
		exit(-1);
	}

	// Aceptar datos a consumir hasta que se envíe la cadena fin
	while(1){
		leidos = read(fd, buffer, 80);
		
		if (strcmp(buffer,"fin") == 0){
			close(fd);
			return 0;
		}

		printf("\nMensaje recibido: %s\n", buffer);
	}

	return 0;
}