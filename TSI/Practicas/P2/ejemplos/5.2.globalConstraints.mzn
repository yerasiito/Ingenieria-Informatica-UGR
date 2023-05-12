include "globals.mzn";

int: N = 10;
int: maxValue = 100;

array[1..N] of var 0..maxValue: vector;

% Todos los valores del vector deben ser diferentes excepto el 0
constraint all_different_except_0(vector);

constraint sum(i in 1..N)(vector[i]) < 10 /\ sum(i in 1..N)(vector[i]) > 5;

solve satisfy;