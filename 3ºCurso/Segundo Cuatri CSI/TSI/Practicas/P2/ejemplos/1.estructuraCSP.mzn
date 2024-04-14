% ESTRUCTURA GENERAL DE UN CSP EN MINIZINC

% 1. Definición de variables y constantes:
var int : x; % Variable entera
var -1..1 : y; %Variable de -1 a 1
int : z = 6; %Constante

% 2. Definición de restricciones:
constraint x > 0 /\ y > 0;
constraint x > y;
constraint x > z;
% 3. Definición del problema. Para CSP usar:
solve satisfy;
% 4. Definición del output (opcional)
output ["x=\(x)\ny=\(y)"];