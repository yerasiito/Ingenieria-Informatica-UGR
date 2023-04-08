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

    (slot temporada
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

; Se crean hechos con los viajes programados
(defrule Viajes
(declare(salience 9999))
=>
   (assert (Viaje (codigo ES) (destino "España") (temporada verano) (transporte avion) (duracion media) (precio medio) (beneficio_agencia alto)))
   (assert (Viaje (codigo FR) (destino "Francia") (temporada primavera) (transporte tren) (duracion larga) (precio caro) (beneficio_agencia alto)))
   (assert (Viaje (codigo AL) (destino "Alemania") (temporada primavera) (transporte avion) (duracion media) (precio medio) (beneficio_agencia medio)))
   (assert (Viaje (codigo UC) (destino "Ucrania") (temporada invierno) (transporte avion) (duracion larga) (precio medio) (beneficio_agencia medio)))
   (assert (Viaje (codigo EU) (destino "Estados Unidos") (temporada otoño) (transporte avion) (duracion corta) (precio caro) (beneficio_agencia bajo)))
)

; Se definen hechos para el viajero
(deffacts Viajero
   (edad e) ; joven, media, mayor
   (epoca_de_viaje ep) ; invierno, primavera, verano, otoño
   (transporte_pref trans) ; barco, avion, tren, coche
   (duracion_de_viaje d) ; corto, medio, largo
   (presupuesto p) ; bajo, medio, alto
   (experiencia_viajando ex) ; si, no
   (tipo_de_destino tip) ; Playa, montaña, ciudad
)

; (Adecuado <nombre del destino> “<texto del motivo>” “apodo del experto”) ;
; Se crea la plantilla para organizar qué contiene un consejo de destino adecuado
(deftemplate Adecuado
  (slot codigo
    (type SYMBOL)
    (default null)
    (allowed-symbols null ES FR AL UC EU)
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

;;; El sistema debe utilizar las propiedades o características que emplearíais en la vida ;;;
;;; real para proporcionar el consejo. Hay que incluir al principio del fichero un ;;;
;;; comentario indicando las propiedades que usareis, los valores que pueden tomar y ;;;
;;; cómo se representan en el sistema. ;;;

; Se establece como un hecho cada viaje con su codigo

(deffacts relaciones
   (Viaje (codigo ES) (destino "España"))
   (Viaje (codigo FR) (destino "Francia"))
   (Viaje (codigo AL) (destino "Alemania"))
   (Viaje (codigo UC) (destino "Ucrania"))
   (Viaje (codigo EU) (destino "Estados Unidos"))
)

;;;;;; Para usar un template, es igual que un hecho, solo que hay que indicar cada campo
;;;; Si se ha creado el template Viajero para crear un hecho de este tipo es (Viajero (edad ?m) ... (tipo_de_destino ?p))
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

;; ¿Edad? ;;
(defrule pregunta_edad
   (not (Viajero edad ?))
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
   (assert (Viajero edad joven)) 
   (retract ?h)
)

(defrule valorar_edad_media
?h <- (e ?e)
(test (and (> ?e 30) (<= ?e 50)))
=>
   (assert (Viajero edad media)) 
   (retract ?h)
)

(defrule valorar_edad_mayor
?h <- (e ?e)
(test (> ?e 50))
=>
   (assert (Viajero edad mayor)) 
   (retract ?h)
)

;; ¿Temporada? ;;
(defrule pregunta_temporada
   (not (Viajero epoca_de_viaje ?))
=>
   (printout t "¿Cual es tu temporada preferida? (invierno|primavera|verano|otoño): " crlf)
   (bind ?resp (read))
   (while (and (not (eq ?resp invierno)) (not (eq ?resp primavera)) (not (eq ?resp verano)) (not (eq ?resp otoño)))
      (printout t "Valor Incorrecto. Introduce un valor (invierno|primavera|verano|otoño)" crlf)
      (bind ?resp (read))
   )
   (assert (Viajero epoca_de_viaje ?resp))
)

;; ¿Transporte? ;;

(defrule pregunta_transporte
   (not (Viajero transporte_pref ?))
=>
   (printout t "Cual es tu transporte preferido? (barco|avion|tren|coche)): " crlf)
   (bind ?resp (read))
   (while (and (not (eq ?resp barco)) (not (eq ?resp avion)) (not (eq ?resp tren)) (not (eq ?resp coche)))
      (printout t "Valor Incorrecto. Introduce un valor (barco|avion|tren|coche)" crlf)
      (bind ?resp (read))
   )
   (assert (Viajero transporte_pref ?resp))
)

;; Duracion de viaje?
(defrule pregunta_duracion_de_viaje
   (not (Viajero duracion_de_viaje ?))
=>
   (printout t "¿Cuanto tiempo quieres viajar? (corto|medio|largo): " crlf)
   (bind ?resp (read))
   (while (and (not (eq ?resp corto)) (not (eq ?resp medio)) (not (eq ?resp largo)))
      (printout t "Valor Incorrecto. Introduce un valor (corto|medio|largo)" crlf)
      (bind ?resp (read))
   )
   (assert (Viajero duracion_de_viaje ?resp))
)

;; ¿Presupuesto? ;;
(defrule pregunta_presupuesto
   (not (Viajero presupuesto ?))
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
   (assert (Viajero presupuesto bajo)) 
   (retract ?h)
)

(defrule valorar_presupuesto_medio
?h <- (p ?p)
(test (and (> ?p 1000) (<= ?p 3000)))
=>
   (assert (Viajero presupuesto medio)) 
   (retract ?h)
)

(defrule valorar_presupuesto_alto
?h <- (p ?p)
(test (> ?p 50))
=>
   (assert (Viajero presupuesto alto)) 
   (retract ?h)
)

;; Experiencia en viaje?
(defrule pregunta_experiencia_viajando
   (not (Viajero experiencia_viajando ?))
=>
   (printout t "¿Has viajado mucho? (si|no|regular): " crlf)
   (bind ?resp (read))
   (while (and (not (eq ?resp si)) (not (eq ?resp no)) (not (eq ?resp regular)))
      (printout t "Valor Incorrecto. Introduce un valor (si|no|regular)" crlf)
      (bind ?resp (read))
   )
   (assert (Viajero experiencia_viajando ?resp))
)

;; ¿Tipo de destino?
(defrule pregunta_tipo_de_destino
   (not (Viajero tipo_de_destino ?))
=>
   (printout t "¿Cual es tu tipo de destino? (playa|montaña|ciudad): " crlf)
   (bind ?resp (read))
   (while (and (not (eq ?resp playa)) (not (eq ?resp montaña)) (not (eq ?resp ciudad)))
      (printout t "Valor Incorrecto. Introduce un valor (playa|montaña|ciudad)" crlf)
      (bind ?resp (read))
   )
   (assert (Viajero tipo_de_destino ?resp))
)

;; Se elige un consejo a razón de las respuestas
(defrule gusta_viaje_playa
(OfertaRecibida No) ;; Estas reglas solo se aplican si el consejo aun no se ha deliberado
(Viajero tipo_de_destino ?tipodedestino)
(test (eq ?tipodedestino playa))
=>
   (assert (Elegido ES))
   (assert (Motivo "Te gusta la playa"))
   (assert (Experto "D. Experto Yerasito"))
   (assert (Razon tipo_de_destino))
   (assert (Razon temporada))
)

(defrule gusta_ciudad_y_dinero
(OfertaRecibida No)
(Viajero tipo_de_destino ?tipd)
(Viajero presupuesto ?presupuesto)
(test (eq ?tipd ciudad))
(test (eq ?presupuesto alto))
=>
   (assert (Elegido AL))
   (assert (Motivo "Te gusta la ciudad y tienes dinerico"))
   (assert (Experto "D. Experto Yerasito"))
)

(defrule gusta_viajar
(OfertaRecibida No)
(Viajero gusta_viajar ?viajar)
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
   ?e <- (Elegido ?el)
   ?m <- (Motivo ?mot)
   ?ex <- (Experto ?expt)
=>
   (assert (Adecuado (codigo ?el) (motivo ?mot) (experto ?expt)))
   (retract ?e)
   (retract ?m)
   (retract ?ex)
)

;; Imprime las respuestas ;;
(defrule datosViajero
   (declare (salience 9000))
   (Viajero edad ?edad)
   (Viajero epoca_de_viaje ?epoca)
   (Viajero transporte_pref ?trans)
   (Viajero duracion_de_viaje ?duraciondeviaje)
   (Viajero presupuesto ?pres)
   (Viajero experiencia_viajando ?exp)
   (Viajero tipo_de_destino ?tipodedestino)

=>
   (printout t "Datos viajero: " crlf)
   (printout t crlf "Edad: " ?edad crlf)
   (printout t "Epoca: " ?epoca crlf)
   (printout t "Transporte: " ?trans crlf)
   (printout t "Duracion de viaje: " ?duraciondeviaje crlf)
   (printout t "Presupuesto: " ?pres crlf)
   (printout t "Experiencia viajando: " ?exp crlf)
   (printout t "Tipo de destino: " ?tipodedestino crlf crlf)
)

; (defrule datosViaje
;    (declare (salience 9000))
;    (Adecuado (codigo ?el) (motivo ?texto) (experto ?experto))
;    (Viaje (codigo ?el) (destino ?r) (temporada ?temp) (transporte ?trans) (duracion ?dur) (precio ?prec) (beneficio_agencia ?ben))
; =>
;    (printout t "Datos viaje: " crlf)
;    (printout t "Viaje a " ?r "(" ?el "):" ?temp " " ?trans " " ?dur " " ?prec " " ?ben crlf)
; )

;; Se imprime un consejo ;;
(defrule ofrece_destino
   (declare (salience 9000))
   ?cr <- (OfertaRecibida No)
   (Adecuado (codigo ?el) (motivo ?texto) (experto ?experto))
   (Viaje (codigo ?el) (destino ?r))
=>
   (printout t ?experto " te aconseja el Destino " ?r "." crlf)
   (printout t "Motivo: " ?texto "." crlf)
   (printout t "¿Rechazas el destino? " crlf)
   (bind ?resp (read))
   (while (and (not (eq ?resp Si)) (not (eq ?resp No)))
      (printout t "Valor Incorrecto. Introduce un valor (Si|No) " crlf)
      (bind ?resp (read))
   )
   (assert (Rechazada ?resp) ) ;; Guarda si rechaza
   (retract ?cr)
   (assert (OfertaRecibida Si))
)

(defrule MotivoRechazo
   (declare (salience 9000))
   (Rechazada Si)
   ?adec <- (Adecuado (codigo ?el) (motivo ?mot) (experto ?expt))
=>
   (printout t "¿Cuál es tu motivo de rechazo?" crlf)
   
    (printout t "Hechos Razon encontrados:" crlf)
    (do-for-all-facts ((?r Razon)) TRUE
        ;; Obtenemos los nombres de los slots del hecho
        (bind ?slot-names (fact-slot-names ?r))
        ;; Iteramos sobre los slots del hecho
        (foreach ?slot-name ?slot-names
            ;; Obtenemos el valor del slot y lo imprimimos en la salida estándar
            (bind ?slot-value (fact-slot-value ?r ?slot-name))
            (printout t ?slot-value crlf)
        )
    )

   (bind ?motivo (read))
   (assert (MotivoRechazo ?motivo)) ; Hecho con el motivo de rechazo: tiempo, tipo, dinero, etc.
   (retract ?adec)
)

(defrule reofrecer
   (declare (salience 9000))
   (MotivoRechazo ?motivo)
   ?of <- (OfertaRecibida Si)
   ?resp <- (Viajero ?motivo ?valor) ; Ej. Se rechaza el tiempo (volveria a preguntar la duracion del viaje)
   ?r <- (Rechazada Si)
=>
   (printout t "Se rechaza " ?motivo " " ?valor crlf)
   (retract ?of) 
   (retract ?resp)
   (retract ?r)
  
   (assert (OfertaRecibida No))
)

;; Para que no siga haciendo preguntas
; (defrule FinPrograma
; (declare (salience 5000))
; (OfertaRecibida ?of)
; (test (eq ?of Si))
; =>
; (assert (Fin))
; )