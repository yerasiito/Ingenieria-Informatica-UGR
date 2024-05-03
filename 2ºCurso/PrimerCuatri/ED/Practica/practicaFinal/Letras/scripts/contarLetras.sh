# Script que cuenta el numero de veces que aparece cada letra de forma 100% precisa
# Informacion sobre el script

if [[ $1 == "-info" ]]; then
    printf "Script que cuenta el numero de veces que aparece cada letra de forma precisa\n"
    printf "Por ejemplo: './contarLetras.sh ../datos/diccionario1.txt'"
    echo "
100
123 a
15 b
23 c
38 d
136 e
8 f
19 g
9 h
60 i
3 j
39 l
54 m
62 n
50 o
17 p
2 q
76 r
57 s
61 t
24 u
6 v
1 x
3 y
1 z
"
    exit 0
fi

#!/bin/bash

#Comprueba parámetros
if [ $# != 1 ]; then
    echo "Numero de parámetros incorrecto."
    echo "Uso: ./contarLetras.sh <diccionario.txt>"
    echo "Usa: './contarLetras.sh -info' para mayor informacion"
    exit 1
fi

#El comando
sed 's/\(.\)/\1\n/g' $1 | sort | uniq -c
