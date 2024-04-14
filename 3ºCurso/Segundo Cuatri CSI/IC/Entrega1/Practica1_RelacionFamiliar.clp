;;;; REALIZADO POR: Yeray Lopez Ramirez ;;;;;
;;;;           DNI: 26050768W		    ;;;;;

;;;; HECHOS GENERALES DEL SISTEMA ;;;;;
;;;;(seran validos para todas las ejecuciones del sistema ;;;;

; Listado de personas de la familia en cuestion introduccidas con la propiedad unaria de hombre o mujer

; Lo primero es definir por qué está formada el conjunto familiar, en este caso serán personas de mi familia
; Además, entre las personas se distinguen dos diferencias: hombre o mujer
; Como las Personas que se recojan solo contendrán dos valores: Si es hombre o mujer, y el nombre, no se ve necesario la opción de hacer un template
(deffacts personas
   (hombre Yeray) ; Yo
   (hombre Mario) ; Hermanastro
   (hombre Aitor) ; Hermano
   (hombre AntonioManuel) ; Padre
   (hombre Donato) ; Abuelo
   (hombre Luis) ; Tio
   (hombre Jaime) ; Novio <3
   (hombre Ramon) ; Hipotético Padre de la novia de mi hermano
   (hombre Pedro) ; Hipotético Hermano de la novia de mi hermano
   (mujer Yanet) ; Madrastra
   (mujer Eva) ; Madre
   (mujer Pilar) ; Abuela
   (mujer Paula) ; Hermanastra repelente haha
   (mujer Reyes) ; Tia
   (mujer Andrea) ; Novia hermano
   (mujer Rocio) ; Prima
)

;;;;; Plantilla típica de Relaciones binarias, ajustada a Relaciones de parentesco restringiendo los valores de tipo de relacion a estas. 
;;;;; Se usa para registrar "El <sujeto> es <tipo de relacion> de <objeto>", por ejemplo "Juan es TIO de Julia" 
(deftemplate Relacion 
  (slot tipo (type SYMBOL) (allowed-symbols HIJO PADRE ABUELO NIETO HERMANO ESPOSO PRIMO TIO SOBRINO CUNIADO YERNO NUERA SUEGRO))
  (slot sujeto)
  (slot objeto)
)


;;; Aplicando el template anteriomente definido, es posible dar constancia de Relaciones de parentesco entre las personas ya definididas en el conjunto de la familia anterior

;;;; Se hace uso de las reglas de parentesco en la Unidad Familiar para evitar escribir más relaciones manuales de las necesarias
(deffacts Relaciones
   (Relacion (tipo HIJO) (sujeto Yeray) (objeto AntonioManuel)) ; "Yeray es HIJO de AntonioManuel" y por tanto, "Yeray es HIJO de Eva", porque "Manuel era ESPOSO de Eva"
   (Relacion (tipo HIJO) (sujeto Aitor) (objeto AntonioManuel)) ; "Aitor es HIJO de Eva"
   (Relacion (tipo HIJO) (sujeto Mario) (objeto Yanet)) ; "Mario es HIJO de Yanet"
   (Relacion (tipo HIJO) (sujeto Paula) (objeto Yanet)) ; "Paula es HIJA de Yanet"
   (Relacion (tipo HIJO) (sujeto Andrea) (objeto Ramon)) ; "Andrea es HIJA de Ramon"
   (Relacion (tipo HIJO) (sujeto Pedro) (objeto Ramon)) ; "Pedro es HIJO de Ramon"
   (Relacion (tipo HIJO) (sujeto Rocio) (objeto Reyes)) ; "Rocio es HIJA de Reyes"
   (Relacion (tipo HIJO) (sujeto AntonioManuel) (objeto Pilar)) ; "AntonioManuel es HIJO de Pilar"
   (Relacion (tipo HIJO) (sujeto Reyes) (objeto Pilar)) ; "Reyes es HIJA de Pilar"

   (Relacion (tipo ESPOSO) (sujeto AntonioManuel) (objeto Eva)) ; "AntonioManuel era ESPOSO de Eva y por la regla de la Dualidad. Eva era ESPOSA de AntonioManuel"
   (Relacion (tipo ESPOSO) (sujeto AntonioManuel) (objeto Yanet)) ; "AntonioManuel es ESPOSO de Yanet"
   (Relacion (tipo ESPOSO) (sujeto Pilar) (objeto Donato)) ; "Pilar es ESPOSA de Donato"
   (Relacion (tipo ESPOSO) (sujeto Luis) (objeto Reyes)) ; "Luis es ESPOSO de Reyes"
   (Relacion (tipo ESPOSO) (sujeto Aitor) (objeto Andrea)) ; "Aitor es ESPOSO de Andrea"
   (Relacion (tipo ESPOSO) (sujeto Yeray) (objeto Jaime)) ; "Yeray es ESPOSO de Jaime"
)

;;;;;;; Cada relacion tiene una relacion dual que se produce al cambiar entre si objeto y sujeto. 
;;;;;;; Por ejemplo, Si x es HIJO de y, y es PADRE de x". 
;;;;;;; Para poder deducirlo con una sola regla metemos esa informacion como hechos con la etiqueta dual, "Dual de HIJO PADRE", y asi con todas las Relaciones consideradas
(deffacts dualidad
   (dual HIJO PADRE)
   (dual ABUELO NIETO)
   (dual HERMANO HERMANO) 
   (dual ESPOSO ESPOSO)
   (dual PRIMO PRIMO)
   (dual TIO SOBRINO)
   (dual CUNIADO CUNIADO)
   (dual YERNO SUEGRO)
   (dual NUERA SUEGRO)
)

;;;;;; Para deducir las reglas que se aplican son de composicion, del tipo "el HERMANO del PADRE es un TIO". 
;;;;;; Por comodidad, en lugar de crear una regla por cada posible composición, metemos como hechos la relacion que se obtiene por composicion. 
;;;;;; Solo metemos unas cuantas composiciones que sean suficientes para deducir cualquier cosa

(deffacts compuestos
   (comp HIJO HIJO NIETO) ; "El HIJO de mi HIJO es mi NIETO"
   (comp PADRE PADRE ABUELO) ; "El PADRE de mi PADRE es mi ABUELO"
   (comp ESPOSO PADRE PADRE)
   (comp HIJO PADRE HERMANO)
   (comp HERMANO PADRE TIO)
   (comp HIJO TIO PRIMO)
   (comp ESPOSO HIJO YERNO)
   (comp HERMANO ESPOSO CUNIADO)
) 


;;;;;; Para que cuando digamos por pantalla el parentesco lo expresemos correctamente, y puesto que el nombre que hemos puesto a cada relacion es el caso masculino, 
;;;;;; vamos a meter como hechos como se diaria esa relacion en femenino mediante la etiqueta femenino
(deffacts femenino
   (femenino HIJO HIJA) 
   (femenino PADRE MADRE) 
   (femenino ABUELO ABUELA) 
   (femenino NIETO NIETA) 
   (femenino HERMANO HERMANA)
   (femenino ESPOSO ESPOSA)
   (femenino TIO TIA) 
   (femenino PRIMO PRIMA)
   (femenino YERNO NUERA) 
   (femenino SUEGRO SUEGRA)
)

;;;;; REGLAS DEL SISTEMA ;;;;;

;;;; La dualidad es simetrica: si r es dual de t, t es dual de r. Por eso solo metimos como hecho la dualidad en un sentido, pues en el otro lo podiamos deducir con esta regla

(defrule autodualidad
   (dual ?r ?t)
   => 
   (assert (dual ?t ?r))
)


;;;; Si x es R de y, entonces y es dual de R de x

(defrule dualidad
   (Relacion (tipo ?r) (sujeto ?x) (objeto ?y))
   (dual ?r ?t)   ; El valor de ?t se toma de la dualidad antes definida, dependiendo de ?r, si ?r = HIJO, entonces ?t = PADRE
   => 
   (assert (Relacion (tipo ?t) (sujeto ?y) (objeto ?x)))) ; Se añade automáticamente esta relación


;;;; Si y es R de x, (y) x es T de z entonces y es RoT de z
;;;; Se añade que z e y sean distintos para evitar que uno resulte hermano de si mismo y cosas similares.

(defrule composicion
   (Relacion (tipo ?r) (sujeto ?y) (objeto ?x))
   (Relacion (tipo ?t) (sujeto ?x) (objeto ?z))
   (comp ?r ?t ?u)
   (test (neq ?y ?z)) ; z e y deben ser distintos
   => 
   (assert (Relacion (tipo ?u) (sujeto ?y) (objeto ?z)))
)

(deffacts Comienzo
   (INICIO) ;; Este inicio será para controlar que no se vuelve a preguntar y que el programa finaliza en un momento dado
)

;;;;; Se hace la pregunta para recoger el nombre de la persona
 
(defrule preguntapersona
   (declare (salience -1)) ;; Se le ha dado prioridad porque creaba las relaciones después
=>
   (printout t "Sobre que individuo quieres saber su relacion? (NOMBRE): " crlf)
   (assert (nombrepersona (read)))
   (assert (Existe No))
)

;;;;; Se pregunta el parentesco
(defrule preguntaparentesco
   (declare (salience -2))
   (nombrepersona ?nombre) ;; Se guarda el valor del dato antes leído en una variable para poder usarla en el PRINOUT
=>
   (printout t "Que relacion de parentesco quiere saber para " ?nombre "? (PARENTESCO): " crlf)
   (assert (parentesco (read)))
   
)
;;;;; Dice por pantalla las personas que son PARENTESCO de NOMBRE

;; Hace una búsqueda de las relaciones en MASCULINO
(defrule relacionparentesco
   (declare (salience -3))
   (nombrepersona ?x) ; Existe un hecho nombrepersona con un valor, el que sea, y se recoge en ?x
   (parentesco ?y) ; Se recoge la relación de parentesco que se debe buscar   
   (Relacion (tipo ?y) (sujeto ?r) (objeto ?x)) ; Se quiere saber que: ALGUIEN es ?y de ?X
   (hombre ?r)
=>
   (printout t ?r " es " ?y " de " ?x crlf)
   (assert (Existe Si))

)

;; Hace una búsqueda de las relaciones en FEMENINO
(defrule relacionparentescofemenino
   (declare (salience -3))
   (nombrepersona ?x)
   (parentesco ?y)
   (Relacion (tipo ?y) (sujeto ?r) (objeto ?x))
   (mujer ?r)
   (femenino ?y ?fem)
=>
   (printout t ?r " es " ?fem " de " ?x crlf)
   (assert (Existe Si))

)

;; Si al menos ha entrado en alguna regla anterior y se ha completado
;; quiere decir que como minimo una relación de parentesco ha encontrado
;; Entonces existirán al mismo tiempo (Existe Si) y (Existe No)
(defrule ExisteRelacion
   (declare (salience -5)) ;; Que la menos se haga después de las reglas anteriores
   (Existe Si)
   ?no <- (Existe No)
=>
   (retract ?no)
)

;; Cuando ya se han ejecutado las reglas anteriores, si sigue existiendo un hecho (Existe No)
;; Quiere decir que no se ha cumplido ningun hecho anterior, entonces las reglas no se han completado
;; Dando a entender que no hay ninguna relación
(defrule NoExisteRelacion
   (declare (salience -10)) ;; Se haga siempre en última instancia
   (Existe No)
   (nombrepersona ?x)
   (parentesco ?y)
=>
   (printout t "No existe ninguna relacion de parentesco del tipo " ?y " para " ?x crlf)
)