% Conjunto inicial
% array [int] of int: S = [1,1,2];
% array [int] of int: S = [1,2,3,4,5,6];
array [int] of int: S = [1,1,2,4,4,5,6,7,8];
int: n = length(S);

% Conjunto disjunto 0 y 1
array [1..n] of var bool: S_disjunto;

% Restricciones
constraint sum(i in 1..n where S_disjunto[i]==0)(S[i]) == sum(i in 1..n where S_disjunto[i]==1)(S[i]);

solve satisfy;

% Imprimir los conjuntos
set of int: S1 = {S[i] | i in 1..n where S[i] == 0};
set of int: S2 = {S[i] | i in 1..n where S[i] == 1};

output ["Conjunto S: "] ++ ["\(S)\n"];

output[ "S1: "] ++
[ if fix(S_disjunto[i])==0 then "\(S[i]) " endif | i in 1..n ] ++ ["\n"];

output[ "S2: "] ++
[ if fix(S_disjunto[i])==1 then "\(S[i]) " endif | i in 1..n ] ++ ["\n"];

output["Suma: "] ++ [show(sum(i in 1..n where S_disjunto[i]==0)(S[i]))]