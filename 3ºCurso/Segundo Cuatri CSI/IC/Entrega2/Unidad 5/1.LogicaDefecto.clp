;;;;;;;;;; EJERCICIO 1 DE LA PRACTICA 4 ;;;;;;;;;;
;;;;;;; Implementar en CLISP un sistema que pregunte por un animal ;;;;;;;
;;;;;;; y responda si ese animal vuela o no, basado en el siguiente conocimiento ;;;;;;;

;;;; Las aves casi todas vuelan ;;;;
;;;; La mayor parte de los animales no vuelan ;;;;
;;;; Las aves y los mamiferos son animales ;;;;
;;;; Los gorriones, las palomas, las aguilas y los pingüinos son aves ;;;;
;;;; La vaca, los perros y los caballos son mamiferos ;;;;
;;;; Los pingüiños no vuelan ;;;;

;;;;; Lógica por Defecto ;;;;;
;;; Casi todas las aves vuelan -> Por defecto un ave vuela ;;;
;;; La mayor parte de los animales no vuelan -> a falta de informacion se puede asumir que un pájaro NO vuela ;;;


;;; Para reprensentar las animales se utilizan los siguientes hechos ;;;
;; (ave ?x) ?x es un ave ;;
;; (animal ?y) ?y es un animal ;;
;; (vuela ?y si|no seguro|por_defecto) ?y si vuela|no vuela y se sabe o bien con certeza(seguro)|por defecto que es el conocimiento base ;;

(deffacts datos
    (ave aguila)
    (ave gorrion)
    (ave paloma)
    (ave pinguino)
    (mamifero vaca)
    (mamifero perro)
    (mamifero caballo)
    (vuela pinguino no seguro)
)

;; Un ave es un animal ;;
;; Se añade la explicacion ;;
(defrule aves_son_animales
    (ave ?x)
    =>
    (assert (animal ?x))
    (bind ?expl (str-cat "sabemos que un/a " ?x " es un animal porque las aves son un tipo de animal"))
    (assert (explicacion animal ?x ?expl))
)

