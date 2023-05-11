include "globals.mzn";
% int : marcas = 3;
% int : marcas = 5;
% int : marcas = 7;
int : marcas = 10;
% int : marcas = 12;

array[0..marcas] of var int: posiciones; %Vector de posiciones.

% Restricciones
constraint posiciones[0]=0; %La primera marca está en x1=0
constraint forall(i in 1..marcas)(posiciones[i] > posiciones[i-1]); %Orden creciente
constraint all_different([posiciones[i] - posiciones[j] | i in 0..marcas , j in i+1..marcas-1]); %Ninguna distancia coincide

% Mimizar la ultima marca
solve minimize posiciones[marcas-1];

% Salida
output ["Posición de las marcas: "];
output ["\(posiciones[i]) "| i in 0..marcas-1];
output ["\nUltima marca: "] ++ [show(posiciones[marcas-1])]