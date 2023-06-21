;;;;;;;;;; EJERCICIO 2 DE LA PRACTICA 5 ;;;;;;;;;;
;;;;;;; Implementar en CLISP un sistema que haga un diagnostico sobre la averia ;;;;;;;
;;;;;;; de un coche que no arranca de acuerdo a las siguientes reglas ;;;;;;;

;;; R1: SI el motor obtiene gasolina Y el motor gira ENTONCES problemas con las bujías con certeza 0,7
;;; R2: SI NO gira el motor ENTONCES problema con el starter con certeza 0,8
;;; R3: SI NO encienden las luces ENTONCES problemas con la batería con certeza 0,9
;;; R4: SI hay gasolina en el deposito ENTONCES el motor obtiene gasolina con certeza 0,9
;;; R5: SI hace intentos de arrancar ENTONCES problema con el starter con certeza -0,6
;;; R6: SI hace intentos de arrancar ENTONCES problema con la batería 0,5


;;;;; REPRESENTACION ;;;;; 

; (FactorCerteza ?h si|no ?f) representa que ?h se ha deducido con factor de certeza ?f
; ?h podrá_ser:
; - problema_starter
; - problema_bujias
; - problema_batería
; - motor_llega_gasolina

; (Evidencia ?e si|no) representa el hecho de si evidencia ?e se da
; ?e podrá ser:
; - hace_intentos_arrancar
; - hay_gasolina_en_deposito
; - encienden_las_luces
; - gira_motor

;;; convertimos cada evidencia en una afirmación sobre su factor de certeza

(defrule certeza_evidencias
   (Evidencia ?e ?r)
   =>
   (assert (FactorCerteza ?e ?r 1)) 
)

;; También podríamos considerar evidencias con una cierta 
;; incertidumbre: al preguntar por la evidencia, pedir y recoger 
;; directamente el grado de certeza

;;; FUNCIONES ;;;

(deffunction encadenado (?fc_antecedente ?fc_regla)
   (if (> ?fc_antecedente 0) 
      then
   (bind ?rv (* ?fc_antecedente ?fc_regla)) 
      else 
   (bind ?rv 0) )
   ?rv
)

(deffunction combinacion (?fc1 ?fc2)
   (if (and (> ?fc1 0) (> ?fc2 0) )
      then
         (bind ?rv (- (+ ?fc1 ?fc2) (* ?fc1 ?fc2) ) )
   else 
      (if (and (< ?fc1 0) (< ?fc2 0) )
         then
            (bind ?rv (+ (+ ?fc1 ?fc2) (* ?fc1 ?fc2) ) )
      else
            (bind ?rv (/ (+ ?fc1 ?fc2) (- 1 (min (abs ?fc1) (abs ?fc2))) ))
      )
   )
   ?rv
)

;; Aunque en este ejemplo no se da, puede ocurrir que tengamos ;;
;; deducciones de hipótesis en positivo y negativo que hay que ;;
;; combinar para compararlas ;;
(defrule combinar_signo
   (declare (salience 2))
   (FactorCerteza ?h si ?fc1)
   (FactorCerteza ?h no ?fc2)
=>
   (assert (Certeza ?h (- ?fc1 ?fc2))) 
)

;; Combinar misma deduccion por distintos caminos
(defrule combinar
   (declare (salience 1))
   ?f <- (FactorCerteza ?h ?r ?fc1)
   ?g <- (FactorCerteza ?h ?r ?fc2)
   (test (neq ?fc1 ?fc2))
=>
   (retract ?f ?g)
   (assert (FactorCerteza ?h ?r (combinacion ?fc1 ?fc2))) 
)

;;; TRADUCCION DE REGLAS ;;;

; R1: SI el motor obtiene gasolina Y el motor gira ENTONCES problemas con las bujías con certeza 0,7
(defrule R1
   (FactorCerteza motor_llega_gasolina si ?f1)
   (FactorCerteza gira_motor si ?f2)
   (test (and (> ?f1 0) (> ?f2 0))) 
   =>
   (assert (FactorCerteza problema_bujias si (encadenado (* ?f1 ?f2) 0.7)))
   ; (printout t "R1: bujias '0.7" crlf)
)

;;; R2: SI NO gira el motor ENTONCES problema con el starter con certeza 0,8
(defrule R2
   (FactorCerteza gira_motor no ?f1)
   (test (> ?f1 0) )
=>
   (assert (FactorCerteza problema_starter si (encadenado ?f1 0.8) ) )
   ; (printout t "R2: starter '0.8" crlf)
)

;;; R3: SI NO encienden las luces ENTONCES problemas con la batería con certeza 0,9
(defrule R3
   (FactorCerteza encienden_las_luces no ?f1)
   (test (> ?f1 0) )
=>
   (assert (FactorCerteza problema_bateria si (encadenado ?f1 0.9) ) )
   ; (printout t "R3: bateria '0.9" crlf)
)

;;; R4: SI hay gasolina en el deposito ENTONCES el motor obtiene gasolina con certeza 0,9
(defrule R4
   (FactorCerteza hay_gasolina_en_deposito si ?f1)
   (test (> ?f1 0) )
=>
   (assert (FactorCerteza motor_llega_gasolina si (encadenado ?f1 0.9) ) )
   ; (printout t "R4: motor_llega_gasolina '0.9" crlf)
)

;;; R5: SI hace intentos de arrancar ENTONCES problema con el starter con certeza -0,6
(defrule R5
   (FactorCerteza hace_intentos_arrancar si ?f1)
   (test (> ?f1 0) )
=>
   (assert (FactorCerteza problema_starter si (encadenado ?f1 -0.6) ) )
   ; (printout t "R5: starter '-0.6" crlf)
)