; Los mamiferos son animales (A3)
(defrule mamiferos_son_animales
   (mamifero ?x)
   =>
   (assert (animal ?x))
   (bind ?expl (str-cat "sabemos que un/a " ?x " es un animal porque los
   mamiferos son un tipo de animal"))
   (assert (explicacion animal ?x ?expl))
)
; añadimos un hecho que contiene la explicación de la deducción

;;; Casi todos las aves vuelan --> puedo asumir por defecto que las aves vuelan
; Asumimos por defecto
(defrule ave_vuela_por_defecto
   (declare (salience -1)) ; para disminuir probabilidad de añadir erróneamente
   (ave ?x)
   =>
   (assert (vuela ?x si por_defecto))
   (bind ?expl (str-cat "asumo que un/a " ?x " vuela, porque casi todas las aves
   vuelan"))
   (assert (explicacion vuela ?x ?expl))
)

; Retractamos cuando hay algo en contra
(defrule retracta_vuela_por_defecto
   (declare (salience 1))
   ; para retractar antes de inferir cosas erroneamente
   ?f<- (vuela ?x ?r por_defecto)
   (vuela ?x ?s seguro)
   =>
   (retract ?f)
   (bind ?expl (str-cat "retractamos que un/a " ?x " " ?r " vuela por defecto, porque
   sabemos seguro que " ?x " " ?s " vuela"))
   (assert (explicacion vuela ?x ?expl))
)

; La mayor parte de los animales no vuelan -> Puede interesar asumir que por defecto no vuela un animal
(defrule mayor_parte_animales_no_vuelan
   (declare (salience -2)) ;;;; es mas arriesgado, mejor después de otros razonamientos
   (animal ?x)
   (not (vuela ?x ? ?))
   =>
   (assert (vuela ?x no por_defecto))
   (bind ?expl (str-cat "asumo que " ?x " no vuela, porque la mayor parte de los animales no vuelan"))
   (assert (explicacion vuela ?x ?expl))
)


;;;;;;;;;; A PARTIR DE AQUI COMIENZA EL EJERCICIO ;;;;;;;;;;
;;;;;; Completar esta base de conocimiento para que el sistema pregunte ;;;;;;
;;;;;; que de qué animal esta interesado en obtener información sobre si vuela y: ;;;;;;
;;;; - si es uno de los recogidos en el conocimiento indique si vuela o no ;;;;
;;;; - si no es uno de los recogidos pregunte si es un ave o un mamífero y según la respuesta indique si vuela o no ;;;;
;;;; - Si no se sabe si es un mamífero o un ave también responda según el razonamiento por defecto indicadO ;;;;


;; Un usuario interesado en un animal ;;
(defrule pregunta
    =>
    (printout t "Sobre que animal quieres saber si vuela o no?" crlf)
    (assert (pregunta (read)))

)

;; Se ha introducido un animal que no está recogido en la base del conocimiento actual
(defrule animal_desconocido
    (declare (salience -100)) ;; Es la ultima opcion que se ejecuta si no se ha hecho ninguna de las anteriores
    ?p <- (pregunta ?x) ; Se extrae el identificador del hecho para eliminarlo
    (not (or (mamifero ?x) (ave ?x))) ;; Si el animal no es ni un ave ni un mamifero
    =>
    (printout t " No se reconoce al animal introducido (" ?x "). Es mamifero o ave?" crlf)
    (assert (respuesta ?x (read))) ;; Se pregunta para almacenarlo
    (retract ?p)
)

;; El animal desconocido se guarda como un mamifero y se registra en la base del conocimiento
;; Se crea el hecho de pregunta ?x para seguir con el proceso
(defrule registrar_mamifero
    (declare (salience -100))
    ?r <- (respuesta ?x mamifero) ;; Si el usuario introdujo que ?x era un mamifero
    =>
    (assert (mamifero ?x))
    (assert (pregunta ?x)) ;; Se agrega de nuevo la pregunta inicial ahora que se ha registrado el animal
    (retract ?r)
)

;; El animal desconocido se guarda como un ave
(defrule registrar_ave
    (declare (salience -100))
    ?r <- (respuesta ?x ave) ;; Si el usuario introdujo que ?x era un ave
    =>
    (assert (ave ?x))
    (assert (pregunta ?x)) ;; Se agrega de nuevo la pregunta inicial ahora que se ha registrado el animal
    (retract ?r)
)

; Si con la respuesta dada no se sabe si es un ave o mamifero, se guarda como un animal a secas
(defrule animal_por_defecto
   (declare (salience -100))
   ?r <- (respuesta ?x ?s)
   (not (eq ?s mamifero))
   (not (eq ?s ave))
   =>
   (assert (animal ?x) (pregunta ?x))
   (retract ?r)
)

;Es un mamifero
(defrule siendo_mamifero
   (declare (salience -100))
   ?p <- (pregunta ?x) ;; Se coge el identificador de la pregunta
   (mamifero ?x) ;; ?x es un hecho guardado como mamifero
   (explicacion vuela ?x ?expl)
   =>
   (printout t ?x " es un mamifero y " ?expl crlf)
   (assert (correcto ?x))
   (retract ?p)
)

; Es un ave
(defrule siendo_ave
   (declare (salience -100))
   ?p <- (pregunta ?x)
   (ave ?x) ;; ?x es un hecho guardado como ave
   (explicacion vuela ?x ?expl)
   =>
   (printout t ?x " es un ave y " ?expl crlf)
   (assert (correcto ?x))
   (retract ?p)
)

; Es un animal pero sin categorizar en mamifero o ave
(defrule siendo_desconocido
   (declare (salience -100))
   ?p <- (pregunta ?x)
   (animal ?x)
   (not (ave ?x)) ;; Todos son animales, pero no está registrado como ave
   (not (mamifero ?x)) ;; Ni como mamifero
   (explicacion vuela ?x ?expl)
   =>
   (printout t ?x " es un animal y " ?expl crlf)
   (assert (correcto ?x))
   (retract ?p)
)