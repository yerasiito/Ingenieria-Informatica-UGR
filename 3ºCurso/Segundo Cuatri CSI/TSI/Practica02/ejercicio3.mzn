array [int] of int: asignaturas = [4, 4, 2];
int: horas = sum(i in asignaturas)(i);
int: n = length(asignaturas);
set of int: nAsignaturas = 1..n;

array [int] of int: bloque1 = [2];
array [int] of int: bloque2 = [1,3];

array [1..horas] of var nAsignaturas: horario;

% Bloques de 2
constraint forall(i in 1..horas) (
    if (horario[i] in bloque2) then
        horario[i] == horario[i+1] /\ horario[i] != horario[i+2]
    endif
);

% Horas de clase
constraint forall(i in 1..horas) (
    let {
        var int: count = sum(j in 1..horas)(horario[j] = i)
    }
    in
    count >= horario[i]
);

solve satisfy;