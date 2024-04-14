% Para definir un array multidimensional únicamente tenemos que
% definir los tamaños de cada dimension:
set of int: XPOS = 1..5;
set of int: YPOS = 1..3;
array [XPOS,YPOS] of var 0..9: grid;
% Grid de 5 filas, 3 columnas, con valores del 0 al 9:
