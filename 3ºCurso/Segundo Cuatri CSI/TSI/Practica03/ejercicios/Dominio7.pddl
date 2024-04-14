(define (domain starcrfd7)
    (:requirements :strips :typing :fluents :negative-preconditions :conditional-effects :disjunctive-preconditions :universal-preconditions :equality)
    (:types
        ;; Los recursos no tienen objetos, solo tipos de recursos
        ;; Las unidades y los edificios pueden ser instanciados, por eso hay tipo y no tipos.
        Unidad tipoUnidad Edificio tipoEdificio Localizacion tipoRecurso - object
    )
    (:constants 
        ; subclases de cada objeto.
        VCE Marine Soldado - tipoUnidad
        CentroDeMando Barracones Extractor - tipoEdificio
        Minerales Gas Especia - tipoRecurso
        accion - Acciones
    )
    (:predicates
        ;; Un edificio, Unidad o Recurso esta en una Localizacion concreta
        (en ?e - object ?l - Localizacion)

        ;; Existe un camino entre dos localizaciones
        ;; Conectar dos localizaciones para formar el grid
        (conectado ?l1 - Localizacion ?l2 - Localizacion)

        ;; Se dispone del recurso
        (generando ?r - tipoRecurso)

        ; La unidad está libre (no extrae un recurso)
        (libre ?u)

        ; La unidad esta recolectando un recurso
        (extrayendo ?u ?tr)

        ; Tipo de edificio
        (esTipoEdificio ?e - edificio ?t - tipoEdificio)

        ; Tipo de Unidad
        (esTipoUnidad ?u - unidad ?t - tipoUnidad)

        ; Materiales que el edificio necesita
        (necesita ?to - object ?tr - tipoRecurso)

        ; Si un edificio está construido
        (construido ?e - Edificio)

        ; Donde se recluta la unidad
        (recluta ?u - tipoUnidad ?te - tipoEdificio)

        ; Ya esté reclutada
        (reclutada ?u)

    )
    (:functions
        ; Contador de acciones
        (NumeroAcciones)

        ; Almacen de Minerales y Gas
        (AlmacenRecursos ?tr - tipoRecurso)

        ; La cantidad de recurso necesaria para cualquier entidad
        (necesitaRecurso ?o - object ?r - tipoRecurso)
    )
    
    ;; Navegar: mueve una unidad entre dos localizaciones
    ;; Parámetros: Unidad, Localizacion Origen, Localizacion destino
    (:action Navegar
        :parameters (?u - Unidad ?lorig - Localizacion ?ldest - Localizacion)
        :precondition
            (and                
                ; La unidad está libre
                (libre ?u)
                
                ; La unidad está en la localizacion origen
                (en ?u ?lorig)

                ; Están conectadas las localizaciones
                (conectado ?lorig ?ldest)
            )
        :effect
            (and
                ; La unidad se mueva a localizacion de destino
                (en ?u ?ldest)

                ; La unidad ya no está en la localización de origen
                (not (en ?u ?lorig))

                ; El numero de acciones incrementa
                (increase (NumeroAcciones) 1)
            )
    )

    ;; Asignar: asigna un VCE a un nodo recurso
    ;; Parámetros: Unidad, Recurso, Tipo de Recurso, Localización del recurso
    (:action Asignar
        :parameters (?u - Unidad ?l - Localizacion)
        :precondition
            (and
                ; La unidad está libre
                (libre ?u)

                ; Debe ser VCE
                (esTipoUnidad ?u VCE)

                ; La unidad está en la localización
                (en ?u ?l)

                ; O bien extrae Minerales o Gas
                (or
                    (en Minerales ?l) ; Los minerales no requieren edificio
                    
                    (en Especia ?l) ; La especia no requieren edificio

                    (and ; El gas requiere extractor
                        (en Gas ?l)
                        (exists (?e - edificio) 
                            (and 
                                (esTipoEdificio ?e Extractor) ; Es un extractor
                                (construido ?e) ; Está ya construido (redundancia)
                                (en ?e ?l) ; El edificio está en la localización
                            )
                        )                        
                    )
                )
            )
        :effect
            (and
                ; La unidad extrae y no hace otra cosa más
                (not(libre ?u))
                ; Si hay un desposito de algo en ?l, lo está generando
                (forall (?tr - tipoRecurso)
                    (when (en ?tr ?l)
                        (and 
                            (generando ?tr)
                            (extrayendo ?u ?tr)
                        )
                    )
                )

                ; El numero de acciones incrementa
                (increase (NumeroAcciones) 1)
            )
    )
    
    ;; Construir: construye un Edificio en un nodo
    ;; Parámetros: Unidad, Edificio, Localizacion
    (:action Construir
      :parameters (?u - Unidad ?e - Edificio ?l - Localizacion)
      :precondition
        (and
            ; La unidad está libre
            (libre ?u)

            ; La unidad es un VCE
            (esTipoUnidad ?u VCE)

            ; Está en la localización
            (en ?u ?l)

            ; No está ya construido
            (not (construido ?e))

            ; El edificio necesita recursos especificos de su tipo
            (forall (?tr - tipoRecurso ?te - tipoEdificio)
                (imply
                    ; Si el tipo de edificio necesita el recurso
                    (and 
                        (esTipoEdificio ?e ?te)
                        (necesita ?te ?tr)
                    )
                    
                    ; Entonces tiene que estar disponible dicho recurso
                    (and
                        (generando ?tr) 
                        (>= (AlmacenRecursos ?tr) (necesitaRecurso ?te ?tr))
                    )
                )
            )

        )
      :effect
        (and
            ; Se construye dicho edificio
            (construido ?e)
            ; Se construye el edificio
            (en ?e ?l)

            ; Se gastan recursos
            (forall (?tr - tipoRecurso ?te - tipoEdificio)
                (when (and (esTipoEdificio ?e ?te) (necesita ?te ?tr)) 
                    (and
                        (decrease (AlmacenRecursos ?tr) (necesitaRecurso ?te ?tr))     
                    )
                )
            )

            ; El numero de acciones incrementa
            (increase (NumeroAcciones) 1)
        )
    )

    ;; Reclutar: crea nuevas unidades
    ;; Parámetros: Edificio, Unidad, Localizacion
    (:action Reclutar
      :parameters (?e - Edificio ?u - Unidad ?l - Localizacion)
      :precondition
        (and
            ; Está construido el edificio necesario
            (construido ?e)
            (not (Reclutada ?u))
            ; Esta libre la unidad
            (libre ?u)

            ; La unidad necesita recursos especificos de su tipo
            (forall (?tr - tipoRecurso ?tu - tipoUnidad)
                    (imply
                        ; Si el tipo de unidad necesita el recurso
                        (and
                            (esTipoUnidad ?u ?tu)
                            (necesita ?tu ?tr)                            
                        )
                        ; Entonces tiene que estar disponible dicho recurso
                        (and
                            (generando ?tr) 
                            (>= (AlmacenRecursos ?tr) (necesitaRecurso ?tu ?tr))
                        )
                    )
            )
            ; La unidad se recluta en un edificio concreto
            (exists (?te - tipoEdificio ?tu - tipoUnidad)
                (and
                    (esTipoEdificio ?e ?te)
                    (esTipoUnidad ?u ?tu)
                    (recluta ?tu ?te)
                    (en ?e ?l)
                )   
            )
        )
    :effect
        (and
            ; Se crea una unidad en la localizacion del edificio
            (en ?u ?l)

            ; Ya esta reclutada
            (Reclutada ?u)

            ; Se gastan recursos
            (forall (?tr - tipoRecurso ?tu - tipoUnidad)
                (when (and (esTipoUnidad ?u ?tu) (necesita ?tu ?tr)) 
                    (and
                        (decrease (AlmacenRecursos ?tr) (necesitaRecurso ?tu ?tr))     
                    )
                )
            )

            ; El numero de acciones incrementa
            (increase (NumeroAcciones) 1)
        )
    )

    ;; Recolectar: extrae cantidades limitadas de recursos
    ;; Parámetros: tipoRecurso, Localizacion
    (:action Recolectar
      :parameters (?tr - tipoRecurso ?l - Localizacion)
      :precondition
        (and
            ; Hay un recurso en la localizacion
            (en ?tr ?l)

            ; Hay un VCE en ?l
            (exists (?u - Unidad)
                (and
                    (not(libre ?u)) ; Si no está libre es que está extrayendo
                    (en ?u ?l) ; Si está en ?l está extrayendo ahi
                    (esTipoUnidad ?u VCE) ; Debe ser un VCE
                )
            )

            ; Los almacenes no estén llenos
            (<= (AlmacenRecursos Minerales) 50)
            (<= (AlmacenRecursos Gas) 60)
        )
    :effect
        (and
            ; Si se recolecta minerales, aumenta 5 por cada VCE en la localizacion
            (forall (?u - Unidad)
                (when (and (en Minerales ?l) (extrayendo ?u Minerales))
                    (and
                        ; Aumentar deposito de recurso
                        (increase (AlmacenRecursos Minerales) 5)
                    )
                )
            )

            ; Si ha recolectado más minerales del umbral, asigna el máximo permitido
            (when (>= (AlmacenRecursos Minerales) 50) 
                (and
                    (assign (AlmacenRecursos Minerales) 50)
                )
            )

            ; Si se recolecta gas, aumenta 10 por cada VCE en la localizacion
            (forall (?u - Unidad)
                ;(when (and(en ?u ?l) (not(libre ?u)) (esTipoUnidad ?u VCE) (en Gas ?l)) 
                (when (and (en Gas ?l) (extrayendo ?u Gas))
                    (and
                        ; Aumentar deposito de recurso
                        (increase (AlmacenRecursos Gas) 10)
                    )
                )
            )

            ; Si ha recolectado más gas del umbral, asigna el máximo permitido
            (when (>= (AlmacenRecursos Gas) 60) 
                (and
                    (assign (AlmacenRecursos Gas) 60)
                )
            )

            ; El numero de acciones incrementa
            (increase (NumeroAcciones) 1)
        )
    )

)