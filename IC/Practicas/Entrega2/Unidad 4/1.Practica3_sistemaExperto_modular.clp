;;;; REALIZADO POR: Yeray Lopez Ramirez ;;;;;
;;;;           DNI: 26050768W		    ;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                                                EJERCICIO 3 DE LA PRACTICA 1                                                    ;;
;;                    Diseniar un Sistema Experto que asesore a un cliente en una agencia de viaje                                ;;
;;                sobre qué destino elegir de forma que el sistema actúe tal y como lo hariais vosotros                           ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; SISTEMA EXPERTO DE RECOMENDACION DE VIAJES ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Sistema de agencia de viajes por el cual se recomiendan basados en informacion de usuario y de viajes preseleccionados.        ;;
;; En concreto se pide al ususario de forma inicial la edad, la compania, la temporada, actividad y presupuesto.                  ;;
;; Con esos datos se ofrece un viaje acorde a los requisitos y posteriormente se le pregunta al usuario si quiere                 ;;
;; rechazar o no el destino, pudiendo añadir más requisitos como la duracion, el transporte, el lugar, la ubicacion y el tipo     ;;
;; El sistema termina cuando se ofrece un viaje y el usuario acepta. Se muestra un mensaje de despedida con el beneficio obtenido ;;
;; para la agencia.                                                                                                               ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; CREACION DE VIAJES ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Los viajes se crean en la regla Viajes donde crean todos los hechos con los viajes que ofrece la agencia. Se parte del         ;;
;; deftemplate original pero se añaden nuevas caracteristicas:                                                                    ;;
;; - publico: adulto mayor                                                                                                        ;;
;; - numero: una varias                                                                                                           ;;
;; - temporada (sustituye a dia_salida): invierno verano intermedia                                                               ;;
;; - lugar: rural urbano intermedio                                                                                               ;;
;; - ubicacion: nacional europeo internacional daigual                                                                            ;;
;; - tipo: playa montania interior                                                                                                ;;
;; - actividad: familiar deportivo negocios voluntariado                                                                          ;;
;; Se han creado 20 viajes con mas o menos sentido y con variedad. Están ordenados de mayor a menor beneficio para la agencia. Se ;;
;; eligirá el que de mayor beneficio y que se ajuste al usuario.                                                                  ;;
;; No tienen porque cumplirse todas las condiciones de viaje, al elegir la opcion "daigual" se ignora esa caracteristica.         ;;
;; He visto la necesidad de realizar varias simplificaciones aunque a vista de usuario no se percibe:
;; 1. La edad podia ser joven tambien pero se excluian actividades de adulto que eran validas
;; 2. El numero distinguia entre solo, pareja, familia o amigos pero se simplifica a uno/varios para facilitar la recomendacion   ;;
;; 3. La temporada primavera y otoño se consideran intermedia.
;; Aparte se hacen deducciones que se describen en el siguiente apartado.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; RECOMENDACION DE VIAJES ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Inicialmente se hacen 4-5 preguntas basicas para hacer una primera recomendacion. Una vez ofertada el usuario puede rechazarla ;;
;; y añadir cualquiera de las siguientes opciones:                                                                                ;;
;;    temporada | transporte | duracion | presupuesto | lugar de destino | ubicacion | tipo de destino | actividad                ;;
;; Cuanto mas especifico mas dificil sera recomendar pero mejor se ajustara al usuario. El sistema mejora exponencialmente al     ;;
;; aniadir mas destinos y se pueden introducir muy facilmente con un assert, el resto del trabajo es automatico.                  ;;
;; En el prototipo se trabajan con 20 destinos y 10 caracteristicas. Recomendaria aniadir muchos mas destinos pero no me quiero   ;;
;;    pasar de asserts de solo destinos ademas de que es eso, un prototipo.                                                       ;;
;;                                                                                                                                ;;
;; Para recomendar se toma el siguiente procedimiento:                                                                            ;;
;; 1. La edad: se preguntará de forma numérica y se transformará en adulto o mayor. Inicialmente podía ser joven pero se          ;;
;;        simplificó para facilitar la recomendación                                                                              ;;
;;    Los Viajes serán ofrecidos o bien para adultos o para mayores por lo que se eligiran según la edad dada. No es rechazable.  ;;
;;                                                                                                                                ;;
;; 2. La compania: se preguntará al usuario si va solo o acompañado, se distinguirá entre pareja, familia y amigos                ;;
;;    Los Viajes serán ofertados para una o varias personas pero se deducirá actividades según la compania:                       ;;
;;       - Si eliges solo: no se deduce.                                                                                          ;;
;;       - Si eliges pareja: se deduce actividad familiar. Inicialmente era romantica, se simplificó para recomendar más.         ;;
;;       - Si eliges familia: se deduce actividad familiar.                                                                       ;;
;;       - Si eliges amigos: no se deduce.                                                                                        ;; 
;;    No es rechazable.                                                                                                           ;;
;;                                                                                                                                ;;
;; 3. La temporada: se preguntará la estacion que desea al usuario aunque se simplificará sin que lo note.                        ;;
;;       - Si eliges primavera u otoño se simplificarán con estación intermedia, esto permite una mejor recomendación.            ;;
;;       - Se respetará si es invierno o verano.                                                                                  ;;
;;       - Se da la posibilidad de "daigual", en este caso se ignora la temporada al elegir el destino.                           ;;
;;    La mayoría de viajes ofertados son en verano o intermedias así que invierno puede ser dificil de recomendar.                ;;
;;    Se puede rechazar.                                                                                                          ;;
;; 4. El presupuesto: se preguntara la cantidad directamente. El sistema comparará si el precio de cada viaje es menor al         ;;
;;       dinero que pone el usuario. Se pide un minimo de 100€ aunque recomiendo poner sobre 600€-700€                            ;;
;;    Es rechazable, por si el destino es muy caro.                                                                               ;;
;; 5. (Depende) Si has elegido compania = solo o amigos entonces te hara una quinta pregunta sobre el tipo de viaje               ;;
;;    Se podra elegir entre: deportivo | negocios | voluntariado o daigual.                                                       ;;
;;    Cada viaje contiene una actividad especifica que determinara de forma clave la recomendacion. En caso de elegir daigual, se ;;
;;    elegira el viaje sin tener en cuenta su actividad.                                                                          ;;
;;                                                                                                                                ;;
;; Llegados a este punto el sistema puede llegar a 2 estados:                                                                     ;;
;;    1. Que te recomiende un viaje. Te mostrara el motivo completo de eleccion y si deseas aceptar el destino.                   ;;
;;       Si rechazas te preguntara el motivo de rechazo y te preguntara sobre lo que has rechazado, ofertando otro destino        ;;
;;    2. Que no te haga encontrado ningun viaje (mala suerte): entonces te dira si quieres cambiar la informacion proporcionada.  ;;
;;       Si aceptas cambiar los datos, te preguntara como si hubieses rechazado.                                                  ;;
;;       En cambio si no quieres cambiar los datos, se disculpara y te dara la despedida.                                         ;;
;;                                                                                                                                ;;
;; Una vez dentro de la dinamica de rechazar destinos para ir afinando pueden resultar en un nuevo destino (bien!) o si respondes ;;
;; a los transportes o a la ubicacion(nacional/internacional) te dara 4 posibles alternativas:                                    ;;
;; 1. Si elegiste el coche o nacional: te dira que cojas el coche por Espania hasta encontrar un destino que te guste.            ;;
;; 2. Si elegiste el tren o europeo: te dira que viajes en tren por Europa hasta encontrar el destino que te guste.               ;;
;; 3. Si elegiste el avion o internacional: te dira que pruebes a coger un vuelo a un destino aleatorio.                          ;;
;; 4. Si elegiste el barco: te dira de realizar un crucero por el Atlantico-                                                      ;;
;;                                                                                                                                ;;
;; Las posibilidades son variadas y las deducciones completas. Espero que el sistema sea satisfactorio.                           ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;ELECCION DE VIAJES;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; La eleccion de viajes se encarga el metodo decideViaje. Mediante un bucle (ahora explicare porque) recorre todos los Viajes    ;;
;; que tiene la agencia y los compara con los datos del usuario. Se busca que coincida la caracteristica con el dato del usuario  ;;
;; o se salta la caracteristica si es daigual. La incertidumbre da mayor libertad al sistema de recomendar.                       ;;
;;                                                                                                                                ;;
;; El primer viaje que cumpla los requisitos sera el de mayor beneficio de la agencia asi que se lo ofrece directamente.          ;;
;; El motivo dado seran las propiedades del viaje que se justifican con los datos proporcionados por el usuario                   ;;
;; El experto sera el creador del sistema: Yeray Lopez Ramirez, que es apodado como D. Yerasito                                   ;;
;;                                                                                                                                ;;
;; La ventaja de usar el bucle aqui es que permite aniadir de forma muy sencilla viajes sin hacer reglas especificas para cada    ;;
;; uno. Ademas aplica el mismo criterio para todos los viajes permitiendo que sea el sistema quien elija.                         ;; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;; Para usar un template, es igual que un hecho, solo que hay que indicar cada campo
(deftemplate Viaje
    (slot codigo
        (type SYMBOL)
    )
    (slot destino 
        (type STRING)
    )
    (slot publico
        (type SYMBOL)
        (allowed-symbols adulto mayor) ; joven simplificado como adulto
    )
    (slot numero
        (type SYMBOL)
        (allowed-symbols una varias) ; parejas, familia y amigos simplificado como varias
    )
    (slot temporada
        (type SYMBOL)
        (allowed-symbols invierno verano intermedia) ; otonio y primavera simplificadas como intermedia
    )
    (slot transporte
        (type SYMBOL)
        (allowed-symbols barco avion tren autobus coche) ;; autobus y coche se consideran de forma identica
    )
    (slot duracion
        (type SYMBOL)
        (allowed-symbols corta media larga) ;; se evalua numericamente por dias: [0-7] cort, [8-30] medio, +30 largo
    )
    (slot lugar
        (type SYMBOL)
        (allowed-symbols rural urbano intermedio) ; intermedio funciona igual que daigual/nose. Acepta rural y urbano
    )
    (slot ubicacion
        (type SYMBOL)
        (allowed-symbols nacional europeo internacional daigual) ; nacional infiere transporte coche, europeo infiere transporte tren, internacional infiere transporte avion.
    )
    (slot tipo
        (type SYMBOL)
        (allowed-symbols playa montania interior daigual) ; daigual permite ignorar la caracteristica 
    )
    (slot actividad
        (type SYMBOL)
        (allowed-symbols familiar deportivo negocios voluntariado) ; las parejas y familias infieren actividad familiar (inicialmente parejas=romantico)
    )
    (slot precio
        (type NUMBER) ; Se evalue que el precio < presupuesto
    )
    (slot beneficio_agencia
        (type SYMBOL)
        (default null)
        (allowed-symbols null bajo medio alto) ; se maximiza el beneficio ordenando los destinos de mayor a menor beneficio
    )
)

