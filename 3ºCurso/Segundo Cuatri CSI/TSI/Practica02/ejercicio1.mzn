% Conjunto inicial

% Descomentar el array S a probar
% array [int] of int: S = [1,1,2];
% array [int] of int: S = [1,2,3,4,5,6];
array [int] of int: S = [1,1,2,4,4,5,6,7,8];

int: n = length(S);

% Para la codificación del problema se ha utilizado un vector bool disjunto del cual se representa como 0 el conjunto disjunto S1 y 1 el conjunto disjunto S2. 
% Conjunto disjunto 0 y 1
array [1..n] of var bool: S_disjunto;

% Restricción:  suma de los números en S1 sea igual a la suma de los números en S2
constraint sum(i in 1..n where not S_disjunto[i])(S[i]) == sum(i in 1..n where S_disjunto[i])(S[i]);

solve satisfy;

% Imprimir el conjunto S original
output ["Conjunto S: "] ++ ["\(S)\n"];

% Imprimir los disconjuntos S1 y S2
output[ "S1: "] ++
[ if not fix(S_disjunto[i]) then "\(S[i]) " endif | i in 1..n ] ++ ["\n"];

output[ "S2: "] ++
[ if fix(S_disjunto[i]) then "\(S[i]) " endif | i in 1..n ] ++ ["\n"];

% Imprimir la suma
output["Suma: "] ++ [show(sum(i in 1..n where not S_disjunto[i])(S[i]))]