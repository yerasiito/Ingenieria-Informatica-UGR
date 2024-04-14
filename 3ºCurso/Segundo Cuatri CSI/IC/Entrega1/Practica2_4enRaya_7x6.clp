;;;; REALIZADO POR: Yeray Lopez Ramirez ;;;;;
;;;;           DNI: 26050768W		    ;;;;;

;;;;;;; JUGADOR DE 4 en RAYA ;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; 
;;;;;;;;;; Version de 4 en raya clásico: Tablero de 6x7, donde se introducen fichas por arriba
;;;;;;;;;;;;;;;;;;;;;;; y caen hasta la posicion libre mas abajo
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;; Hechos para representar un estado del juego

;;;;;;; (Turno M|J)   representa a quien corresponde el turno (M maquina, J jugador)
;;;;;;; (Tablero Juego ?i ?j _|M|J) representa que la posicion i,j del tablero esta vacia (_), o tiene una ficha propia (M) o tiene una ficha del jugador humano (J)

;;;;;;;;;;;;;;;; Hechos para representar estado del analisis
;;;;;;; (Tablero Analisis Posicion ?i ?j _|M|J) representa que en el analisis actual la posicion i,j del tablero esta vacia (_), o tiene una ficha propia (M) o tiene una ficha del jugador humano (J)
;;;;;;; (Sondeando ?n ?i ?c M|J)  ; representa que estamos analizando suponiendo que la ?n jugada h sido ?i ?c M|J
;;;

;;;;;;;;;;;;; Hechos para representar una jugadas

;;;;;;; (Juega M|J ?columna) representa que la jugada consiste en introducir la ficha en la columna ?columna 


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; INICIALIZAR ESTADO


(deffacts Estado_inicial
    (Tablero Juego 1 1 _) (Tablero Juego 1 2 _) (Tablero Juego 1 3 _) (Tablero Juego  1 4 _) (Tablero Juego  1 5 _) (Tablero Juego  1 6 _) (Tablero Juego  1 7 _)
    (Tablero Juego 2 1 _) (Tablero Juego 2 2 _) (Tablero Juego 2 3 _) (Tablero Juego 2 4 _) (Tablero Juego 2 5 _) (Tablero Juego 2 6 _) (Tablero Juego 2 7 _)
    (Tablero Juego 3 1 _) (Tablero Juego 3 2 _) (Tablero Juego 3 3 _) (Tablero Juego 3 4 _) (Tablero Juego 3 5 _) (Tablero Juego 3 6 _) (Tablero Juego 3 7 _)
    (Tablero Juego 4 1 _) (Tablero Juego 4 2 _) (Tablero Juego 4 3 _) (Tablero Juego 4 4 _) (Tablero Juego 4 5 _) (Tablero Juego 4 6 _) (Tablero Juego 4 7 _)
    (Tablero Juego 5 1 _) (Tablero Juego 5 2 _) (Tablero Juego 5 3 _) (Tablero Juego 5 4 _) (Tablero Juego 5 5 _) (Tablero Juego 5 6 _) (Tablero Juego 5 7 _)
    (Tablero Juego 6 1 _) (Tablero Juego 6 2 _) (Tablero Juego 6 3 _) (Tablero Juego 6 4 _) (Tablero Juego 6 5 _) (Tablero Juego 6 6 _) (Tablero Juego 6 7 _)
    (Jugada 0)
)

(defrule Elige_quien_comienza
=>
    (printout t "Quien quieres que empieze: (escribe M para la maquina o J para empezar tu) ")
    (assert (Turno (read)))
)

