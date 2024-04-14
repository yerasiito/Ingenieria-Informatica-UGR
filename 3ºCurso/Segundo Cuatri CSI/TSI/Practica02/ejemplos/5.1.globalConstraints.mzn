% A menudo, es común usar restricciones globales, definidas por el
% usuario o predefinidas en librerías. Las más comunes son:

include "globals.mzn";
% constraint all_different(<array>);
% constraint forall(<set>)(<restricción>);

% Por ejemplo:
array[0..9] of var 0..9: digitos;
constraint all_different(digitos);
constraint forall(i,j in 0..9)(i==j \/ digitos[i] != digitos[j]);

% all_different se puede aplicar a array multidimensionales:
array[1..3,1..3] of var 1..9: grid;
constraint all_different( [ grid[i,j] | i,j in 1..3 ] );
constraint all_different( grid );

% También se pueden usar predicados
% definidos por el usuario