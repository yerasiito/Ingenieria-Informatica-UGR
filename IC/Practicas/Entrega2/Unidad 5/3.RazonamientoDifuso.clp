;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;   Modulo ejecutar sistema difuso con varias variables de entrada   ;;;;;;;
;;;;;       MODULO CALCULO FUZZY (modulo calculo_fuzzy)      ;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;  Copywright Juan Luis Castro  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;;;;;;;;;;;;;;;;;;;;;;;;; FUNCIONES NECESARIAS  ;;;;;;;;;;;;;;;;;;;;;;;

; Membership es una funcion que calcul el el grado de pertenencia de value al conjunto difuso
;trapezoidal (a b c d).
(deffunction membership (?value ?a ?b ?c ?d)
(if  (< ?value ?a) then (bind ?rv 0)
	else
	   (if (< ?value ?b) then (bind ?rv (/ (- ?value ?a) (- ?b ?a)))
           else
             (if  (< ?value ?c) then (bind ?rv 1)
                 else
                   (if (< ?value ?d) then (bind ?rv (/ (- ?d ?value) (- ?d ?c)))
                        else (bind ?rv 0)
                   )
             )
       )
)
?rv
)

; center_of_gravity es una función que calcula el centro de gravedad del conjunto difuso
;trapezoidal (a b c d).
(deffunction center_of_gravity (?a ?b ?c ?d)
(bind ?ati (/ (- ?b ?a) 2))
(bind ?atd (/ (- ?d ?c) 2))
(bind ?rv (/ (+ (+ ?b ?c) (- ?atd ?ati)) 2))
?rv
)

(deffunction conjuncion (?x ?y)
(bind ?rv (* ?x ?y))
?rv
)


;;;;;;;;;;;;;;;;;;;;;;;;;; CONOCIMIENTO ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Entradas: Peso y edad de un paciente  (dato ?variable ?valor)
; Salida: riesgo de infarto (fuzzy inference ?variable ?valor)
;;;;;;;;;;;;Conocimiento ;;;;;;;;;;;;;;;;;
;; Si la edad es avanzada el riesgo de infarto es medio
;; Si el peso es elevado el riesgo de infarto es alto
;; Si el peso es muy elevado el riesgo de infarto es muy alto


;;  Definimos los conjuntos difusos que usará el sistema

(deffacts conjuntos_difusos
(cd edad avanzada 60 70 150 150)  ; aproximadamente mas de 65

(cd peso elevado 90 100 110 120)  ; aproximadamente entre 62 y 70
(cd peso muy_elevado 130 230 401 401) ; aproximadamente mas de 105

(cd riesgo bajo 2 2 2 2)    ; aproximadamente 2 (siempre hay riesgo de infarto)
(cd riesgo medio 4 5 5 6)    ; aproximadamente 5
(cd riesgo alto 8 10 10 12)     ; aproximadamente 10
(cd riesgo muy_alto 15 30 50 50)     ; aproximadamente 20
)

;; Definimos las reglas y las explicaciones asociadas

(deffacts reglas
(regla 1 antecedente edad avanzada)
(regla 1 consecuente riesgo medio)
(regla 1 explicacion "Si la edad es avanzada, el riesgo de infarto es medio.")

(regla 3 antecedente peso muy_elevado)
(regla 3 consecuente riesgo muy_alto)
(regla 3 explicacion "Si el peso es muy elevado, el riesgo de infarto es muy alto.")

(regla 2 antecedente peso elevado)
(regla 2 consecuente riesgo alto)
(regla 2 explicacion "Si el peso es elevado, el riesgo de infarto es alto.")

)


; Obtenemos el cumplimiento de cada conjunto difuso

(defrule cumplimiento_predicado_difuso
(declare (salience 3))
(modulo calculo_fuzzy)
(cd ?v ?l ?a ?b ?c ?d)
(dato ?v ?x)
=>
(bind ?g (membership ?x ?a ?b ?c ?d))
(assert (fuzzy cumplimiento ?v ?l ?g))
(if (> ?g 0) then (printout t ?v " es " ?l " en grado " ?g crlf))
)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Obtenemos el matching de cada antecedente de cada regla
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defrule matching_antecedente_simple
(declare (salience 2))
(modulo calculo_fuzzy)
(regla ?r antecedente ?v ?l)
(fuzzy cumplimiento ?v ?l ?g)
=>
(assert (fuzzy matching ?r ?g ?v))
)

