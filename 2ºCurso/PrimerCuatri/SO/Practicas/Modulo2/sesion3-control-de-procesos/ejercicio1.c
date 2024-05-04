/*
    Ejercicio 1
    Implementa un programa en C que tenga como argumento un número entero.
    
    Este programa creará un proceso hijo encargado de comprobar si dicho número es par o impar e 
    informará al usuario con un mensaje que se enviará por la salida estándar.

    El proceso padre comprobará si dicho número es divisible por 4 y lo informará por la salida estándar.
*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char **argv){
    if (argc != 2){
        perror("nº parámetros incorrecto: requiere entero\n");
        exit(1);
    }

    pid_t pid;
    int num = atoi(argv[1]);

    if ( (pid = fork()) < 0){
        perror("Error en el fork\n");
    
    // proceso padre
    }else if (pid == 0){
        printf("\nel pid padre: %i",pid);
        if ((num % 4) == 0)
            printf("\nPadre: número divisible por 4\n");
        else
            printf("\nPadre: número NO divisible por 4\n");
    
    // proceso hijo
    }else{
        printf("El pid hijo: %i",pid);
        if ((num % 2) == 0)
            printf("\nHijo: el número es par\n");
        else
            printf("\nHijo: el número es impar\n");
    }

    return 0;
}
