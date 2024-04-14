% Las variables son aquellas para las que el CSP solver va a buscar valores 
% dentro de sus dominios y respetando las restricciones
% La definición de toda variable comienza por “var”
% seguida por su dominio y su nombre o identificador:
var int : x;
var -1..1 : y;
% Un dominio puede ser:
% * Un tipo primitivo (int, float o bool)
% * Un intervalo (para int: “a .. b”; para float: “a.x .. b.y”, p.ej. 0.0 .. 10.0)
% * Un conjunto previamente definido (“set of”):

set of int: values1 = -1..1;
var values1: y2;

set of int: values2 = {-1,0,1};
var values2: y3;