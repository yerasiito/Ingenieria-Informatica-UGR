#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define S_ISREG2 (mode)     (((mode) & S_IFMT) == 0100000)

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
            else strcpy(tipoArchivo, "No es un archivo regular");
            printf("%s\n",tipoArchivo);
        }
    }
}