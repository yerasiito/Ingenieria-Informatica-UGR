#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<unistd.h>

int main(int argc, char **argv){
    
    if (argc != 2){
        printf("\nNº parámetros incorrecto");
        exit(-1);
    }

    char *pathname = argv[1];   // parámetro introducido (ruta al archivo de lectura)
    char buffer[80];            // buffer de E/S
    int num_bloque = 1;         // nº bloque leído
    int numbytes;               // nº bytes leídos en cada iteración (0 <= numbytes <= 80)
    int fd1, fd2;               // descriptores de archivo

    // Archivo de lectura
    if ((fd1 = open(pathname, O_RDONLY)) < 0){
        printf("\nError %d en open 1", errno);
        perror("\nError en open 1");
        exit(-1);
    }

    // Archivo de escritura
    if ((fd2 = open("salida.txt", O_CREAT|O_WRONLY, S_IRUSR|S_IWUSR)) < 0){
        printf("\nError %d en open 2", errno);
        perror("\nError en open 2");
        exit(-1);
    }

    // Deja la primera línea libre
    write(fd2, &buffer, 26);
    write(fd2, "\n", 1);

    // Recorre el archivo a leer en tramos de 80 bytes
    while((numbytes = read(fd1, &buffer, 80)) > 0){
        
        // Escribe "Bloque i" al principio del bloque
        char titulo_bloque[8];
        sprintf(titulo_bloque, "Bloque %d", num_bloque);
        write(fd2, &titulo_bloque, sizeof(titulo_bloque));
        write(fd2, "\n", 1);
        num_bloque++;

        // Escribe el cuerpo del bloque
        if (write(fd2, &buffer, numbytes) < 0){
            printf("\nError %d en segundo write: bloque %d", errno, num_bloque);
			perror("\nError en el segundo write");
			exit(-1);
        }
        write(fd2, "\n", 1);        
    }

    // MODIFICACIÓN
    // Muestra en la primera línea el nº total de bloques

    // se sitúa en la 1ª línea
    if (lseek(fd2, 0, SEEK_SET) < 0){
        perror("\nError en lseek");
        exit(-1);
    }

    // Escribe el total de bloques (num_bloque-1)
    char cadena[26];
    sprintf(cadena, "El número de bloques es %d", num_bloque-1);
    write(fd2, &cadena, sizeof(cadena));

    // Cierra los archivos
    close(fd1);
    close(fd2);

    return 0;
}