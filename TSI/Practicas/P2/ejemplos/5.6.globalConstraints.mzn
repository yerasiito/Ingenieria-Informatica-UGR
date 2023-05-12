include "globals.mzn";

int: N = 5;
int: maxValue = 100;

array[1..N] of var 1..maxValue: vector;

% Los valores del vector son todos diferentes
constraint all_different(vector);

% Son todos pares
constraint forall(i in 1..N)((vector[i] mod 2)==0);

% Existen dos valores cuya suma da el valor máximo
constraint exists(i,j in 1..N)(j!=i /\ (vector[i]+vector[j] == maxValue));

solve satisfy;

output [ "\(vector[i]) " | i in 1..N] ++ ["\n"];