;;;;;;;;;;;;;;;;;;;;;;; MUESTRA POSICION ;;;;;;;;;;;;;;;;;;;;;;;
(defrule muestra_posicion
    (declare (salience 10))
    (muestra_posicion)
    (Tablero Juego 1 1 ?p11) (Tablero Juego 1 2 ?p12) (Tablero Juego 1 3 ?p13) (Tablero Juego 1 4 ?p14) (Tablero Juego 1 5 ?p15) (Tablero Juego 1 6 ?p16) (Tablero Juego 1 7 ?p17)
    (Tablero Juego 2 1 ?p21) (Tablero Juego 2 2 ?p22) (Tablero Juego 2 3 ?p23) (Tablero Juego 2 4 ?p24) (Tablero Juego 2 5 ?p25) (Tablero Juego 2 6 ?p26) (Tablero Juego 2 7 ?p27)
    (Tablero Juego 3 1 ?p31) (Tablero Juego 3 2 ?p32) (Tablero Juego 3 3 ?p33) (Tablero Juego 3 4 ?p34) (Tablero Juego 3 5 ?p35) (Tablero Juego 3 6 ?p36) (Tablero Juego 3 7 ?p37)
    (Tablero Juego 4 1 ?p41) (Tablero Juego 4 2 ?p42) (Tablero Juego 4 3 ?p43) (Tablero Juego 4 4 ?p44) (Tablero Juego 4 5 ?p45) (Tablero Juego 4 6 ?p46) (Tablero Juego 4 7 ?p47)
    (Tablero Juego 5 1 ?p51) (Tablero Juego 5 2 ?p52) (Tablero Juego 5 3 ?p53) (Tablero Juego 5 4 ?p54) (Tablero Juego 5 5 ?p55) (Tablero Juego 5 6 ?p56) (Tablero Juego 5 7 ?p57)
    (Tablero Juego 6 1 ?p61) (Tablero Juego 6 2 ?p62) (Tablero Juego 6 3 ?p63) (Tablero Juego 6 4 ?p64) (Tablero Juego 6 5 ?p65) (Tablero Juego 6 6 ?p66) (Tablero Juego 6 7 ?p67)
=>
    (printout t "####################" crlf)
    (printout t "# 1  " ?p11 " " ?p12 " " ?p13 " " ?p14 " " ?p15 " " ?p16 " " ?p17 " #" crlf)
    (printout t "# 2  " ?p21 " " ?p22 " " ?p23 " " ?p24 " " ?p25 " " ?p26 " " ?p27 " #" crlf)
    (printout t "# 3  " ?p31 " " ?p32 " " ?p33 " " ?p34 " " ?p35 " " ?p36 " " ?p37 " #" crlf)
    (printout t "# 4  " ?p41 " " ?p42 " " ?p43 " " ?p44 " " ?p45 " " ?p46 " " ?p47 " #" crlf)
    (printout t "# 5  " ?p51 " " ?p52 " " ?p53 " " ?p54 " " ?p55 " " ?p56 " " ?p57 " #" crlf)
    (printout t "# 6  " ?p61 " " ?p62 " " ?p63 " " ?p64 " " ?p65 " " ?p66 " " ?p67 " #" crlf)
    (printout t "#                  #" crlf "#    1 2 3 4 5 6 7 #" crlf)
    (printout t "####################" crlf)
)


;;;;;;;;;;;;;;;;;;;;;;; RECOGER JUGADA DEL CONTRARIO ;;;;;;;;;;;;;;;;;;;;;;;
(defrule mostrar_posicion
    (declare (salience 9999))
    (Turno J)
=>
    (assert (muestra_posicion))
)

(defrule jugada_contrario
    ?f <- (Turno J)
=>
    (printout t "en que columna introduces la siguiente ficha? ")
    (assert (Juega J (read)))
    (retract ?f)
)

(defrule juega_contrario_check_entrada_correcta
    (declare (salience 1))
    ?f <- (Juega J ?c)
    (test (and (neq ?c 1) (and (neq ?c 2) (and (neq ?c 3) (and (neq ?c 4) (and (neq ?c 5) (and (neq ?c 6) (neq ?c 7))))))))
=>
    (printout t "Tienes que indicar un numero de columna: 1,2,3,4,5,6 o 7" crlf)
    (retract ?f)
    (assert (Turno J))
)

(defrule juega_contrario_check_columna_libre
    (declare (salience 1))
    ?f <- (Juega J ?c)
    (Tablero Juego 1 ?c ?X) 
    (test (neq ?X _))
=>
    (printout t "Esa columna ya esta completa, tienes que jugar en otra" crlf)
    (retract ?f)
    (assert (Turno J))
)

(defrule juega_contrario_actualiza_estado
    ?f <- (Juega J ?c)
    ?g <- (Tablero Juego ?i ?c _)
    (Tablero Juego ?j ?c ?X) 
    (test (= (+ ?i 1) ?j))
    (test (neq ?X _))
=>
    (retract ?f ?g)
    (assert (Turno M) (Tablero Juego ?i ?c J))
)

(defrule juega_contrario_actualiza_estado_columna_vacia
    ?f <- (Juega J ?c)
    ?g <- (Tablero Juego 6 ?c _)
=>
    (retract ?f ?g)
    (assert (Turno M) (Tablero Juego 6 ?c J))
)


;;;;;;;;;;; ACTUALIZAR  ESTADO TRAS JUGADA DE CLIPS ;;;;;;;;;;;;;;;;;;

(defrule juega_clisp_actualiza_estado
    ?f <- (Juega M ?c)
    ?g <- (Tablero Juego ?i ?c _)
    (Tablero Juego ?j ?c ?X) 
    (test (= (+ ?i 1) ?j))
    (test (neq ?X _))
=>
    (retract ?f ?g)
    (assert (Turno J) (Tablero Juego ?i ?c M))
)

(defrule juega_clisp_actualiza_estado_columna_vacia
    ?f <- (Juega M ?c)
    ?g <- (Tablero Juego 6 ?c _)
=>
    (retract ?f ?g)
    (assert (Turno J) (Tablero Juego 6 ?c M))
)

;;;;;;;;;;; CLIPS JUEGA SIN CRITERIO ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defrule elegir_jugada_aleatoria
    (declare (salience -9998))
    ?f <- (Turno M)
