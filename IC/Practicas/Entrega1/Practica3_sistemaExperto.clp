;;;;;;;;;; EJERCICIO 3 DE LA PRACTICA 1 ;;;;;;;;;;
;;;;;;; Diseñar un Sistema Experto que asesore a un cliente en una agencia de viaje ;;;;;;;
;;;;;;; sobre qué destino elegir de forma que el sistema actúe tal y como lo hariais vosotros ;;;;;;;

;;;;; CONSIDERACIONES ;;;;;

;;; Para representar los destinos se utilizan los siguientes hechos ;;;

(deffacts Destinos
    (Destino España)
    (Destino Francia)
    (Destino Alemania)
    (Destino Ucrania)
    (Destino Estados_Unidos)
    (Bienvenida No)
)

;;; Para reprensentar que el sistema aconseja elegir un destino <nombre del destino> ;;;
;;; por el motivo <texto del motivo> utilizaremos el hecho ;;;

; (Adecuado <nombre del destino> “<texto del motivo>” “apodo del experto”) ;
; Se crea la plantilla para organizar qué contiene un consejo de destino adecuado
(deftemplate Adecuado
  (slot codigo
    (type SYMBOL)
    (default null)
    (allowed-symbols  null ES FR AL UC EU)
  )
  (slot motivo
    (type STRING)
    (default ?DERIVE)
  )
  (slot experto
    (type STRING)
    (default "Clips")
    (allowed-strings "Clips" "D. Experto Yerasito")
  )
)


; Se crea la plantilla para organizar qué contiene un consejo adecuado de viaje
(deftemplate Viaje
    (slot codigo
        (type SYMBOL)
        (default null)
        (allowed-symbols null ES FR AL UC EU)
    )
    (slot destino 
        (type STRING)
        (allowed-strings "España" "Alemania" "Francia" "Ucrania" "Estados Unidos")
    )

    (slot dia_salida
        (type SYMBOL)
        (default null)
        (allowed-symbols null invierno primavera verano otoño)
    )
    (slot transporte
        (type SYMBOL)
        (default avion)
        (allowed-symbols barco avion tren coche)
    )
    (slot duracion
        (type SYMBOL)
        (default null)
        (allowed-symbols null corta media larga)
    )
    (slot precio
        (type SYMBOL)
        (default medio)
        (allowed-symbols barato medio caro)
    )
    (slot beneficio_agencia
        (type SYMBOL)
        (default null)
        (allowed-symbols null bajo medio alto)
    )
)

;;; El sistema debe utilizar las propiedades o características que emplearíais en la vida ;;;
;;; real para proporcionar el consejo. Hay que incluir al principio del fichero un ;;;
;;; comentario indicando las propiedades que usareis, los valores que pueden tomar y ;;;
;;; cómo se representan en el sistema. ;;;


; Para relacionar cada simbolo del viaje con su nombre completo

(deftemplate Relacion_Binaria
   (slot destino
      (type SYMBOL)
      (default null)
      (allowed-symbols null España Francia Alemania Ucrania Estados_Unidos)
   )
   (slot simbolo_destino
      (type SYMBOL)
      (default null)
      (allowed-symbols null ES FR AL RU EU)
   )
)

; Al cliente se le hará una serie de preguntas y a razón de ello, se eligirá un viaje ;
; Se creará una plantilla que guarde como un hecho las respuestas
(deffacts Respuestas
   (estado_civil e)
   (edad e)
   (presupuesto p)
   (tiempo_de_viaje tie)
   (gusta_viajar g)
   (tipo_de_destino tip)
)

; Se establece como un hecho cada viaje con su codigo

(deffacts relaciones
   (Relacion_Binaria (destino España) (simbolo_destino ES))
   (Relacion_Binaria (destino Francia) (simbolo_destino FR))
   (Relacion_Binaria (destino Alemania) (simbolo_destino AL))
   (Relacion_Binaria (destino Ucrania) (simbolo_destino RU))
   (Relacion_Binaria (destino Estados_Unidos) (simbolo_destino EU))
)


;;;;;; Para usar un template, es igual que un hecho, solo que hay que indicar cada campo
;;;; Si se ha creado el template Respuestas para crear un hecho de este tipo es (Respuestas_Preguntas (edad ?m) ... (tipo_de_destino ?p))
;;;; Y se crea el hecho


