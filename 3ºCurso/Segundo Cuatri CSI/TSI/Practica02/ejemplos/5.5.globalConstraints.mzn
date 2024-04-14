% Estas restricciones globales se pueden combinar con otras
% funciones típicas (suma, contar, etc…):

% sum(<POS>) ( <array> )
% count(<array>,<value>)

% Ejemplo:
include "globals.mzn";
% Array con 10 posiciones con números del 0 al 20
array[0..9] of var 0..20: myarray;
% All different:
constraint forall(i in 0..20)(count(myarray,i)<=1);
% La suma de la primera mitad igual a la suma de la segunda mitad
constraint sum(i in 0..4)(myarray[i]) ==
           sum(i in 5..9)(myarray[i]);
solve satisfy;