=>
    (assert (Jugar (random 1 7)))
    (retract ?f)
)

(defrule comprobar_posible_jugada_aleatoria
    ?f <- (Jugar ?c)
    (Tablero Juego 1 ?c M|J)
=>
    (retract ?f)
    (assert (Turno J))
)

(defrule clisp_juega_sin_criterio
    (declare (salience -9999))
    ?f<- (Jugar ?c)
=>
    (printout t "JUEGO en la columna (sin criterio) " ?c crlf)
    (retract ?f)
    (assert (Juega M ?c))
    (printout t "Juego sin razonar, que mal"  crlf) 
)


;;;;;;;;;;;;;;;;;;;;;;;;;;;  Comprobar si hay 4 en linea ;;;;;;;;;;;;;;;;;;;;;

(defrule cuatro_en_linea_horizontal
    (declare (salience 9999))
    (Tablero ?t ?i ?c1 ?jugador)
    (Tablero ?t ?i ?c2 ?jugador) 
    (test (= (+ ?c1 1) ?c2))
    (Tablero ?t ?i ?c3 ?jugador)
    (test (= (+ ?c1 2) ?c3))
    (Tablero ?t ?i ?c4 ?jugador)
    (test (= (+ ?c1 3) ?c4))
    (test (or (eq ?jugador M) (eq ?jugador J) ))
=>
    (assert (Cuatro_en_linea ?t ?jugador horizontal ?i ?c1))
)

(defrule cuatro_en_linea_vertical
    (declare (salience 9999))
    ?f <- (Turno ?X)
    (Tablero ?t ?i1 ?c ?jugador)
    (Tablero ?t ?i2 ?c ?jugador)
    (test (= (+ ?i1 1) ?i2))
    (Tablero ?t ?i3 ?c  ?jugador)
    (test (= (+ ?i1 2) ?i3))
    (Tablero ?t ?i4 ?c  ?jugador)
    (test (= (+ ?i1 3) ?i4))
    (test (or (eq ?jugador M) (eq ?jugador J) ))
=>
    (assert (Cuatro_en_linea ?t ?jugador vertical ?i1 ?c))
)

(defrule cuatro_en_linea_diagonal_directa
    (declare (salience 9999))
    ?f <- (Turno ?X)
    (Tablero ?t ?i ?c ?jugador)
    (Tablero ?t ?i1 ?c1 ?jugador)
    (test (= (+ ?i 1) ?i1))
    (test (= (+ ?c 1) ?c1))
    (Tablero ?t ?i2 ?c2  ?jugador)
    (test (= (+ ?i 2) ?i2))
    (test (= (+ ?c 2) ?c2))
    (Tablero ?t ?i3 ?c3  ?jugador)
    (test (= (+ ?i 3) ?i3))
    (test (= (+ ?c 3) ?c3))
    (test (or (eq ?jugador M) (eq ?jugador J) ))
=>
    (assert (Cuatro_en_linea ?t ?jugador diagonal_directa ?i ?c))
)

(defrule cuatro_en_linea_diagonal_inversa
    (declare (salience 9999))
    ?f <- (Turno ?X)
    (Tablero ?t ?i ?c ?jugador)
    (Tablero ?t ?i1 ?c1 ?jugador)
    (test (= (+ ?i 1) ?i1))
    (test (= (- ?c 1) ?c1))
    (Tablero ?t ?i2 ?c2  ?jugador)
    (test (= (+ ?i 2) ?i2))
    (test (= (- ?c 2) ?c2))
    (Tablero ?t ?i3 ?c3  ?jugador)
    (test (= (+ ?i 3) ?i3))
    (test (= (- ?c 3) ?c3))
    (test (or (eq ?jugador M) (eq ?jugador J) ))
=>
    (assert (Cuatro_en_linea ?t ?jugador diagonal_inversa ?i ?c))
)

;;;;;;;;;;;;;;;;;;;; DESCUBRE GANADOR
(defrule gana_fila
    (declare (salience 9999))
    ?f <- (Turno ?X)
    (Cuatro_en_linea Juego ?jugador horizontal ?i ?c)
=>
    (printout t ?jugador " ha ganado pues tiene cuatro en linea en la fila " ?i crlf)
    (retract ?f)
    (assert (muestra_posicion))
) 

(defrule gana_columna
    (declare (salience 9999))
    ?f <- (Turno ?X)
    (Cuatro_en_linea Juego ?jugador vertical ?i ?c)
=>
(printout t ?jugador " ha ganado pues tiene cuatro en linea en la columna " ?c crlf)
    (retract ?f)
    (assert (muestra_posicion))
) 

(defrule gana_diagonal_directa
    (declare (salience 9999))
    ?f <- (Turno ?X)
    (Cuatro_en_linea Juego ?jugador diagonal_directa ?i ?c)
=>
    (printout t ?jugador " ha ganado pues tiene cuatro en linea en la diagonal que empieza la posicion " ?i " " ?c   crlf)
    (retract ?f)
    (assert (muestra_posicion))
) 