;; Se crean hechos con los viajes programados, estan ordenados por BENEFICIO DE LA AGENCIA. >>> BEFINICIO PRIMERO ;;
;; La mitad han sido generados mediante IA (es mas original que yo) y revisados manualmente.
(defrule Viajes
   (declare(salience 100))
=>
(assert (Viaje (codigo MX) (destino "Cancún, México") (publico adulto) (numero varias) (temporada verano) (transporte avion) 
               (duracion corta) (lugar urbano) (ubicacion internacional) (tipo playa) (actividad familiar) (precio 600) (beneficio_agencia alto)))

(assert (Viaje (codigo AU) (destino "Sydney, Australia") (publico adulto) (numero una) (temporada verano) (transporte avion) 
               (duracion larga) (lugar urbano) (ubicacion internacional) (tipo playa) (actividad voluntariado) (precio 300) (beneficio_agencia alto)))

(assert (Viaje (codigo ES04) (destino "Granada, Espania") (publico mayor) (numero una) (temporada invierno) (transporte autobus) (duracion corta)
               (lugar urbano) (ubicacion nacional) (tipo montania) (actividad deportivo) (precio 100) (beneficio_agencia alto))) 

(assert (Viaje (codigo JP) (destino "Tokio, Japón") (publico adulto) (numero una) (temporada intermedia) (transporte avion) 
               (duracion larga) (lugar urbano) (ubicacion internacional) (actividad negocios) (tipo interior) (precio 400) (beneficio_agencia alto)))

(assert (Viaje (codigo IT) (destino "Toscana, Italia") (publico mayor) (numero varias) (temporada verano) (transporte tren) (duracion corta)
               (lugar rural) (ubicacion europeo) (tipo montania) (actividad familiar) (precio 1000) (beneficio_agencia alto)))

(assert (Viaje (codigo CA) (destino "Vancouver, Canadá") (publico adulto) (numero una) (temporada invierno) (transporte avion) 
               (duracion corta) (lugar urbano) (ubicacion internacional) (tipo interior) (actividad deportivo) (precio 600) (beneficio_agencia medio)))

(assert (Viaje (codigo FR) (destino "París, Francia") (publico adulto) (numero varias) (temporada intermedia) (transporte tren)
               (duracion corta) (lugar urbano) (ubicacion europeo) (tipo interior) (precio 300) (actividad familiar) (beneficio_agencia medio)))

(assert (Viaje (codigo TH) (destino "Phuket, Tailandia") (publico adulto) (numero una) (temporada verano) (transporte avion) 
               (duracion larga) (lugar rural) (ubicacion internacional) (tipo playa) (precio 700) (actividad voluntariado) (beneficio_agencia medio)))

(assert (Viaje (codigo ES00) (destino "Cantabria, Espania") (publico mayor) (numero una) (temporada invierno) (transporte autobus) 
               (duracion media) (lugar urbano) (ubicacion nacional) (tipo montania) (actividad negocios) (precio 200) (beneficio_agencia bajo)))
               
(assert (Viaje (codigo ES01) (destino "Valencia, Espania") (publico adulto) (numero una) (temporada verano) (transporte coche) 
               (duracion corta) (lugar urbano) (ubicacion nacional) (tipo interior) (actividad negocios) (precio 400) (beneficio_agencia medio)))

(assert (Viaje (codigo GR) (destino "Islas Griegas") (publico mayor) (numero una) (temporada intermedia) (transporte barco) (duracion corta) 
               (lugar rural) (ubicacion europeo) (tipo playa) (actividad voluntariado) (precio 400) (beneficio_agencia alto)))

(assert (Viaje (codigo CU) (destino "La habana, Cuba") (publico adulto) (numero varias) (temporada invierno) (transporte barco) (duracion larga)
               (lugar rural) (ubicacion internacional) (tipo playa) (actividad familiar) (precio 500) (beneficio_agencia medio)))

(assert (Viaje (codigo ES05) (destino "Santiago de Compostela, Espania") (publico adulto) (numero una) (temporada intermedia) (transporte autobus)
               (duracion corta) (lugar rural) (ubicacion nacional) (tipo interior) (actividad deportivo) (precio 200) (beneficio_agencia bajo)))

(assert (Viaje (codigo PE) (destino "Lima, Perú") (publico adulto) (numero una) (temporada verano) (transporte avion) (duracion larga) 
               (lugar urbano) (ubicacion internacional) (tipo playa) (actividad voluntariado) (precio 600) (beneficio_agencia bajo)))

(assert (Viaje (codigo UG) (destino "Kampala, Uganda") (publico adulto) (numero una) (temporada verano) (transporte avion) (duracion larga)
              (lugar rural) (ubicacion internacional) (tipo interior) (actividad voluntariado) (precio 400) (beneficio_agencia bajo)))

(assert (Viaje (codigo ES02) (destino "Asturias, Espania") (publico mayor) (numero una) (temporada invierno) (transporte autobus)
               (duracion larga) (lugar rural) (ubicacion nacional) (tipo interior) (actividad deportivo) (precio 500) (beneficio_agencia bajo)))

(assert (Viaje (codigo ES03) (destino "Ceuta, Espania") (publico adulto) (numero varias) (temporada verano) (transporte barco)
               (duracion corta) (lugar intermedio) (ubicacion nacional) (tipo playa) (actividad familiar) (precio 100) (beneficio_agencia bajo)))
)

