# Script que lista las palabras de un fichero de texto
# que comienzan por una letra pasada como parámetro
#!/bin/bash

#Informacion sobre el script
if [[ $1 == "-info" ]]; then
    printf "Script que lista las palabras de un fichero de texto que comienzan por una letra pasada como parámetro\n"
    printf "Ejemplo de ejecucion: './palabrasPorLetra.sh ../datos/diccionario1.txt a'" #Lista las palabras que empiezan por a en el diccionario1.txt
    echo "
adicionalmente
andaba
admirablemente
andarlos
augmentar
amago
aseguradamente
ambarar
abridla
andado
aterido
armad
alhombrar
ahorita
andale
aplayar
a
        "
    exit 0
fi

if [ $# != 2 ]; then
    echo "Número de parámetros incorrecto."
    echo "Uso: ./palabrasPorLetra.sh <diccionario.txt> <caracter>"
    echo "Usa './palabrasPorLetra.sh -info' para mayor informacion"
    exit 1
fi

grep -E '\b'$2'' $1
