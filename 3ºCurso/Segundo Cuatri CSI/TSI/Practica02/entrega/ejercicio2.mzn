include "globals.mzn";

% Representación de las marcas, descomenta para probar

% int : marcas = 3;
% int : marcas = 5;
% int : marcas = 7;
int : marcas = 10;
% int : marcas = 12;

% Para la codificación del problema se ha utilizado un vector int de marcas del cual se representa la posición del vector como el número de marca y el valor como la posición.
array[0..marcas] of var int: posiciones; %Vector de posiciones.

% Restricciones

% 1.La primera marca está en x1=0
constraint posiciones[0]=0; 

% 2.Orden creciente
constraint forall(i in 1..marcas)(posiciones[i] > posiciones[i-1]);

% 3.la distancia entre todas las marcas es diferente
constraint all_different([posiciones[i] - posiciones[j] | i in 0..marcas , j in i+1..marcas-1]); %Ninguna distancia coincide

% Mimizar la ultima marca
solve minimize posiciones[marcas-1];

% Salida
output ["Posición de las marcas: "];
output ["\(posiciones[i]) "| i in 0..marcas-1];
output ["\nUltima marca: "] ++ [show(posiciones[marcas-1])]