;;;; Si se ha creado el deffacts Viajero para crear un hecho de este tipo es (Viajero (edad ?m) ... (tipo_de_destino ?p))
;;;; Y se crea el hecho
(deffacts Viajero
   (edad e) ; joven, media, mayor
   (compania c); solo, pareja, familia, amigos
   (temporada ep) ; invierno, primavera, verano, otonio
   (transporte trans) ; barco, avion, tren, coche
   (duracion_de_viaje d) ; corto, medio, largo
   (presupuesto p) ; bajo, medio, alto
   (lugar_de_destino lug) ; rural, urbano, intermedio
   (ubicacion_geografica ubi) ; nacional, europeo, internacional
   (tipo_destino tip) ; playa, montania, interior
   (actividad act) ; playa, montania, interior
)

; (Adecuado <nombre del destino> “<texto del motivo>” “apodo del experto”) ;
; Se crea la plantilla para organizar qué contiene un consejo de destino adecuado
(deftemplate Adecuado
  (slot codigo
    (type SYMBOL)
  )
  (slot motivo
    (type LEXEME) ; Es un STRING pero admite textos mas largos """LEXEME"""
    (default ?DERIVE)
  )
  (slot experto
    (type STRING)
    (default "Clips")
    (allowed-strings "Clips" "D. Experto Yerasito") ; El experto es mi nick
  )
)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; EL SISTEMA EMPIEZA AQUI ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defrule Da_bienvenida
  (declare (salience 100))