(defrule gana_diagonal_inversa
    (declare (salience 9999))
    ?f <- (Turno ?X)
    (Cuatro_en_linea Juego ?jugador diagonal_inversa ?i ?c)
=>
    (printout t ?jugador " ha ganado pues tiene cuatro en linea en la diagonal hacia arriba que empieza la posicion " ?i " " ?c   crlf)
    (retract ?f)
    (assert (muestra_posicion))
) 


;;;;;;;;;;;;;;;;;;;;;;;  DETECTAR EMPATE

(defrule empate
    (declare (salience -9999))
    (Turno ?X)
    (Tablero Juego 1 1 M|J)
    (Tablero Juego 1 2 M|J)
    (Tablero Juego 1 3 M|J)
    (Tablero Juego 1 4 M|J)
    (Tablero Juego 1 5 M|J)
    (Tablero Juego 1 6 M|J)
    (Tablero Juego 1 7 M|J)
=>
    (printout t "EMPATE! Se ha llegado al final del juego sin que nadie gane" crlf)
)

;;;;;;;;;;;;;;;;;;;;;; CONOCIMIENTO EXPERTO ;;;;;;;;;;

;; Cuando un participante juega una ficha en una columna donde no hay nada (es decir sin importar la columna es la fila 6 y hay _)
(defrule ficha_cae_primera_fila
    (Tablero ?t ?f ?c _) ;; Si no hay ninguna ficha
    (test (eq ?f 6)) ;; Y es la priemra fila, porque la fila 6 es el LIMITE INFERIOR
=>
    (assert (caeria ?f ?c)) ;; Cae en la primera fila
)

;;;;;;; ATENCION !!!!! LA PRIORIDAD DE ACTUALIZAR EL ESTADO DEL TABLERO DE CLIP ES LA DE POR DEFECTO, 0 ;;;;;;;
;;;;;;; POR TANTO, ESTAS REGLAS TENDRÁN QUE TENER PRIORIDAD NEGATIVA, DE MÁS GRANDE A MENOR (Es decir, de -1 a -9999) ;;;;;;;
;;;;;;; De lo contrario, esto se revolvería ANTES de que CLIPS actualice

;;; Cuando un participante juega una ficha en una posicion donde no hay nada, ¿donde cae?
(defrule ficha_cae_vacio
    (Tablero ?t ?f ?c _) ;; No hay nada, entonces
    (anterior ?f ?c v ?f1 ?c1) ;; si en la anterior posicion a esa
    (Tablero ?t ?f1 ?c1 ?ficha) ;; Hay una ficha
    (test (or (eq ?ficha J) (eq ?ficha M))) ;; De algún participante, J ó M
=>
    (assert (caeria ?f ?c)) ;; Entones cae en el espacio vacío
)


;; Eliminar hechos de caeria cuando en esas posiciones ya hay una ficha colocada
(defrule no_caeria
    (Tablero ?t ?f ?c M|J) ; Si existe una posicion en el tablero (f,c) donde hay una ficha colocada
    ?no <- (caeria ?f ?c) ; Y es verdad que está registrado que una ficha puede caer en esa misma posicion si se juega
=>
    (retract ?no) ;; Se elimina ese hecho como cierto ya que es una posición ocupada
)

;;;; PRIMERO DE TODO NECESITAMOS SABER LAS POSICIONES SIGUIENTES Y ANTERIORES, para poder leer bien el tablero ;;;;
;#######################
;# _  _  _  _  _  _  _ #
;# _  _  _  _  _  _  _ #
;# _  _  _  _  _  _  _ #
;# _  _  _  _  _  _  _ #
;# v  _  d2 d1 _  _  _ #
;# v  d2 h  h  d1 _  _ #
;#######################
; v: vertical
; h: horizontal
; d1: diagonal abajo
; d2: diagonal arriba

;;;;; POSICIONES SIGUIENTES ;;;;;

;; Para saber cual es la siguiente posicion a la derecha dada una posicion
;; Si obtuviese por ej: Tablero Juego 1 2 M, entonces el hecho sería: 
;; La siguiente posición respecto (1,2) en Horizontal es (1,3)
(defrule siguiente_derecha
    (Tablero ?t ?f ?c ?X) ; Se recibe un tablero cualquiera con una posicion f c
    (test (< ?c 7)) ; Si es 7, no hay más tablero a la derecha
=> 
    (assert (siguiente ?f ?c h ?f (+ ?c 1))) ; inserta un hecho, la siguiente posicion a la derecha
)
;; Para saber cual es la siguiente posicion hacia arriba dada una posicion
;; OJO, subir en el tablero es restar filas.
(defrule siguiente_arriba
    (Tablero ?t ?f ?c ?X)
    (test (> ?f 1)) ; Si es fila 1, no hay más tablero arriba
=>
    (assert (siguiente ?f ?c v (- ?f 1) ?c))
)