(defrule Da_bienvenida
  (declare (salience 100))
  ?b <- (Bienvenida No)
=>
  (printout t "Sistema de Asesoramiento. Los destinos ofertados son:" crlf)
  (printout t "- Barcelona, España." crlf)
  (printout t "- Paris, Francia." crlf)
  (printout t "- Berlin, Alemania." crlf)
  (printout t "- Kiev, Ucrania." crlf)
  (printout t "- California, Estados Unidos." crlf)
  (printout t "Se haran una serie de preguntas para poder recomendar la mejor eleccion" crlf)
  (assert (Bienvenida Si))
  (retract ?b)
  (assert (OfertaRecibida No)) ;; Será la condición de parada del programa
)

;;;;; REGLAS PARA HACER PREGUNTAS ;;;;;

;; ¿Estado civil? ;;

(defrule pregunta_estado_civil
=>
   (printout t "¿Cual es tu estado civil? (casado|soltero|nose): " crlf)
   (bind ?resp (read))
   (while (and (not (eq ?resp casado)) (not (eq ?resp soltero)) (not (eq ?resp nose)))
      (printout t "Valor Incorrecto. Introduce un valor (casado|soltero|nose)" crlf)
      (bind ?resp (read))
   )
   (assert (ec ?resp))
)

;; ¿Edad? ;;
(defrule pregunta_edad
=>
   (printout t "Cual es tu edad? (NUMERO)): " crlf)
   (bind ?resp (read))
   (while (not (numberp ?resp))
      (printout t "Valor Incorrecto. Introduce tu edad (NUMERO)" crlf)
      (bind ?resp (read))
   )
   (assert (e ?resp))
)

(defrule valorar_edad_joven
?h <- (e ?e)
(test (<= ?e 30))
=>
   (assert (e_valoracion joven))
   (retract ?h)
)

(defrule valorar_edad_media
?h <- (e ?e)
(test (and (> ?e 30) (<= ?e 50)))
=>
   (assert (e_valoracion medio))
   (retract ?h)
)

(defrule valorar_edad_mayor
?h <- (e ?e)
(test (> ?e 50))
=>
   (assert (e_valoracion viejo))
   (retract ?h)
)

;; ¿Presupuesto? ;;
(defrule pregunta_presupuesto
=>
   (printout t "Cual es tu presupuesto? (NUMERO)): " crlf)
   (bind ?resp (read))
   (while (not (numberp ?resp))
      (printout t "Valor Incorrecto. Introduce tu presupuesto (NUMERO)" crlf)
      (bind ?resp (read))
   )
   (assert (p ?resp))
)

(defrule valorar_presupuesto_bajo
?h <- (p ?p)
(test (<= ?p 1000))
=>
   (assert (p_valoracion bajo))
   (retract ?h)
)

(defrule valorar_presupuesto_medio
?h <- (p ?p)
(test (and (> ?p 1000) (<= ?p 3000)))
=>
   (assert (p_valoracion medio))
   (retract ?h)
)

(defrule valorar_presupuesto_alto
?h <- (p ?p)
(test (> ?p 50))
=>
   (assert (p_valoracion alto))
   (retract ?h)
)

;; ¿Tiempo de viaje?
(defrule pregunta_tiempo_de_viaje
=>
   (printout t "¿Cuanto tiempo quieres viajar? (corto|medio|largo): " crlf)
   (bind ?resp (read))
   (while (and (not (eq ?resp corto)) (not (eq ?resp medio)) (not (eq ?resp largo)))
      (printout t "Valor Incorrecto. Introduce un valor (corto|medio|largo)" crlf)
      (bind ?resp (read))
   )
   (assert (t ?resp))
)

;; ¿Tipo de viaje?
(defrule pregunta_viajar
=>
   (OtraVez ?a)
   (printout t "¿Has viajado mucho? (si|no|regular): " crlf)
   (bind ?resp (read))
   (while (and (not (eq ?resp si)) (not (eq ?resp no)) (not (eq ?resp regular)))
      (printout t "Valor Incorrecto. Introduce un valor (si|no|regular)" crlf)
      (bind ?resp (read))
   )
   (assert (v ?resp))
)

;; ¿Tipo de destino?
(defrule pregunta_tipo_de_destino
=>
   (printout t "¿Cual es tu tipo de destino? (playa|montaña|ciudad): " crlf)
   (bind ?resp (read))
   (while (and (not (eq ?resp playa)) (not (eq ?resp montaña)) (not (eq ?resp ciudad)))
      (printout t "Valor Incorrecto. Introduce un valor (playa|montaña|ciudad)" crlf)
      (bind ?resp (read))
   )
   (assert (tipd ?resp))
)

