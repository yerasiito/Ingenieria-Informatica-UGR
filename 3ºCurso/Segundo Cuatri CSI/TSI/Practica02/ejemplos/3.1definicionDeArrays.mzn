% Una forma muy útil de definir variables es mediante arrays, los
% cuales son a menudo el input de algunas restricciones globales
% Un vector (unidimensional) se define como:
% array [<set-of-int>] of var <type>: <identifier>;
% donde <set-of-int> identifica las posiciones del array y puede ser
%cualquier conjunto de enteros (también negativos). Ejemplo:

array [1..7] of var 1..3: regiones;
constraint regiones[1] != regiones[2] /\ regiones[1] != regiones[3];
constraint regiones[2] != regiones[3] /\ regiones[2] != regiones[4];
constraint regiones[4] != regiones[5];
constraint regiones[5] != regiones[6] ;
constraint regiones[3] != regiones[4] /\ regiones[3] != regiones[5]
/\ regiones[3] != regiones[6] ;
solve satisfy;
output ["region \(i) = \(regiones[i]) \n" | i in 1..7];