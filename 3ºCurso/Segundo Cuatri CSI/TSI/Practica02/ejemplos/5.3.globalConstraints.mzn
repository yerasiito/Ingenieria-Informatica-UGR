include "globals.mzn";

int: N = 5;
int: maxValue = 100;
set of int: exception = {2};
array[1..N] of var 1..maxValue: vector;

% Todos los valores del vector deben ser diferentes excepto los que
% proporcionamos como excepción
constraint all_different_except(vector, exception);

constraint sum(i in 1..N)(vector[i]) < 11 /\ sum(i in 1..N)(vector[i]) > 5;

solve satisfy;