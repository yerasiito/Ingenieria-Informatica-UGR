array [int] of int: numeros = [4, 4, 2];
int: block_size = 2;

int: total_elements = sum(numeros);
array[1..total_elements] of var int: conjuntoObjetos;

constraint forall(i in 1..total_elements) (
    conjuntoObjetos[i] >= 1 /\ conjuntoObjetos[i] <= length(numeros)
);

constraint forall(i in 1..length(numeros)) (
    count(conjuntoObjetos, i) == numeros[i]
);

constraint forall(i in 1..total_elements) (
    conjuntoObjetos[i] = conjuntoObjetos[(i - 1) div block_size + 1]
);

solve satisfy;

output [show(conjuntoObjetos)];