;;; R6: SI hace intentos de arrancar ENTONCES problema con la batería 0,5
(defrule R6
   (FactorCerteza hace_intentos_arrancar si ?f1)
   (test (> ?f1 0) )
=>
   (assert (FactorCerteza problema_bateria si (encadenado ?f1 0.5) ) )
   ; (printout t "R6: bateria '0.5" crlf)
)

(defrule checkStarter
(declare (salience -1))
(not (FactorCerteza problema_starter $? $?))
=>
(assert (FactorCerteza problema_starter no 0))
)

(defrule checkBujia
(declare (salience -1))
(not (FactorCerteza problema_bujias $? $?))
=>
(assert (FactorCerteza problema_bujias no 0))
)

(defrule checkBateria
(declare (salience -1))
(not (FactorCerteza problema_bateria $? $?))
=>
(assert (FactorCerteza problema_bateria no 0))
)

(defrule checkMotor
(declare (salience -1))
(not (FactorCerteza motor_llega_gasolina $? $?))
=>
(assert (FactorCerteza motor_llega_gasolina no 0))
)

;;;;; PREGUNTAS AL USUARIO SOBRE EL COCHE ;;;;;

;; Pregunta 1: Intenta arrancar?
(defrule pregunta_intentos_arrancar
=>
   (printout t "Hace intentos de arrancar? (si|no)" crlf)
   (bind ?resp (read))
   (while (and (not (eq ?resp si)) (not (eq ?resp no)))
      (printout t "Valor Incorrecto. Introduce un valor (si|no: " )
      (bind ?resp (read))
   )
   (assert (Evidencia hace_intentos_arrancar ?resp))
)

;; Pregunta 2: Hay gasolina en el depósito?
(defrule pregunta_gasolina_en_deposito
=>
   (printout t "Hay gasolina en el deposito? (si|no)" crlf)
   (bind ?resp (read))
   (while (and (not (eq ?resp si)) (not (eq ?resp no)))
      (printout t "Valor Incorrecto. Introduce un valor (si|no: " )
      (bind ?resp (read))
   )
   (assert (Evidencia hay_gasolina_en_deposito ?resp))
)

;; Pregunta 3: Encienden las luces?
(defrule pregunta_encienden_luces
=>
   (printout t "Las luces encienden? (si|no)" crlf)
   (bind ?resp (read))
   (while (and (not (eq ?resp si)) (not (eq ?resp no)))
      (printout t "Valor Incorrecto. Introduce un valor (si|no: " )
      (bind ?resp (read))
   )
   (assert (Evidencia encienden_las_luces ?resp))
)

;; Pregunta 4: Gira el motor?
(defrule pregunta_gira_motor
=>
   (printout t "El motor gira? (si|no)" crlf)
   (bind ?resp (read))
   (while (and (not (eq ?resp si)) (not (eq ?resp no)))
      (printout t "Valor Incorrecto. Introduce un valor (si|no: " )
      (bind ?resp (read))
   )
   (assert (Evidencia gira_motor ?resp))
   (assert (Generar_respuesta))
)

;; Calcula la mayor certeza de todos los problemas
(defrule mayorCerteza
   ?a <- (Generar_respuesta)
   (FactorCerteza problema_starter ?sn ?v)
   (FactorCerteza problema_bujias ?sn1 ?v1)
   (FactorCerteza problema_bateria ?sn2 ?v2)
   (FactorCerteza motor_llega_gasolina ?sn3 ?v3)
=>
   (assert (MayorCerteza (max ?v ?v1 ?v2 ?v3)))
   (assert (Imprimir))
)

;; Imprime las certezas de cada problema
(defrule imprimir
   ?i <- (Imprimir)
   (FactorCerteza problema_starter ?sn ?v)
   (FactorCerteza problema_bujias ?sn1 ?v1)
   (FactorCerteza problema_bateria ?sn2 ?v2)
   (FactorCerteza motor_llega_gasolina ?sn3 ?v3)
   (MayorCerteza ?valor)
   (FactorCerteza ?motivo ?s ?valor)
=>
   (printout t crlf "Certezas: ")
   (printout t crlf"###########################"crlf)
   (printout t "Problema starter " ?v crlf)
   (printout t "Problema bujias " ?v1 crlf)
   (printout t "Problema bateria " ?v2 crlf)
   (printout t "Motor llega gasolina " ?v3 crlf)
   (printout t "###########################" crlf crlf)
   (retract ?i)
)

;; Imprime la mayor certeza obtenida a partir de la información dada por el usuario
(defrule Respuesta
   ?a <- (Generar_respuesta)
   (MayorCerteza ?maximo)
   (FactorCerteza ?h ?s ?maximo)
   =>
   (if (eq ?maximo 0)
      then
      (printout t "No se ha encontrado ningún problema válido en la base de datos." crlf)
      else
      (switch ?h
         (case motor_llega_gasolina then
            (printout t "Podemos afirmar que llega gasolina con una certeza de " ?maximo crlf)
         )
         (case problema_starter then
            (printout t "Se concluye que hay un problema en el starter con una certeza de " ?maximo crlf)
         )
         (case problema_bujias then
            (printout t "Se ha concluido que hay un problema en las bujías con una certeza de " ?maximo crlf)
         )
         (case problema_bateria then
            (printout t "Podemos afirmar que hay un problema en la batería con una certeza de " ?maximo crlf)
         )
      )
   )
   (retract ?a)
)