;; Se recogen los datos introducidos por el usuario
(defrule recoger_datos
;; Todas estos hechos existen como único, ya que ha sido lo que ha respondido el usuario
?ec <- (ec ?estadocivil)
?e_valor <- (e_valoracion ?edad) ;; Aqui la edad ha sido actualizada a un valor joven|medio|viejo
?p_valor <- (p_valoracion ?presupuesto) ;; Aqui el presupuesto ha sido actualizado a un valor bajo|medio|alto
?t <- (t ?tiempodeviaje)
?v <- (v ?viajar)
?tipd <- (tipd ?tipodedestino)
=>
   (assert (Respuestas estado_civil ?estadocivil))
   (assert (Respuestas edad ?edad)) 
   (assert (Respuestas presupuesto ?presupuesto))
   (assert (Respuestas tiempo_de_viaje ?tiempodeviaje))
   (assert (Respuestas gusta_viajar ?viajar))
   (assert (Respuestas tipo_de_destino ?tipodedestino))
   ;; DEBUG
   ; (printout t "Los datos obtenidos son: " ?estadocivil " " ?edad " " ?presupuesto " " ?tiempodeviaje " " ?viajar " " ?tipodedestino crlf)
   ;;; Estos valores ya no interesa guardarlos, ya que se tienen almacenados en el hecho Respuestas
   (retract ?ec)
   (retract ?e_valor)
   (retract ?p_valor)
   (retract ?t)
   (retract ?v)
   (retract ?tipd)
)

;; Se elige un consejo a razón de las respuestas
(defrule gusta_viaje_playa
(OfertaRecibida No) ;; Estas reglas solo se aplican si el consejo aun no se ha deliberado
(Respuestas tipo_de_destino ?tipodedestino)
(test (eq ?tipodedestino playa))
=>
   (assert (Elegido ES))
   (assert (Motivo "Te gusta la playa"))
   (assert (Experto "D. Experto Yerasito"))
)

(defrule gusta_ciudad_y_dinero
(OfertaRecibida No)
(Respuestas tipo_de_destino ?tipd)
(Respuestas presupuesto ?presupuesto)
(test (eq ?tipd ciudad))
(test (eq ?presupuesto alto))
=>
   (assert (Elegido AL))
   (assert (Motivo "Te gusta la ciudad y tienes dinerico"))
   (assert (Experto "D. Experto Yerasito"))
)

(defrule gusta_viajar
(OfertaRecibida No)
(Respuestas gusta_viajar ?viajar)
(test (or (eq ?viajar si) (eq ?viajar regular)))
=>
   (assert (PreguntaTipoDeViaje))
   (printout t "Que tipo de viajes te gusta hacer? (romantico|negocios|voluntariado|deportivo|tradicional): " crlf)
   (bind ?resp (read))
   (while (and (not (eq ?resp romantico)) (not (eq ?resp negocios)) (not (eq ?resp voluntariado)) (not (eq ?resp deportivo)) (not (eq ?resp tradicional)))
      (printout t "Valor Incorrecto. Introduce un valor (romantico|negocios|voluntariado|deportivo|tradicional)" crlf)
      (bind ?resp (read))
   )
   (assert (TipoDeViaje ?resp)) ;; Guarda la opción elegido
)


; Se comprueba qué tipo de viaje se ha elegido
(defrule en_viaje
   (declare (salience 500))
   ?ptdv <- (PreguntaTipoDeViaje)
   ?pdv <- (TipoDeViaje ?tp)
=>
   (if 
      (eq ?tp romantico) then 
         (assert (Elegido FR))
         (assert (Motivo "Te gusta viajar y en concreto viajes románticos. Seguro que lo pasas bien"))
         (assert (Experto "D. Experto Yerasito"))
         ;; Ya no interesa que esto siga existiendo para que no entre de nuevo aquí
         (retract ?ptdv) 
         (retract ?pdv)
         
   )
   (if
      (eq ?tp negocios) then 
         (assert (Elegido EU))
         (assert (Motivo "Te gusta viajar y en concreto viajes de negocios. Seguro que amasas una buena fortuna"))
         (assert (Experto "D. Experto Yerasito"))
         ;; Ya no interesa que esto siga existiendo para que no entre de nuevo aquí
         (retract ?ptdv) 
         (retract ?pdv)
   )
   (if
      (eq ?tp voluntariado) then 
         (assert (Elegido RU))
         (assert (Motivo "Te gusta viajar y en concreto el voluntariado. Seguro que ayudaras a mucha gente"))
         (assert (Experto "D. Experto Yerasito"))
         ;; Ya no interesa que esto siga existiendo para que no entre de nuevo aquí
         (retract ?ptdv) 
         (retract ?pdv)
   )

)

