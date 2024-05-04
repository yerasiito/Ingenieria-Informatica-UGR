#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]){
    int i;
    struct stat atributos;
    char tipoArchivo[30];

    if (argc < 2){
        printf("\nSintaxis de ejecución: tarea 2 [<nombre_archivo>]+\n\n");
        exit(-1);
    }

    for (int i = 1; i < argc; i++){
        printf("%s: ", argv[i]);
        if (lstat(argv[i], &atributos) < 0){
            printf("\nError al intentar acceder a los atributos de %s", argv[i]);
            perror("\nError en lstat");
        }else{
            if (S_ISREG(atributos.st_mode)) strcpy(tipoArchivo, "Regular");
            else if (S_ISDIR(atributos.st_mode)) strcpy(tipoArchivo, "Directorio");
            else if (S_ISCHR(atributos.st_mode)) strcpy(tipoArchivo, "Especial de caracteres");
            else if (S_ISBLK(atributos.st_mode)) strcpy(tipoArchivo, "Especial de bloques");
            else if (S_ISFIFO(atributos.st_mode)) strcpy(tipoArchivo, "Cauce con nombre (FIFO)");
            else if (S_ISLNK(atributos.st_mode)) strcpy(tipoArchivo, "Enlace relativo (soft)");
            else if (S_ISSOCK(atributos.st_mode)) strcpy(tipoArchivo, "Socket");
            else strcpy(tipoArchivo, "Tipo de archivo desconocido");
            printf("%s\n",tipoArchivo);
        }
    }

    return 0;
}