=>
  (printout t "Sistema de Asesoramiento de Destinos. Hay una gran variedad a elegir así que" crlf)
  (printout t "se haran una serie de preguntas para poder recomendar la mejor eleccion." crlf )
  (assert (OfertaRecibida no)) ;; Será la condición de parada del programa
  (assert (Decidido no))
)

;;;;; REGLAS PARA HACER PREGUNTAS ;;;;;

;; ¿Edad? ;;
(defrule pregunta_edad
   (not (Viajero edad ?))
=>
   (printout t "¿Cual es tu edad? (NUMERO)): ")
   (bind ?resp (read))
   (while (or(not (numberp ?resp)) (< ?resp 18) (> ?resp 120)) ;; La edad debe ser numerica y en el rango [18-120]
      (printout t "Valor Incorrecto. Introduce tu edad (NUMERO[18-120]): ")
      (bind ?resp (read))
   )
   (assert (e ?resp))
)
;; Infiere edad ;;
;; Los adultos se consideran menor de 50 y mayores a partir de 50, espero no herir a nadie ;;
(defrule valorar_edad_adulto
?h <- (e ?e)
(test (<= ?e 50))
=>
   (assert (Viajero edad adulto)) 
   (retract ?h)
)

(defrule valorar_edad_mayor
?h <- (e ?e)
(test (> ?e 50))
=>
   (assert (Viajero edad mayor)) 
   (retract ?h)
)

;; ¿Compania? ;;
;; El usuario percibe que puede elegir pero realmente su respuesta sera simplificada a una/varias personas.
(defrule pregunta_compania
   (not (Viajero compania ?))
=>
   (printout t "¿Cuantos viajan? (solo|pareja|familia|amigos): ")
   (bind ?resp (read))
   (while (and (not (eq ?resp solo)) (not (eq ?resp pareja)) (not (eq ?resp familia)) (not (eq ?resp amigos)))
      (printout t "Valor Incorrecto. Introduce un valor (solo|pareja|familia|amigos): ")
      (bind ?resp (read))
   )
   (assert (Viajero compania ?resp))
)

