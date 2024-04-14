% Las constantes son datos del problema que participan en las
% restricciones del problema pero cuyos valores son fijos
% Se definen igual que las variables pero sin la palabra reservada
% “var”. También se puede declarar su valor:
int : z1;
int : z2 = 6;
% Si no se define su valor, éste será preguntado antes de comenzar
% la ejecución. Ejemplo:
var int : x;
int : min = 6;
int : max;
constraint x > min;
constraint x < max;
solve satisfy;