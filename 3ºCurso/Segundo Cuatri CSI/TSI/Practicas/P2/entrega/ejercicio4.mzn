include "globals.mzn";

% Se inicializan las variables asociadas a las TAREAS
int: N = 10;
set of int: TR = 1..3;
set of int: TAREAS = 1..N;

% Se asigna un número a cada tarea
int: LevantarMuros = 1;
int: CarpinteriaTejado = 2;
int: PonerTejado = 3;
int: InstalacionElectrica = 4;
int: PintadoFachada = 5;
int: Ventanas = 6;
int: Jardin = 7;
int: Techado = 8;
int: PintadoInterior = 9;
int: Remates = 10;

% Se crea una matriz de duraciones por tarea(filas) y trabajador(columnas)
array[TAREAS, TR] of int: Duraciones = [|5,7,10|
                                         3,5,7|
                                         3,2,4|
                                         2,5,8|
                                         4,3,6|
                                         3,2,1|
                                         2,2,3|
                                         1,3,5|
                                         2,3,4|
                                         3,2,1|
|];

% Una tarea tiene un INICIO (un día), un FIN (lo que se tarde en completar la tarea y un trabajador asignado
array[TAREAS] of var int: Inicio; % Día en el que comienza la tarea
array[TAREAS] of var int: Fin; % Día en el que termina la tarea
array[TAREAS] of var int: asignarTrabajador; % Trabajador asignado a la tarea
array[TAREAS] of var bool: asignarTrabajadorApoyo; % Indica si se asigna un trabajador de apoyo a la tarea

% Empieza en el día 1
constraint Inicio[1] = 1;

% Restricciones de inicio de cada tarea
%(1) A    Levantar muros          7        Ninguna

% (2) B    Carpintería de tejado (A)
constraint Inicio[CarpinteriaTejado] > Fin[LevantarMuros];
%(3) C    Poner tejado (B)
constraint Inicio[PonerTejado] > Fin[CarpinteriaTejado];
%(4) D    Instalación eléctrica (A)
constraint Inicio[InstalacionElectrica] > Fin[LevantarMuros];
%(5) E    Pintado fachada (C,D)
constraint Inicio[PintadoFachada] > Fin[PonerTejado] /\ Inicio[PintadoFachada] > Fin[InstalacionElectrica];
%(6) F    Ventanas (C,D,E)
constraint Inicio[Ventanas] > Fin[PonerTejado] /\ Inicio[Ventanas] > Fin[InstalacionElectrica] /\ Inicio[Ventanas] > Fin[PintadoFachada];
%(7) G    Jardín (C,D)
constraint Inicio[Jardin] > Fin[PonerTejado] /\ Inicio[Jardin] > Fin[InstalacionElectrica];
%(8) H    Techado (A)
constraint Inicio[Techado] > Fin[LevantarMuros];
%(9) I    Pintado interior (F,H)
constraint Inicio[PintadoInterior] > Fin[Ventanas] /\ Inicio[PintadoInterior] > Fin[Techado];
%(10) J   Remates (G,I)
constraint Inicio[Remates] > Fin[Jardin] /\ Inicio[Remates] > Fin[PintadoInterior];
                    
% Calcula el día de finalización de cada tarea                   
constraint forall(t in TAREAS) (
  let {
    var int: duracion = Duraciones[t, asignarTrabajador[t]] - 1; % resta 1 ya que la duración de una tarea se considera en términos de intervalos, donde el día de inicio cuenta como el primer día de trabajo y el día de finalización cuenta como el último día de trabajo
  } in
    if duracion >= 1 /\ asignarTrabajadorApoyo[t] then
      Fin[t] = Inicio[t] + duracion - 1 % El trabajador de apoyo resta 1 día de duración
    else
      Fin[t] = Inicio[t] + duracion
    endif
);

% Restricción: Un trabajador no puede empezar a trabajar mientras hace otra tarea
constraint forall(i in TAREAS, j in TAREAS
where 
  i != j /\ asignarTrabajador[i] == asignarTrabajador[j])
(Inicio[j] > Fin[i] \/ Inicio[j] < Inicio[i]);

% Restricción: Un trabajador de apoyo no puede empezar a trabajar mientras hace otra tarea
constraint forall(i in TAREAS, j in TAREAS
where 
  i != j /\ asignarTrabajadorApoyo[i] == asignarTrabajadorApoyo[j])
(Inicio[j] > Fin[i] \/ Inicio[j] < Inicio[i]);

% Minimiza la duración máxima de construcción
solve minimize max(i in TAREAS)(Fin[i]);

% Imprime los resultados en formato tabla
output ["Tarea\t| A\tB\tC\tD\tE\tF\tG\tH\tI\tJ "] ++ ["\n"];
output ["Inicio\t| "] ++ ["\(Inicio[i])\t" | i in TAREAS] ++ ["\n"];
output ["Fin\t| "] ++ ["\(Fin[i])\t" | i in TAREAS] ++ ["\n"];
output ["Trabaj\t| "] ++ ["\(asignarTrabajador[i])\t" | i in TAREAS] ++ ["\n"];
output ["Apoyo\t| "] ++ ["\(asignarTrabajadorApoyo[i])\t" | i in TAREAS] ++ ["\n"];
output ["Duracion de construcción: " ++ show(Fin[N]) ++ " días."];