; Simplifica la respuesta e infiere actividad familiar para las parejas y familias
; Inicialmente la mayoria de la informacion no es obligatoria y se omite
(defrule deduce_compania
   (and(not(Viajero compania una)) (not(Viajero compania varias)))
   ?r <- (Viajero compania ?comp)
   =>
   (if 
      (eq ?comp solo) then 
         (assert (Viajero compania una))
      else
         (assert (Viajero compania varias))
         (if 
            (or(eq ?comp pareja) (eq ?comp familia)) then 
               (assert (Viajero actividad familiar))
         )
   )

   ; Inialmente se parte de la minima informacion, luego segun rechace se le preguntan cosas específicas
   (assert (Viajero transporte daigual))
   (assert (Viajero duracion_de_viaje media))
   (assert (Viajero ubicacion_geografica daigual))
   (assert (Viajero lugar_de_destino intermedio))
   (assert (Viajero tipo_destino daigual))

   (retract ?r)

   ; Solo/amigos requiere de otra pregunta de actividad
)

;; ¿Temporada? ;;
;; Elegir entre primavera/otonio da como resultado intermedia pero al usuario le damos a elegir
(defrule pregunta_temporada
   (not (Viajero temporada ?))
=>
   (printout t "¿En que temporada quieres viajar? (invierno|primavera|verano|otonio|daigual): ")
   (bind ?resp (read))
   (while (and (not (eq ?resp invierno)) (not (eq ?resp primavera)) (not (eq ?resp verano)) (not (eq ?resp otonio)) (not (eq ?resp daigual)))
      (printout t "Valor Incorrecto. Introduce un valor (invierno|primavera|verano|otonio|daigual): ")
      (bind ?resp (read))
   )
   
   (if
      (or(eq ?resp verano) (eq ?resp invierno)) then
      (assert (Viajero temporada ?resp))
   else
      (assert (Viajero temporada intermedia))
   )
)

;; Se le pregunta la actividad que desea realizar en el viaje. Es muy determinante ya que son muchas opciones y cierra las
;; recomendaciones enormemente por lo que se procedera a preguntarle el presupuesto directamente
(defrule actividad_viaje
   (not (Viajero actividad ?))
=>
   (printout t "¿Como te gustan los viajes? (deportivo|negocios|voluntariado|daigual): ")
   (bind ?resp (read))
   (while (and (not (eq ?resp deportivo)) (not (eq ?resp negocios)) (not (eq ?resp voluntariado)) (not (eq ?resp daigual)))
      (printout t "Valor Incorrecto. Introduce un valor (deportivo|negocios|voluntariado|daigual): ")
      (bind ?resp (read))
   )

   (assert (Viajero actividad ?resp))
)

;; ¿Transporte? ;;
;; El autobus se considera igual que el coche, se le da sensacion de eleccion al usuario
(defrule pregunta_transporte
   (not (Viajero transporte ?))
=>
   (printout t "¿En qué transporte te gustaría viajar? (barco|avion|tren|coche|autobus|daigual)): ")
   (bind ?resp (read))
   (while (and (not (eq ?resp barco)) (not (eq ?resp avion)) (not (eq ?resp tren)) (not (eq ?resp coche)) (not (eq ?resp autobus)) (not (eq ?resp daigual)))
      (printout t "Valor Incorrecto. Introduce un valor (barco|avion|tren|coche|autbous|daigual): ")
      (bind ?resp (read))
   )
   ; Flexibilizar datos, sino es muy dificil recomendar
   (if
      (eq ?resp autobus) then
      (assert (Viajero transporte coche))
   else
      (assert (Viajero transporte ?resp))
   )
)

