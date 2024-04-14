include "globals.mzn";

% Se inicializan las variables asociadas a las TAREAS
int: N = 10;
set of int: TR = 1..3;
set of int: TAREAS = 1..N;

% A cada tarea se le asigna un número
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

% Se crea un vector de duraciones por tarea. 
% Las filas son tareas y las columnas trabajadores.
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
array[TAREAS] of var int: Inicio; % Se asigna el dia que comienza la tarea
array[TAREAS] of var int: Fin; % Una tarea tiene un dia de finalización
array[TAREAS] of var int: asignarTrabajador; % Una tarea tiene un trabajador

% Restricciones

constraint Inicio[1] = 1; % Empieza en el día 1

% Se aplican restriccioens a cada inicio de tarea
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

% Un trabajador no puede empezar a trabajar mientras hace una tarea
constraint forall(i in TAREAS, j in TAREAS
where 
  i != j /\ asignarTrabajador[i] == asignarTrabajador[j])
(Inicio[j] > Fin[i] \/ Inicio[j] < Inicio[i]);
                                            
% La duracion de la tarea debe ser la del trabajador asignado
constraint forall(t in TAREAS)(Fin[t] = Inicio[t] + Duraciones[t,asignarTrabajador[t]]-1); % resta 1 ya que la duración de una tarea se considera en términos de intervalos, donde el día de inicio cuenta como el primer día de trabajo y el día de finalización cuenta como el último día de trabajo

% Minimiza la duración máxima de construcción
solve minimize max(i in TAREAS)(Fin[i]);

% Salida en formato tabla
output ["Tarea\t| A\tB\tC\tD\tE\tF\tG\tH\tI\tJ "] ++ ["\n"];
output ["Inicio\t| "] ++ ["\(Inicio[i])\t" | i in TAREAS] ++ ["\n"];
output ["Fin\t| "] ++ ["\(Fin[i])\t" | i in TAREAS] ++ ["\n"];
output ["Trabaj\t| "] ++ ["\(asignarTrabajador[i])\t" | i in TAREAS] ++ ["\n"];
output ["Duracion de construcción: " ++ show(Fin[N]) ++ " días."];