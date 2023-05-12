% También se pueden definir arrays de constantes
% (sin la palabra “var”):
set of int: POS = 1..7;
set of int: VALUES = 1..3;
array [POS] of var VALUES: regiones;
array[POS] of string: strRegiones =
  ["WA","NT", "SA", "Q", "NSW", "V", "T"];
constraint regiones[1] != regiones[2] /\ regiones[1] != regiones[3] ;
constraint regiones[2] != regiones[3] /\ regiones[2] != regiones[4] ;
constraint regiones[4] != regiones[5] ;
constraint regiones[5] != regiones[6] ;
constraint regiones[3] != regiones[4] ;
constraint regiones[3] != regiones[5] /\ regiones[3] != regiones[6] ;
output ["\(strRegiones[i]) = \(regiones[i])\n" | i in POS];