;; Infiere hechos de ubicacion segun el transporte
; Si elige un coche lo normal es que busque destinos nacionales, un tren para los europeos e internacional para el avion y el barco
(defrule deduce_transporte
   (Viajero transporte ?trans)
   =>
   (if
      (or(eq ?trans coche) (eq ?trans autobus)) then 
         (assert (Viajero ubicacion_geografica nacional)) ; En coche/autobus no tendras pensado ir muy lejos
   )
   (if 
      (eq ?trans tren) then 
         (assert (Viajero ubicacion_geografica europa)) ; El tren es util sobre todo en europa
   )
   (if 
      (or(eq ?trans barco) (eq ?trans avion)) then 
         (assert (Viajero ubicacion_geografica internacional)) ; los barcos y aviones son perfectos para viajes internacionales
   )
)
; Solo si no sabe que transporte coger
;; Si o si se inferira el transporte y la ubicacion ya que son importantes
(defrule preguntar_ubicacion
   (not (Viajero ubicacion_geografica ?))
   ?r <- (Viajero transporte daigual)
=>
   (printout t "¿Te gustaría ir al extranjero? (si|no|daigual): ")
   (bind ?resp (read))
   (while (and (not (eq ?resp si)) (not (eq ?resp no)) (not (eq ?resp daigual)))
      (printout t "Valor Incorrecto. Introduce un valor (si|no|daigual): " )
      (bind ?resp (read))
   )
   (if
      (eq ?resp si) then
         (printout t "¿A europa o mas lejos? (europa|fuera): ")
         (bind ?resp (read))
         (while (and (not (eq ?resp europa)) (not (eq ?resp fuera)))
            (printout t "Valor Incorrecto. Introduce un valor (europa|fuera): ")
            (bind ?resp (read))
         )
         (if
            (eq ?resp europa) then
               (assert (Viajero ubicacion_geografica europa))
               (assert (Viajero transporte tren))
         )
         (if
            (eq ?resp fuera) then
               (assert (Viajero ubicacion_geografica internacional))
               (assert (Viajero transporte avion))
         )
   )
   (if
      (eq ?resp no) then ; No ir al extranjero implica ir por Espania con el coche/autobus
         (assert (Viajero ubicacion_geografica nacional))
         (assert (Viajero transporte coche))
   )
   ; Si no sabe ni el transporte ni donde ir le ponemos internacional y con avion que da mas posibilidad de recomendar
   (if
      (eq ?resp daigual) then
         (assert (Viajero ubicacion_geografica internacional))
         (assert (Viajero transporte avion))
   )
   (retract ?r)
   (assert (Viajero ubicacion_geografica ?resp))

)

;; Duracion de viaje?
;; Pregunta un numero. Como minimo 2 dias
(defrule pregunta_duracion_de_viaje
   (not (Viajero duracion_de_viaje ?))
=>
   (printout t "¿Cuanto tiempo quieres viajar? (en dias): ")
   (bind ?resp (read))
   (while (or(not (numberp ?resp))(< ?resp 2))
      (printout t "Valor Incorrecto. Introduce un valor (numerico en dias) [>=2]: ")
      (bind ?resp (read))
   )
   (assert (d ?resp))
)

;; Infiere la duracion [0-7] corta, [8-30] media y +30 es larga
(defrule valorar_duracion_corta
?h <- (d ?d)
(test (<= ?d 7))
=>
   (assert (Viajero duracion_de_viaje corto)) 
   (retract ?h)
)

(defrule valorar_duracion_medio
?h <- (d ?d)
(test (and (> ?d 7) (<= ?d 30)))
=>
   (assert (Viajero duracion_de_viaje medio)) 
   (retract ?h)
)

(defrule valorar_duracion_larga
?h <- (d ?d)
(test (> ?d 30))
=>
   (assert (Viajero duracion_de_viaje largo)) 
   (retract ?h)
)

;; ¿Lugar de destino?
(defrule pregunta_lugar_de_destino
   (not (Viajero lugar_de_destino ?))
=>
   (printout t "¿Que lugar prefieres? (rural|urbano|intermedio): ")
   (bind ?resp (read))
   (while (and (not (eq ?resp rural)) (not (eq ?resp urbano)) (not (eq ?resp intermedio)))
      (printout t "Valor Incorrecto. Introduce un valor (rural|urbano|intermedio): ")
      (bind ?resp (read))
   )
   (assert (Viajero lugar_de_destino ?resp))
)

;; ¿Tipo de destino?
(defrule pregunta_tipo_destino
   (not (Viajero tipo_destino ?))
=>
   (printout t "¿Qué zona geográfica te gusta? (playa|montania|interior|daigual): ")
   (bind ?resp (read))
   (while (and (not (eq ?resp playa)) (not (eq ?resp montania)) (not (eq ?resp interior)) (not (eq ?resp daigual)))
      (printout t "Valor Incorrecto. Introduce un valor (playa|montania|interior|daigual): ")
      (bind ?resp (read))
   )
   (assert (Viajero tipo_destino ?resp))
)

;; ¿Presupuesto? ;;
(defrule pregunta_presupuesto
   (not (Viajero presupuesto ?))
=>
   (printout t "¿Cual es tu presupuesto? (NUMERO)[>100€, recomiendo 600€]: ")
   (bind ?resp (read))
   (while (or (not (numberp ?resp)) ( <= ?resp 100))
      (printout t "Valor Incorrecto. Introduce tu presupuesto (NUMERO)[>100€, recomiendo 600€]: ")
      (bind ?resp (read))
   )
   (assert (Viajero presupuesto ?resp))
)

