/*
Ejercicio 3

Realiza un programa en C que recorra la jerarquía de subdirectorios existentes a partir de uno dado como argumento
y devuelva la cuenta de todos los archivos regulares que tengan permiso de ejecución para el grupo y para otros.

Deberá devolver sus números de inodo y la suma total de espacio ocupado por dichos archivos.

El formato será:
./buscar <pathname>

En caso de no recibir argumento, toma como punto de partida el directorio actual.
*/

#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>   
#include <dirent.h>
#include <ftw.h>

// Declaración de variables globales
int num_archivos = 0, tam = 0;

int visitar(const char *pathname, const struct stat *statbuf, int typeflag, struct FTW *ftwbuf){
    if( S_ISREG(statbuf->st_mode) && (statbuf->st_mode & S_IXGRP) && (statbuf->st_mode & S_IXOTH) ){
        printf("%s %lu\n", pathname, statbuf->st_ino);
        tam += statbuf->st_size;
        num_archivos++;
    }

    return 0;
}

int main(int argc, char **argv){

    printf("Los i-nodos son:\n");

    if (nftw(argc >= 2 ? argv[1] : ".", visitar, 10, 0)){
        perror("nftw");
    }

    printf("Existen %d archivos regulares con permiso x para grupo y otros\n", num_archivos);
    printf("El tamaño total ocupado por dichos archivos es %d bytes\n", tam);

    return 0;
}
