include "globals.mzn";

% DESCOMENTAR PARA PROBAR MATRICES
% include "matrices/adyacencia10.dzn";
% include "matrices/adyacencia20.dzn";
% include "matrices/adyacencia30.dzn";
% include "matrices/adyacencia40.dzn";
% include "matrices/adyacencia50.dzn";
include "matrices/adyacencia60.dzn";

% MODIFICAR PARA PROBAR SEMILLAS
int: semilla = 0; %0, 33, 42

% Selecciona matriz de adyacencia segun la semilla
array[int, int] of int: adyacencia = 
  if semilla == 0 then
    adyacencia_sem1 % sem 0
  elseif semilla == 1 then 
    adyacencia_sem2 % sem 33
  elseif semilla == 2 then
    adyacencia_sem3 % sem 42
  else
    adyacencia_sem1 % sem 0
endif;

array [1..n] of var bool: conjuntoMinimo;

constraint forall(i in 1..n)(conjuntoMinimo[i] == 1 \/ 
           exists(j in 1..n where adyacencia[i,j] == 1)(conjuntoMinimo[j] == 1)
);

solve minimize sum(i in 1..n)(conjuntoMinimo[i] == 1);

output ["Nº nodos del conjunto minimo: "] ++ [show(sum(i in 1..n)(conjuntoMinimo[i] == 1))];