;; Funcion principal de decision de viaje, explicada al principio
;; 1. Recibe datos del usuario
;; 2. Para cada viaje:
;;    2.1 - Compara cada hecho. Ignora los daigual
;;    2.2 - Genera un viaje Adecuado y sale del bucle
(defrule decideViaje
   ; Que no haya otro destino decidido ya
   ?dec <- (Decidido no)
   ; Obtenemos datos del viajero
   (Viajero edad ?edad) ; joven, media, mayor
   (Viajero compania ?compania) ; una, varias
   (Viajero temporada ?temporada) ; invierno, primavera, verano, otonio, daigual
   (Viajero duracion_de_viaje ?duracion) ; corto, medio, largo
   (Viajero presupuesto ?presupuesto) ; numero
   (Viajero lugar_de_destino ?lugardedestino) ; rural, urbano, intermedio
   (Viajero ubicacion_geografica ?ubicacion) ; nacional, europeo, internacional
   (Viajero tipo_destino ?tipodestino) ; Playa, montania, interior
   (Viajero actividad ?actividad) ; Playa, montania, interior
=>
   (do-for-all-facts ((?v1 Viaje))
         ; Condiciones presupuesto>publico>numero>temporada>duracion>ubicacion>
         (and (>= ?presupuesto ?v1:precio) ; No admite incertidumbre
              (eq ?edad ?v1:publico) ; No admite incertidumbre
              (eq ?compania ?v1:numero) ; No admite incertidumbre
              (or(eq ?temporada ?v1:temporada)(eq ?temporada intermedia) (eq ?temporada daigual)) ; Informacion parcial
              (or(eq ?duracion ?v1:duracion) (eq ?duracion media)) ; Los de duracion media admiten corta/larga
              (or (eq ?lugardedestino ?v1:lugar) (eq ?lugardedestino intermedio)) ; Los de destino intermedio admiten rurales/urbanos
              (or(eq ?ubicacion ?v1:ubicacion) (eq ?ubicacion daigual)) ; Informacion parcial
              (or(eq ?tipodestino ?v1:tipo) (eq ?tipodestino daigual)) ; Informacion parcial
              (or (eq ?actividad ?v1:actividad) (eq ?actividad daigual))) ; Informacion parcial
           (assert (Adecuado (codigo ?v1:codigo)
            (motivo (str-cat 
"""El presupuesto es de """ ?v1:precio """€ y se dispone de """ ?presupuesto """€.
Se recomienda para """ ?edad """.
Va dirigido a """ ?v1:numero """ persona/s.
El destino se ofrece para """ ?v1:temporada """.
La duracion estipulada es """ ?v1:duracion """.
El lugar de destino es """ ?v1:lugar """.
Es un destino """ ?v1:ubicacion """.
El destino ofrece una zona de """ ?v1:tipo """.
Se pueden realizar actividades de """ ?v1:actividad
))
            (experto "D. Experto Yerasito")))

            (assert (Decidido si))
            (retract ?dec)
            (break)
   )
)

; Si no encuentra respuesta...
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; RECOMENDACIONES POR DEFECTO: POR TRANSPORTE ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defrule consejo_por_defecto_barco
   (declare (salience -1))
   (Decidido no)
   (Viajero transporte barco)
   ?cr <- (OfertaRecibida no)
=>
   (printout t "En tu caso ha sido dificil elegir un viaje en concreto." crlf)
   (printout t "Quizas la solucion sea un crucero sobre el Atlántico y elegir el país que más te guste." crlf)
   (retract ?cr)
   (assert (OfertaRecibida si))
)

(defrule consejo_por_defecto_avion
   (declare (salience -1))
   (Decidido no)
   (Viajero transporte avion)
   ?cr <- (OfertaRecibida no)
=>
   (printout t "En tu caso ha sido dificil elegir un viaje en concreto." crlf)
   (printout t "Quizas la solucion sea coger varios vuelos por el mundo y elegir el país que más te guste." crlf)
   (retract ?cr)
   (assert (OfertaRecibida si))
)

(defrule consejo_por_defecto_tren
   (declare (salience -1))
   (Decidido no)
   (Viajero transporte tren)
   ?cr <- (OfertaRecibida no)
=>
   (printout t "En tu caso ha sido dificil elegir un viaje en concreto." crlf)
   (printout t "Quizas la solucion sea coger el tren y visitar diferentes ciudades Europeas." crlf)
   (printout t "Seguro que encuentras algún destino que te guste." crlf)
   (retract ?cr)
   (assert (OfertaRecibida si))
)

(defrule consejo_por_defecto_coche
   (declare (salience -1))
   (Decidido no)
   (Viajero transporte coche)
   ?cr <- (OfertaRecibida no)
=>
   (printout t "En tu caso ha sido dificil elegir un viaje en concreto." crlf)
   (printout t "Quizas la solucion sea coger el coche y visitar diferentes ciudades y pueblos de Espania." crlf)
   (printout t "Seguro que encuentras algún destino que te guste." crlf)
   (retract ?cr)
   (assert (OfertaRecibida si))
)

