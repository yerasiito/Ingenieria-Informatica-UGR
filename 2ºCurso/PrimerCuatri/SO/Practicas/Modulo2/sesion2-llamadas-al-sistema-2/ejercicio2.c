/*
Ejercicio 2

Realiza un programa en C utilizando las llamadas al sistema necesarias que acepte como entrada:
    • Un argumento que representa el 'pathname' de un directorio.
    • Otro argumento que es un número octal de 4 dígitos (similar al que se puede utilizar
      para cambiar los permisos en la llamada al sistema chmod). Para convertir este argumento
      tipo cadena a un tipo numérico puedes utilizar la función strtol. Consulta el manual en
      línea para conocer sus argumentos.

El programa tiene que usar el número octal indicado en el segundo argumento para cambiar los
permisos de todos los archivos que se encuentren en el directorio indicado en el primer
argumento.

El programa debe proporcionar en la salida estándar una línea para cada archivo del directorio
que esté formada por:
<nombre_de_archivo> : <permisos_antiguos> <permisos_nuevos>

Si no se pueden cambiar los permisos de un determinado archivo se debe especificar la siguiente
información en la línea de salida:
<nombre_de_archivo> : <errno> <permisos_antiguos>

*/

#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>   
#include <dirent.h>

int main(int argc, char **argv){

    if (argc != 3){
        printf("Nº parámetros incorrecto, esperados 2 recibidos %d\n", argc-1);
        exit(1);
    }

    // Declaración de variables
    char *pathname = argv[1];
    DIR *directorio;
    struct dirent *sdirent;
    struct stat atributos;
    int stat_result, new_permissions, old_permissions, chmod_result;

    // Abre el directorio
    directorio = opendir(pathname);

    if (directorio == NULL){
        printf("Error: no se ha podido abrir el directorio %s\n", pathname);
        exit(1);
    }

    // Lee el contenido del directorio
    while((sdirent = readdir(directorio)) != NULL){

        stat_result = stat(sdirent->d_name, &atributos);
        if (stat_result < 0){
            printf("Error al intentar acceder a los atributos del archivo %s\n", sdirent->d_name);
        }else{
            // Si no es un directorio
            if(!S_ISDIR(atributos.st_mode)){
                new_permissions = strtol(argv[2], 0, 8) & 0777;
                old_permissions = atributos.st_mode & 0777;

                // cambia los permisos
                chmod_result = chmod(sdirent->d_name, new_permissions);

                if(chmod_result < 0){
                    // no se han podido cambiar los permisos
                    printf("%s \t : \t %d \t %o\n", sdirent->d_name, chmod_result, new_permissions);
                    exit(1);

                }else{
                    // se han cambiado los permisos
                    printf("%s \t : \t %o \t %o\n", sdirent->d_name, old_permissions, new_permissions);
                }
            }
        }
    }

    printf("\n");
    closedir(directorio);

    return 0;
}
