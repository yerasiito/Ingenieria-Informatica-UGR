%Estructura de datos
array [int] of int: asignaturas = [4,4,2];
int: n = length(asignaturas);
int: m = 2*5;
set of int: VALUES = 1..n;
set of int: FRANJA = 1..m; %6 horas de 5 dias

array [int] of int: DOSHORAS = [1,2,3]; % Asignaturas de 2 horas
array [int] of int: UNAHORA = []; % Asignaturas de 2 horas

% Definir vector de horario
array [FRANJA] of var VALUES: horario;

% Restriccion b, asigna la asignatura segun las horas que se imparte
constraint forall(i in DOSHORAS)( % Restriccion c de 2 horas
  let {
    var int: count = 1+sum(j in 1..m-1)(horario[j] == i /\ horario[j+1] == i);
  } in
    count >= asignaturas[i]
);

constraint forall(i in UNAHORA)( % Restriccion c de 1 hora
  let {
    var int: count = sum(j in 1..m-1)(horario[j] == i /\ horario[j+1] != i);
  } in
    count >= asignaturas[i]
);

solve satisfy;

%Si i==A1,A3,A4,A5,A8 entonces i+1==A que sea
%Si i==A2,A6,A7,A9 entonces i+1!=A que sea

% Restriccion d
% alldifferent(1..6*i)