;; Si el programa llega hasta aqui sin una respuesta
(defrule consejo_por_defecto
   (declare (salience -1))
   (Decidido no)
   ?cr <- (OfertaRecibida no)
=>
   (printout t crlf "Oh vaya, que mala suerte :(" crlf)
   (printout t "En tu caso no he sido capaz de recomendarte un viaje en concreto." crlf)
   (printout t "Deseas probar suerte cambiando los datos? (si|no): ")
   (bind ?resp (read))
   (while (and (not (eq ?resp si)) (not (eq ?resp no)))
      (printout t "Valor Incorrecto. Introduce un valor (si|no): " )
      (bind ?resp (read))
   )
   (if 
      (eq ?resp si) then
         (assert(Adecuado (codigo null) (motivo "") (experto "Clips")))
         (assert (Aceptada no)) ; El hecho es como si rechazara, pregunta el motivo de rechazo
   )
   (if 
      (eq ?resp no) then
         (printout t "Sentimos mucho no poder ayudarle. Esperemos volverle a ver pronto!" crlf)
   )
   (retract ?cr)
   (assert (OfertaRecibida si))
)

;; Se imprime un consejo ;;
(defrule ofrece_destino
   (declare (salience 9000))
   ?cr <- (OfertaRecibida no)
   ?dec <- (Decidido si)
   (Adecuado (codigo ?el) (motivo ?texto) (experto ?experto))
   (Viaje (codigo ?el) (destino ?r))
=>
   (printout t "---------------------------------------------------------------------------" crlf)
   (printout t ?experto " te aconseja el Destino: " ?r "." crlf)
   (printout t crlf "Motivos: " ?texto "." crlf)
   (printout t "---------------------------------------------------------------------------" crlf)
   (printout t crlf "Aceptas el destino? ")
   (bind ?resp (read))
   (while (and (not (eq ?resp si)) (not (eq ?resp no)))
      (printout t "Valor Incorrecto. Introduce un valor (si|no): " )
      (bind ?resp (read))
   )
   (assert (Aceptada ?resp) ) ;; Guarda si rechaza
   (retract ?cr)
   (retract ?dec)
   (assert (OfertaRecibida si))
)

; Sugiera al usuario elegir el motivo a rechazar y manda el motivo a rechazar. La siguiente regla se encarga de efectuar el rechazo
(defrule MotivoRechazo
   (declare (salience 9000))
   (Aceptada no)
   ?adec <- (Adecuado (codigo ?el) (motivo ?mot) (experto ?expt))
=>
   (printout t "¿Cuál es tu motivo de rechazo? Elige una" crlf)
   (printout t "(temporada|transporte|duracion|presupuesto|lugar de destino|ubicacion|zona de destino|actividad): " crlf)
   (bind ?motivo (read))
   (while (and (not (eq ?motivo temporada)) (not (eq ?motivo transporte)) (not (eq ?motivo duracion)) (not (eq ?motivo presupuesto)) 
      (not (eq ?motivo lugar)) (not (eq ?motivo ubicacion)) (not (eq ?motivo zona)) (not (eq ?motivo actividad)) )
      
      (printout t "Valor Incorrecto. Introduce un valor")
      (printout t "(temporada|transporte|duracion|presupuesto|lugar de destino|ubicacion|zona de destino|actividad): " crlf)
      (bind ?motivo (read))
   )
   (if 
      (eq ?motivo duracion) then 
      (bind ?motivo duracion_de_viaje)
   )
   (if 
      (eq ?motivo lugar) then 
      (bind ?motivo lugar_de_destino)
   )
   (if 
      (eq ?motivo ubicacion) then 
      (bind ?motivo ubicacion_geografica)
   )
   (if 
      (eq ?motivo zona) then 
      (bind ?motivo tipo_destino)
   )

   (assert (MotivoRechazo ?motivo)) ; Hecho con el motivo de rechazo: tiempo, tipo, dinero, etc.
   (retract ?adec)
)

;; Gestiona el motivo que se rechaza, eso hace que le pregunte al usuario unicamente por lo que se rechaza
(defrule reofrecer
   (declare (salience 9000))
   ?motv <- (MotivoRechazo ?motivo)
   ?of <- (OfertaRecibida si)
   ?resp <- (Viajero ?motivo ?valor) ; Ej. Se rechaza el tiempo (volveria a preguntar la duracion del viaje)
   ?r <- (Aceptada no)
=>
   (printout t "Se rechaza " ?motivo " " ?valor crlf)
   (retract ?of) 
   (retract ?resp)
   (retract ?r)
   (retract ?motv)
   (assert (Decidido no))
   (assert (OfertaRecibida no))
)

; Se despide amablemente
(defrule Despedida
   (declare (salience 9000))
   ?r <- (Aceptada si)
   ?of <- (OfertaRecibida si)
   (Adecuado (codigo ?el) (motivo ?texto) (experto ?experto))
   (Viaje (codigo ?el) (beneficio_agencia ?ben))
=>
   (printout t "Gracias por contactar con nosotros! Disfrute del viaje." crlf)
   (printout t "-------------------Vista para la agencia----------------------" crlf)
   (printout t "El beneficio obtenido para la agencia es " ?ben crlf)
   (printout t "--------------------------------------------------------------" crlf)
   (retract ?r)
   (retract ?of)
)