#!/bin/bash
cmake ..
make

./practica SFHMA SPX 1 &&
./practica SFMHA_hibrido 1 &&

#./practica AGG Aritmetrico 1 && 
#./practica AGG BLX 1 &&

#./practica AGE Aritmetrico 1 && 
#./practica AGE BLX 1 &&

#./practica AM-All 1 &&
#./practica AM-Rand 1 &&
#./practica AM-Best 1