(defrule matching_antecedente_1
(declare (salience 2))
(modulo calculo_fuzzy)
?f <- (fuzzy matching ?r ?g ?v)
(not (fuzzy matching_antecedente_regla ?r ?))
=>
(assert (fuzzy matching_antecedente_regla ?r ?g))
(retract ?f)
)

(defrule matching_antecedente
(declare (salience 2))
(modulo calculo_fuzzy)
?f <- (fuzzy matching ?r ?g ?v)
?h<- (fuzzy matching_antecedente_regla ?r ?g1)
=>
(retract ?f ?h)
(assert (fuzzy matching_antecedente_regla ?r (conjuncion ?g1 ?g)))
)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Inferimos con su correspondiente grado los consecuentes de las reglas que hacen algun matching
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defrule inferencia_difusa
(declare (salience 1))
(modulo calculo_fuzzy)
(fuzzy matching_antecedente_regla ?r ?g1)
(test (> ?g1 0))
(regla ?r consecuente ?v ?l)
(regla ?r explicacion ?text)
=>
(assert (fuzzy inferido ?v ?l ?g1))
(printout t "Se va a aplicar la regla: " ?text  crlf)
)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Obtenemos el valor deducido como la media ponderada (por los grados de cada consecuente)
;;;  de los centros de gravedad de los consecuentes inferidos
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defrule concrecion_individual
(modulo calculo_fuzzy)
(fuzzy inferido ?v ?l ?g1)
(cd ?v ?l ?a ?b ?c ?d)
=>
(assert (fuzzy sumando_numerador ?v (* ?g1 (center_of_gravity ?a ?b ?c ?d))))
)

(defrule concrecion_numerador
(modulo calculo_fuzzy)
?g<- (fuzzy numerador ?v ?x)
?f <- (fuzzy sumando_numerador ?v ?y)
=>
(assert (fuzzy numerador ?v (max ?x ?y)))
(retract ?f ?g)
)

(defrule respuesta
  (declare (salience -1))
  (modulo calculo_fuzzy)
  (fuzzy numerador ?v ?n)
=>
  (assert (fuzzy valor_inferido ?v ?n))
  (if (= ?n 2) then
    (printout t "Ninguna regla aplicada. El riesgo mínimo de infarto es " ?n "%"  crlf)
  else
    (printout t "Aplicando esta(s) regla(s) el valor de " ?v " es " ?n "%"  crlf)
  )
)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;  Una vez inferido el valor salimos del modulo
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defrule salir
(declare (salience -2))
?f <- (modulo calculo_fuzzy)
=>
(retract ?f)
)

;;;;;;;;;;;;;;;;;;;; INICIALIZACION DE LOS VALORES CUANDO SE ENTRA AL MODULO  ;;;;;;;;;;

(defrule iniciar_proceso
(declare (salience 5))
(modulo calculo_fuzzy)
=>
(assert (borrar_datos_ejecucion_anterior))
)

(defrule borrar_datos_ejecucion_anterior
(declare (salience 5))
(modulo calculo_fuzzy)
(borrar_datos_ejecucion_anterior)
?f <- (fuzzy $?)
=>
(retract ?f)
)

(defrule borrar_borrar_datos
(declare (salience 5))
(modulo calculo_fuzzy)
?f<- (borrar_datos_ejecucion_anterior)
(not (fuzzy $?))
=>
(retract ?f)
)

(defrule inicializar_fuzzy_inference
(declare (salience 4))
(modulo calculo_fuzzy)
(regla ? consecuente ?v ?)
=>
(assert (fuzzy numerador ?v 2))
)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;  PARA COMPROBARLO   ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;  Reglas para pedir los datos y entrar en el modulo ;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defrule pregunta1
(declare (salience 1))
=>
(printout t "Peso: ")
  (bind ?resp (read))
  (while (or(not (numberp ?resp)) (< ?resp 50) (> ?resp 300)) ;; La edad debe ser numerica y en el rango [50-300]
    (printout t "Valor Incorrecto. Introduce tu edad (NUMERO[50-300]): ")
    (bind ?resp (read))
  )
(assert (dato peso ?resp))
)

(defrule pregunta2
(declare (salience 1))
=>
(printout t "Edad: ")
  (bind ?resp (read))
  (while (or(not (numberp ?resp)) (< ?resp 18) (> ?resp 150)) ;; La edad debe ser numerica y en el rango [18-150]
    (printout t "Valor Incorrecto. Introduce tu edad (NUMERO[18-150]): ")
    (bind ?resp (read))
  )
(assert (dato edad ?resp))
)

(defrule pregunta3
=>  
  (assert (modulo calculo_fuzzy))
)
