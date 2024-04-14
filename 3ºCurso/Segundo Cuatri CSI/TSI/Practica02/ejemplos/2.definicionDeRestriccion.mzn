% La definición de una restricción comienza por “constraint”
% Se pueden usar los operadores lógicos/aritméticos habituales:
% <= , < , == , != , > , >=
% + , - , * . División entera “a div b”. Resto “a mod b”
% AND: “/\” OR: “\/” IF: “->” IFF: “<->”

% Ejemplo:
var 1..3: WA; var 1..3: NT; var 1..3: SA; var 1..3: Q;
var 1..3: NSW; var 1..3: V; var 1..3: T;
constraint WA != NT /\ WA != SA ;
constraint NT != SA /\ NT != Q ;
constraint Q != NSW ;
constraint NSW != V ;
constraint SA != Q ;
constraint SA != NSW /\ SA != V ;
solve satisfy;