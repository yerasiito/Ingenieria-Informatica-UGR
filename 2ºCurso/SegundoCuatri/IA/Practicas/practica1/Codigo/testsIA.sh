#!/bin/bash

DIRECTORIO="Resultados"
output=$DIRECTORIO/resultados

#./practica1SG mapa semilla nivel fila columna sentido

#Crea el directorio si no existe
if [ ! -d "./$DIRECTORIO" ];then
mkdir $DIRECTORIO;fi

#Crea los ficheros resultados
if [[ -e $output.dat || -L $output.dat ]] ; then
    i=1
    while [[ -e $output-$i.dat || -L $output-$i.dat ]] ; do
        let i++
    done
    output=$output-$i
fi

echo -n ""> $output.dat

echo "Mapa: ./mapas/cuadricula.map" >> $output.dat
for (( c=0; c<=4; c+=1 ))
do
	echo -e -n "Nivel $c: " >> $output.dat
    ./practica1SG ./mapas/cuadricula.map 0 $c 78 79 0 | tail -n1 >> $output.dat
done

echo -e "\nMapa: ./mapas/mapa100.map" >> $output.dat
for (( c=0; c<=4; c+=1 ))
do
	echo -e -n "Nivel $c: " >> $output.dat
    ./practica1SG ./mapas/mapa100.map 0 $c 78 79 0 | tail -n1 >> $output.dat
done

echo -e "\nMapa: ./mapas/mapa75.map" >> $output.dat
for (( c=0; c<=4; c+=1 ))
do
	echo -e -n "Nivel $c: " >> $output.dat
    ./practica1SG ./mapas/mapa75.map 0 $c 14 37 0 | tail -n1 >> $output.dat
done

echo -e "\nMapa: ./mapas/mapa50.map" >> $output.dat
for (( c=0; c<=4; c+=1 ))
do
	echo -e -n "Nivel $c: " >> $output.dat
    ./practica1SG ./mapas/mapa50.map 0 $c 20 20 0 | tail -n1 >> $output.dat
done

echo -e "\nMapa: ./mapas/mapa30.map" >> $output.dat
for (( c=0; c<=4; c+=1 ))
do
	echo -e -n "Nivel $c: " >> $output.dat
    ./practica1SG ./mapas/mapa30.map 0 $c 15 20 0 | tail -n1 >> $output.dat
done

echo -e "\nMapa: ./mapas/medieval.map" >> $output.dat
for (( c=0; c<=4; c+=1 ))
do
	echo -e -n "Nivel $c: " >> $output.dat
    ./practica1SG ./mapas/medieval.map 0 $c 15 20 0 | tail -n1 >> $output.dat
done

echo -e "\nMapa: ./mapas/picto.map" >> $output.dat
for (( c=0; c<=4; c+=1 ))
do
	echo -e -n "Nivel $c: " >> $output.dat
    ./practica1SG ./mapas/picto.map 0 $c 15 20 0 | tail -n1 >> $output.dat
done

echo -e "\nMapa: ./mapas/vertigo.map" >> $output.dat
for (( c=0; c<=4; c+=1 ))
do
	echo -e -n "Nivel $c: " >> $output.dat
    ./practica1SG ./mapas/vertigo.map 0 $c 15 20 0 | tail -n1 >> $output.dat
done
