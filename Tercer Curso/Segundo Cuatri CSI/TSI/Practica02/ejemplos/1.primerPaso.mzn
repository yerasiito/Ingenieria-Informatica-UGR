% Definición de variables:
var int: x;
var int: y;
% Definición de restricciones:
constraint x > 0;
constraint y > 0;
constraint x > y;
% Indica que es un CSP (podría ser un COP)
solve satisfy;