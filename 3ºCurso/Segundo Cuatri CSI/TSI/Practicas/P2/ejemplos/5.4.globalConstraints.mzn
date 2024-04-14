% Debemos habituarnos a pensar de modo declarativo. Por ejemplo,
% ¿de qué manera podríamos hacer un “find” en MiniZinc? Es decir,
% queremos encontrar la posición de un valor dado en un vector
% determinado.
include "globals.mzn";

var int: pos; % posicion en que se encuentra 'target_value' en 'vector’

int: n = 10; % tamaño del vector
int: target_value; % valor cuya posición se desea conocer.
array[1..n] of int: vector = [100,20,30,4,50,6,70,8,90,10];

constraint vector[pos]=target_value;

solve satisfy;