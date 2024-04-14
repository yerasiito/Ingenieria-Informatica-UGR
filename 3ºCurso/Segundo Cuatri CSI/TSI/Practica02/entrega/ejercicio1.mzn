% Conjunto inicial

% Descomentar el array S a probar
% array [int] of int: S = [1,2,3,4,5,6]; % Apartado a insatisfactible
% array [int] of int: S = [99,14,82,47,82,50,77,45,23,92,52,90,46,57,29,25,74,25,30,70];
% array [int] of int: S = [35,82,97,30,38,78,18,39,35,93,49,47,30,57,43,21,92,51,89,80];
array [int] of int: S = [60,8,11,2,49,69,87,15,62,72,89,14,76,63,45,92,74,80,11,2];
int: n = length(S);

% Para la codificación del problema se ha utilizado un vector bool disjunto del cual se representa como 0 el conjunto disjunto S1 y 1 el conjunto disjunto S2. 
% Conjunto disjunto 0 y 1
array [1..n] of var bool: S_disjunto;

% Restricción: la diferencia de la suma de los números en S1 y S2 sea mínima
var int: diff_sum = sum(i in 1..n where S_disjunto[i]==0)(S[i]) - sum(i in 1..n where S_disjunto[i]==1)(S[i]);

% Minimizar la diferencia
solve minimize abs(diff_sum);

% Imprimir el conjunto S original
output ["Conjunto S: "] ++ ["\(S)\n"];

% Imprimir los disconjuntos S1 y S2
output[ "S1: "] ++
[ if not fix(S_disjunto[i]) then "\(S[i]) " endif | i in 1..n ] ++ ["\n"];

output[ "S2: "] ++
[ if fix(S_disjunto[i]) then "\(S[i]) " endif | i in 1..n ] ++ ["\n"];

% Imprimir la suma

output["Suma S1: "] ++ [show(sum(i in 1..n where not S_disjunto[i])(S[i]))] ++ ["\n"];

output["Suma S2: "] ++ [show(sum(i in 1..n where S_disjunto[i])(S[i]))] ++ ["\n"];

output["Diferencia suma: "] ++ [show(diff_sum)];