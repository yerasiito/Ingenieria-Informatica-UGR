int: t = 1;
int: S = 10;
% El formateo de salida (output) debe ser una lista de strings
% Algunas funciones útiles para mostrar el valor de las variables: show,
% show_int, show_float:

output["\(S)\n"];
output[show(S)];

output["t=\(t)\n"];
output["t=" ++ show(t) ++ "\n"];

% fix se emplea en el output para convertir una variable en una constante.
% Es necesario en ocasiones, por ejemplo, cuando se emplea un if en el
% output
array [int] of int: encargado = [1,1,2];
array [int] of string: nombres = ["Paco", "Maria", "Pedro"];
int: n = length(encargado);

output
[ "Encargado: "] ++
[ if fix(encargado[i])==1 then "\(nombres[i]) " else "" endif | i in 1..n ]
;