;;; Si el usuario elige a todo NO ;;;;
(defrule todo_no
   (declare (salience 800))
   ?cr <- (OfertaRecibida No)
   (Respuestas estado_civil ?estadocivil) 
   (Respuestas gusta_viajar ?viajar)
   (test (eq ?viajar no))
   (test (eq ?estadocivil casado))
=>
   (printout t "No te gusta nada, por lo que es dificil recomendarte un viaje." crlf)
   (printout t "La unica recomendacion posible seria hacer un crucero a varios paises y elegir" crlf)
   (printout t "los viajes que mas te puedan llamar la atencion por actividades o cultura" crlf)
   (retract ?cr)
   (assert (OfertaRecibida Si))

)

;;; Si el usuario elige REGULAR en todo ;;;;;
(defrule todo_regular
   (declare (salience 800))
   (OfertaRecibida No)
   (Respuestas gusta_viajar ?viajar)
   (test (eq ?viajar regular))
=>
   (assert (Elegido EU))
   (assert (Motivo "No te gusta nada en especial. Quizas el país que más se adepte a ti sea Estados Unidos dad su variedad"))
   (assert (Experto "D. Experto Yerasito"))

)

;; Si el programa llega hasta aqui sin una respuesta
(defrule consejo_por_defecto
   (declare (salience -10))
   ?cr <- (OfertaRecibida No)
=>
   (printout t "En tu caso ha sido dificil elegir un viaje en concreto." crlf)
   (printout t "Quizas la solucion sea un crucero sobre el Atlántico y elegir el país que más te guste" crlf)
   (printout t "Tienes gustos diversos y no profundizas en un estilo en especifico" crlf)
   (retract ?cr)
   (assert (OfertaRecibida Si))
)

;; Se crea un consejo ;;
(defrule crear_oferta
   (declare (salience 1000))
   (Elegido ?el)
   (Motivo ?mot)
   (Experto ?expt)
=>
   (assert (Adecuado (codigo ?el) (motivo ?mot) (experto ?expt)))
)

;; Se imprime un consejo ;;
(defrule ofrece_destino
   (declare (salience 9000))
   ?cr <- (OfertaRecibida No)
   (Adecuado (codigo ?el) (motivo ?texto) (experto ?experto))
   (Relacion_Binaria (destino ?r) (simbolo_destino ?el))
=>
   (printout t ?experto " te aconseja el Destino " ?r "." crlf)
   (printout t "Motivo: " ?texto "." crlf)
   (printout t "¿Rechazas el destino? " crlf)
   (bind ?resp (read))
   (while (and (not (eq ?resp Si)) (not (eq ?resp No)))
      (printout t "Valor Incorrecto. Introduce un valor (Si|No) " crlf)
      (bind ?resp (read))
   )

   (printout t "Cual es tu motivo de rechazo?")
   (bind ?motivo (read))
   (assert (MotivoRechazo ?motivo)) ; Hecho con el motivo de rechazo: tiempo, tipo, dinero, etc.

   (assert (Rechazada ?resp) ) ;; Guarda si rechaza
   (retract ?cr)
)

(defrule reofrecer
   (declare (salience 9000))
   (MotivoRechazo ?motivo)
   ?rech <- (Respuestas ?motivo ?valor) ; Ej. Se rechaza el tiempo (volveria a preguntar la duracion del viaje)

   ?resp1 <- (Adecuado (codigo ?el) (motivo ?mot) (experto ?expt))

   ?r <- (Rechazada Si)
=>
   (printout t "Respuestas " ?motivo " " ?valor)
   (retract ?rech)
   (retract ?r)
   (retract ?resp1)  
  
   (assert (OfertaRecibida No))
   (assert (OtraVez Si))
)

;; Para que no siga haciendo preguntas
; (defrule FinPrograma
; (declare (salience 5000))
; (OfertaRecibida ?of)
; (test (eq ?of Si))
; =>
; (assert (Fin))
; )