;; Para saber cual es la siguiente posicion en diagonal hacia arriba dada una posicion
(defrule siguiente_diagonal_superior
    (Tablero ?t ?f ?c ?X)
    (test (> ?f 1)) ; Si es fila 1, no hay más tablero arriba
    (test (< ?c 7)) ; Si es columna 7, no hay más tableero a la derecha
=>
    (assert (siguiente ?f ?c d2 (- ?f 1) (+ ?c 1) ))
)

;; Para saber cual es la siguiente posicion en diagonal hacia abajo dada una posicion
(defrule siguiente_diagonal_inferior
    (Tablero ?t ?f ?c ?X)
    (test (< ?f 6)) ; Si es fila 6, no hay más tablero abajo
    (test (< ?c 7)) ; Si es columna 7, no hay más tablero a la derecha
=>
    (assert (siguiente ?f ?c d1 (+ ?f 1) (+ ?c 1) ))
)

;;;;; POSICIONES ANTERIORES ;;;;;

;; Para saber cual es la anterior posicion a la izquierda dada una posicion
(defrule anterior_izquierda
    (Tablero ?t ?f ?c ?X)
    (test (> ?c 1))
=>
    (assert (anterior ?f ?c h ?f (- ?c 1)))
)

;; Para saber cual es la anterior posicion hacia abajo dada una posicion
(defrule anterior_abajo
    (Tablero ?t ?f ?c ?X)
    (test (< ?f 6))
=>
    (assert (anterior ?f ?c v (+ ?f 1) ?c)) ; OJO, bajar en el tablero es sumar filas
)

;; Para saber cual es la anterior posicion en diagonal hacia arriba dada una posicion
(defrule anterior_diagonal_superior
    (Tablero ?t ?f ?c ?X)
    (test (> ?f 1)) ;; Porque va hacia arriba, de la fila 6 a la 1, mientras sea mayor que 1 se puede restar
    (test (> ?c 1))
=>
    (assert (anterior ?f ?c d2 (+ ?f 1) (- ?c 1) ))
)

;; Para saber cual es la anterior posicion en diagonal hacia abajo dada una posicion
(defrule anterior_diagonal_inferior
    (Tablero ?t ?f ?c ?X)
    (test (< ?f 6))
    (test (> ?c 1))
=>
    (assert (anterior ?f ?c d1 (- ?f 1) (- ?c 1)))
)

;;; Un jugador tiene dos fichas conectadas, no es necesario comprobar anterior (se duplicarían hechos)
(defrule tiene_dos_conectadas
    (Tablero ?t ?f ?c ?jugador) ; Tablero inicial
    (siguiente ?f ?c ?linea ?f1 ?c1) ; Existe una posicion siguiente a ese tablero inicial en cualquier direccion hacia delante
    (Tablero ?t ?f1 ?c1 ?jugador) ; Obtiene jugador para comprobar después que no sea _

    (test (or (eq ?jugador M) (eq ?jugador J))) ;; Se comprueba que la ficha sea de alguno de los participantes, no vale _
=>
    (assert (conectado2 ?t ?linea ?f ?c ?f1 ?c1 ?jugador)) ;; Donde ?linea indica si es horizontal, vertical, diagonal superior o inferior
    ;;DEBUG;;
    ; (printout t "-Hay 2 fichas de " ?jugador " conectadas en " ?linea ": ")
    ; (printout t "(" ?f "," ?c ") y (" ?f1 "," ?c1 ")" crlf)
)

;;; Un jugador tiene 3 fichas conectadas hacia delante
;; Se parte de que ya exista un hecho como verdad "CONECTADO2"
(defrule tiene_tres_conectadas
    (Tablero ?t ?f ?c ?jugador) ; Tablero inicial
    (conectado2 ?t ?linea ?f ?c ?f1 ?c1 ?jugador) ;; En una celda (f, c) haya una conexión con (f1, c1)
    (siguiente ?f1 ?c1 ?linea ?f2 ?c2) ;; Que exista una posición siguiente válida en la misma direccion (?linea)
    (Tablero ?t ?f2 ?c2 ?jugador) ;; Obtiene jugador para comprobar después que no sea _
    (test (or (eq ?jugador J) (eq ?jugador M))) ;; Y que la ficha sea de un participante
=>
    (assert (conectado3 ?t ?linea ?f ?c ?f2 ?c2 ?jugador)) ;; Se crea un hecho que recoge la linea desde la ficha inicial hasta la ultima
    ;;DEBUG;;
    ; (printout t "-Hay 3 fichas de " ?jugador " conectadas en " ?linea ": ")
    ; (printout t "(" ?f "," ?c "),(" ?f1 "," ?c1 ") y (" ?f1 "," ?c1 ")" crlf)
)

