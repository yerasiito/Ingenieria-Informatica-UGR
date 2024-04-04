#!/bin/bash

DIRECTORIO="Resultados"
output=$DIRECTORIO/resultados

#./practica1SG mapa semilla nivel fila columna sentido


echo -e "\nMapa: ./mapas/mapaEspecial.map" >> $output.dat
for (( c=0; c<=4; c+=1 ))
do
	echo -e -n "Nivel $c: " >> $output.dat
    ./practica1SG ./mapas/cuadricula.map 0 $c 50 20 0 | tail -n1 >> $output.dat
done

...

echo "Mapa: ./mapas/mapaXX.map" >> $output.dat
for (( c=0; c<=4; c+=1 ))
do
	echo -e -n "Nivel $c: " >> $output.dat
    ./practica1SG ./mapas/mapa30.map 0 $c 10 20 0 | tail -n1 >> $output.dat
done

...
