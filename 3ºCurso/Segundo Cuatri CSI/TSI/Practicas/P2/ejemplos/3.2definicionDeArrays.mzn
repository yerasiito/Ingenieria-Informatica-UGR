% El conjunto de posiciones puede ser cualquiera (pero cuidado
%cuando se accede a él!):

array [1..7] of var 1..3: regiones;
output ["\(regiones[i]) " | i in 1..7] ++ ["\n"];
array [10..16] of var 1..3: regiones1;
output ["\(regiones1[i]) " | i in 10..16] ++ ["\n"];
array [-10..-4] of var 1..3: regiones2;
output ["\(regiones2[i]) " | i in -10..-4] ++ ["\n"];

% Para evitarlo se pueden definir “sets”
set of int: POS = 1..7;
set of int: VALUES = 1..3;
array [POS] of var VALUES: regiones3;
output ["\(regiones3[i]) " | i in POS];