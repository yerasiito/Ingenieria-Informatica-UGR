% Conjunto inicial
% array [int] of int: S = [99,14,82,47,82,50,77,45,23,92,52,90,46,57,29,25,74,25,30,70];
% array [int] of int: S = [35,82,97,30,38,78,18,39,35,93,49,47,30,57,43,21,92,51,89,80];
array [int] of int: S = [60,8,11,2,49,69,87,15,62,72,89,14,76,63,45,92,74,80,11,2];
int: n = length(S);

% Conjunto disjunto 0 y 1
array [1..n] of var bool: S_disjunto;

% Restricciones
var int: diff_sum = sum(i in 1..n where S_disjunto[i]==0)(S[i]) - sum(i in 1..n where S_disjunto[i]==1)(S[i]);

solve minimize abs(diff_sum);

% Imprimir los conjuntos
output ["S:"] ++ ["\(S)\n"];

output[ "S1: "] ++
[ if fix(S_disjunto[i])==0 then "\(S[i]) " endif | i in 1..n ] ++ ["\n"];

output[ "S2: "] ++
[ if fix(S_disjunto[i])==1 then "\(S[i]) " endif | i in 1..n ] ++ ["\n"];

output["Suma S1: "] ++ [show(sum(i in 1..n where S_disjunto[i]==0)(S[i]))] ++ ["\n"];

output["Suma S2: "] ++ [show(sum(i in 1..n where S_disjunto[i]==1)(S[i]))] ++ ["\n"];

output["Diferencia suma: "] ++ [show(diff_sum)];