;; Las fichas conectadas pierden valor si no es posible continuar la linea
;; Si se tiene JMMJ ya no interesa saber que están conectadas MM porque no se puede hacer nunca un conecta 3
;; Si por delante puede hacerte un 3 en raya, o por detras, se mantiene, puede interesa
(defrule eliminar_tiene_dos_conectadas
    ?con2 <- (conectado2 ?t ?linea ?f ?c ?f1 ?c1 ?jugador) ;; Si un jugador tiene 2 fichas conectadas
    (siguiente ?f1 ?c1 ?linea ?f2 ?c2) ;; Se coge la siguiente en linea con las conectadas
    (Tablero ?t ?f2 ?c2 ?ficha) ;; Y en esa posicion hay una ficha
    (test (not (eq ?jugador ?ficha))) ;; Que no son la misma. Es decir hay algo tal que _ _ _ M M M J
    (test (not (eq ?ficha _))) ;; Que no sea vacía (_)

    (anterior ?f ?c ?linea ?f3 ?c3) ;; Lo mismo pero con la anterior
    (Tablero ?t ?f3 ?c3 ?ficha)
    (test (not (eq ?jugador ?ficha)))  ;; Que no son la misma. Es decir hay algo tal que _ _ J M M _
    (test (not (eq ?ficha _)))
=>
    ;; Entonces ese conectado no interesa que exista porque está bloqueado y nunca ganará
    (retract ?con2)
)

;; Es el mismo caso anterior, pero ahora con tres fichas conectadas
;; Si se tiene JMMMJ ya no interesa saber que están conectadas porque la jugada ha sido bloqueada
(defrule eliminar_tiene_tres_conectadas
    ?con3 <- (conectado3 ?t ?linea ?f ?c ?f1 ?c1 ?jugador) ;; Si un jugador tiene 3 fichas conectadas
    (siguiente ?f1 ?c1 ?linea ?f2 ?c2) ;; Se coge la siguiente en linea con las conectadas
    (Tablero ?t ?f2 ?c2 ?ficha) ; Obtiene la "ficha" siguiente
    (test (not (eq ?jugador ?ficha))) ;; Que no son la misma. Es decir hay algo tal que _ _ _ M M M J
    (test (not (eq ?ficha _))) ;; Que no sea vacía (_)
    
    (anterior ?f ?c ?linea ?f3 ?c3) ;; Y tambien, la anterior al inicio de la conexion
    (Tablero ?t ?f3 ?c3 ?ficha)
    (test (not (eq ?jugador ?ficha)))  ;; Que no son la misma. Es decir hay algo tal que _ _ J M M M _
    (test (not (eq ?ficha _)))
    
=>
    ;; Entonces ese conectado no interesa que exista porque está bloqueado y nunca ganará
    (retract ?con3)
)

(defrule hay_hueco_horizontal
    (Tablero ?t ?f ?c _)

    (siguiente ?f ?c h ?f2 ?c2) ;; Los huecos serán solo en horizontal o que coincida la diagonal, no puede haber un hueco en mitad de la columna
    (Tablero ?t ?f2 ?c2 ?jugador) ;; En la siguiente posicion horizontal hay una ficha de un participante
    
    (anterior ?f ?c h ?f3 ?c3) ;; Y en la posición anterior horizontal
    (Tablero ?t ?f3 ?c3 ?jugador) ;; También hay una ficha de un participante
    
    (caeria ?f ?c) ;; Hay que comprobar que al jugar en la columna ?c la ficha caería en dicha posición.
    (test (or (eq ?jugador M) (eq ?jugador J))) ;; La ficha de ?jugador debe ser de M ó J no otro espacio en blanco
=>
    (assert (hueco ?f ?c ?jugador))
)

;; Las diagonales hay que tratarlas de una forma especial ya que no sirve con hacer siguiente-anterior
;####################
;# 1 _ _ _ _ _ _ _  #
;# 2 _ _ _ _ _ _ _  #
;# 3 _ _ _ _ _ _ _  #
;# 4 J _ _ _ _ _ _  #
;# 5 M x _ _ _ _ _  #
;# 6 M M J _ _ _ _  #
;#   1 2 3 4 5 6 7  #
;####################

;; En un tablero como el anterior, se aprecia un hueco entre (4, 1) y (6, 3) en la posicion
;; Pero tal y como está construido el programa la posicion siguiente en diagonal inferior sí es (6, 3)
;; Pero la posición anterior a diagonal inferior no es (4, 1) si no (6, 1)
;; Por esto mismo no basta con hacer que siguiente y anterior compartan ?linea hay que tratarlo de forma especial

(defrule hay_hueco_diagonal_inferior
    (Tablero ?t ?f ?c _) 
    ;; Se recuerda que d2 es diagonal hacia arriba y d1 es diagonal hacia abajo
    (siguiente ?f ?c d1 ?f2 ?c2) ;; Se coge la posición siguiente en diagonal inferior del punto a analizar (f, c) {se cogerá (6, 3)}
    (Tablero ?t ?f2 ?c2 ?jugador) ;; Obtiene ficha de participante
    (anterior ?f ?c d2 ?f3 ?c3) ;; Pero para que haga la diagonal, la otra que interesa es la anterior pero hacia arriba (4, 1)
    (Tablero ?t ?f3 ?c3 ?jugador) ;; También hay una ficha de un participante
    (caeria ?f ?c)

    (test (or (eq ?jugador M) (eq ?jugador J))) ;; La ficha de ?jugador debe ser de M ó J no otro espacio en blanco
=>
    (assert (hueco ?f ?c ?jugador))
)

;####################
;# 1 _ _ _ _ _ _ _  #
;# 2 _ _ _ _ _ _ _  #
;# 3 _ _ _ _ _ _ _  #
;# 4 _ _ M _ _ _ _  #
;# 5 _ x J _ _ _ _  #
;# 6 M M J _ _ _ _  #
;#   1 2 3 4 5 6 7  #
;####################

;; Hay que recoger las posiciones para formar la diagonal superior
(defrule hay_hueco_superior_diagonal_superior
    (Tablero ?t ?f ?c _)
    (siguiente ?f ?c d2 ?f2 ?c2) ;; Se coge la posición siguiente en diagonal inferior del punto a analizar (f, c) {se cogerá (4, 3)}
    (Tablero ?t ?f2 ?c2 ?jugador) ;; En la siguiente posicion horizontal hay una ficha de un participante
    (anterior ?f ?c d1 ?f3 ?c3) ;; Pero para que haga la diagonal, la otra que interesa es la anterior pero hacia abajo (6, 1)
    (Tablero ?t ?f3 ?c3 ?jugador) ;; También hay una ficha de un participante
    (caeria ?f ?c) ;; Hay que comprobar que al jugar en la columna ?c la ficha caería en dicha posición.
    
    (test (or (eq ?jugador M) (eq ?jugador J))) ;; La ficha de ?jugador debe ser de M ó J no otro espacio en blanco
=>
    (assert (hueco ?f ?c ?jugador))
)

;; Un jugador ganaria si juega en esta columna
(defrule se_ganaria_siguiente
    (conectado3 ?t ?linea ?f ?c ?f2 ?c2 ?jugador) ;; Si un jugador tiene TRES fichas conectadas
    (siguiente ?f2 ?c2 ?linea ?f3 ?c3) ;; Mira si hay posicion libre antes o después  
    (Tablero ?t ?f3 ?c3 _) ;; Y esa posición está vacía
    (caeria ?f3 ?c3) ;; y al jugar una ficha en esa columna, caeria en la posición deseada
=>
    (assert (ganaria ?jugador ?f3 ?c3)) ;; El participante ganaría si juega en la columna c3 (se indica la fila para evitar errores)
)

(defrule se_ganaria_anterior
    (conectado3 ?t ?linea ?f ?c ?f2 ?c2 ?jugador) ;; Si un jugador tiene TRES fichas conectadas
    (anterior ?f ?c ?linea ?f3 ?c3) ;; Mira si hay posicion libre antes o después  
    (Tablero ?t ?f3 ?c3 _) ;; Y esa posición está vacía
    (caeria ?f3 ?c3) ;; y al jugar una ficha en esa columna, caeria en la posición deseada
=>
    (assert (ganaria ?jugador ?f3 ?c3)) ;; El participante ganaría si juega en la columna c3 (se indica la fila para evitar errores)
)

;; Es necesario eliminarla, ya que si no, la máquina se obsesionaría en echar ficha siempre en esa columna
(defrule eliminar_se_ganaria
    ?g <- (ganaria ?jugador ?f ?c)
    (Tablero ?t ?f ?c M|J) ;; Si se registró una jugada maestra en una columna pero fue tapada
    ;; No importa mucho quien la tapó, si ?jugador = J y la tapó J, entonces ha ganado y el juego termina, si la tapó M entonces se elimina
=>
    (retract ?g)
)

;;;; Para indicar que la máquina va a jugar es OBLIGATORIO hacerlo de la forma siguiente: ;;;;

; (declare (salience n)) donde n sea mayor que -9999, para no usar jugadas aleatorias y además darle preferencias a jugadas más importantes
; ?turno <- (Turno M) ;; Para coger el identificador de que es el turno de la máquina porque luego HAY QUE BORRARLO para dar paso al turno del JUGADOR
; hechos que se quieren comprobar, como conectado(...) o ganaria(...)
; =>
; (assert (Juega M ?c)) ;; Con esto la máquina jugará en la colunma ?c cuyo valor será el que interese tras haber comprobado los hechos
; (retract ?turno) ;; Hay que quitar que la máquina ya ha jugado, para dar paso al jugador J

;;;;;;;; JUGADA GANADORA ;;;;;;;;
(defrule jugada_ganadora
    (declare (salience -50))
    ?turno <- (Turno M) ;; Si es el turno de la máquina
    (ganaria M ?f ?c) ;; Y la máquina ganaría si juega en esa posición
=>
    (assert (Juega M ?c)) ;; Se juega en esa columna para ganar
    (retract ?turno)
    (printout t "JUGADA GANADORA: Columna " ?c crlf)
)

;; Si el jugador ganase en su siguiente jugada, se debe impedir a toda costa
(defrule jugada_ganadora_enemiga
    (declare (salience -100)) ;; Menos que la jugada maestra porque si la Máquina tiene la opción de ganar en un movimiento, debe hacerlo
    ?turno <- (Turno M)
    (ganaria J ?f ?c) ;; Es el Jugador el que gana
=>
    (assert (Juega M ?c)) ;; Se juega en esa columna para evitar la victoria del jugador
    (retract ?turno)
    (printout t "NO TAN RAPIDO CRACK: Columna " ?c crlf)
)

;;; Si M tiene ya dos fichas conectadas y es posible jugar en una posición que haría conectar 3 fichas
(defrule jugada_conecta_tres_siguiente
    (declare (salience -150))
    ?turno <- (Turno M)
    (conectado2 ?t ?linea ?f ?c ?f1 ?c1 M) ;; Y tiene dos conectadas
    (siguiente ?f1 ?c1 ?linea ?f2 ?c2) ;; Y existe una posición siguiente para conectarla
    (caeria ?f2 ?c2) ;; Y existe la posibilidad de que la ficha caiga en esa posición al jugar esa columna
=>
    (assert (Juega M ?c2)) ;; La máquina juega en la columna ?c2
    (retract ?turno)
    (printout t "JUGADA CONECTA 3 SIGUIENTE: Columna " ?c2 crlf)

)

;; Comprueba que pueda conectar 3 fichas colocando en la columna anterior
;; Esta regla es necesaria ya que puede ser que hacia delante no puede hacer un conectado 3, pero sí que pueda hacia atrás
(defrule jugada_conecta_tres_anterior
    (declare (salience -150))
    ?turno <- (Turno M) 
    (conectado2 ?t ?linea ?f ?c ?f1 ?c1 M) ;; Y tiene dos conectadas
    (anterior ?f ?c ?linea ?f2 ?c2) ;; Y existe una posición anterior para conectarla (no está en el limite del tablero)
    (caeria ?f2 ?c2) ;; Y existe la posibilidad de que la ficha caiga en esa posición al jugar esa columna
=>
    (assert (Juega M ?c2)) ;; La máquina juega en la columna ?c2
    (retract ?turno)
    (printout t "JUGADA CONECTA 3 ANTERIOR: Columna " ?c2 crlf)
)

;;; Jugada donde se rellena un hueco de la Maquina
;;; Por ejemplo en una fila así: _ _ _ M _ M _ , Si M jugase en la columna 5, rellenaría un hueco y crearía un 3 en raya
(defrule jugada_hueco
    (declare (salience -350))
    ?turno <- (Turno M)
    ?hu <- (hueco ?f ?c M)  
=>
    (assert (Juega M ?c))
    (retract ?turno)
    (retract ?hu)
    (printout t "JUGADA HUECO: Columna " ?c crlf)
)

;; Si hay un hueco en blanco pero a izquierda y derecha hay una ficha del jugador
(defrule jugada_hueco_enemigo
    (declare (salience -120)) ;; Interesa que el otro jugador no rellene sus huecos y una ficha
    ?turno <- (Turno M)
    ?hu <- (hueco ?f ?c J)
=>
    (assert (Juega M ?c))
    (retract ?hu)
    (retract ?turno)
    (printout t "ME ROBO TU HUECO: Columna " ?c crlf)
)

;; Se intenta conectar 2 fichas M
(defrule jugada_conecta_dos_anterior
    (declare (salience -400)) ;; Prioridad pequeña, es un movimiento que se hace si no se puede hacer otros mejores
    ?turno <- (Turno M)
    (Tablero Juego ?f ?c _) ;; Si es posible jugar ahí
    (caeria ?f ?c)

    (siguiente ?f ?c ?linea ?f2 ?c2) ;; La posición siguiente es valida
    (Tablero Juego ?f2 ?c2 M) ;; Y hay una ficha de la máquina. Es buena jugada porque uniría dos fichas
=>
    (assert (Juega M ?c))
    (retract ?turno)
    (printout t "JUGADA CONECTA 2 ANTERIOR: Columna " ?c crlf)
)

(defrule jugada_conecta_dos_siguiente
    (declare (salience -400)) ;; Prioridad pequeña
    ?turno <- (Turno M)
    (Tablero Juego ?f ?c _) ;; Si es posible jugar ahí
    (caeria ?f ?c)

    (anterior ?f ?c ?linea ?f2 ?c2) ;; La posición anterior es valida
    (Tablero Juego ?f2 ?c2 M) ;; Y hay una ficha de la máquina. Es buena jugada porque uniría dos fichas
=>
    (assert (Juega M ?c))
    (retract ?turno)
    (printout t "JUGADA CONECTA 2 SIGUIENTE: Columna " ?c crlf)
)