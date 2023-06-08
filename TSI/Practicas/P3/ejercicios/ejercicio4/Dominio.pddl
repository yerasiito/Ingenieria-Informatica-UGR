(define (domain starcrfd3)
    (:requirements :strips :typing :fluents :negative-preconditions :conditional-effects :disjunctive-preconditions :universal-preconditions :equality)
    (:types
        Unidad tipoUnidad Edificio tipoEdificio Localizacion tipoRecurso - object
    )
    (:constants 
        VCE Marine Soldado - tipoUnidad
        CentroDeMando Barracones Extractor - tipoEdificio
        Minerales Gas - tipoRecurso
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
                ; Si hay un desposito de minerales en ?l, extrae minerales
                (when (and (en Minerales ?l))
                    (and
                        (generando Minerales)

                    ) 
                )

                ; Si hay un desposito de gas en ?l, extrae gas
                (when (and (en Gas ?l))
                    (and
                        (generando Gas)
                    )
                )
            )
    )
    

    (:action Construir
      :parameters (?u - Unidad ?e - Edificio ?l - Localizacion)
      :precondition
        (and
            ; La unidad está libre
            (libre ?u)

            ; Está en la localización
            (en ?u ?l)

            ; No está ya construido
            (not (construido ?e))

            ; El edificio necesita recursos especificos de su tipo
            (forall (?tr - tipoRecurso)
                    (imply
                        ; Si el tipo de edificio necesita el recurso
                        (exists (?te - tipoEdificio)
                            (and 
                                (esTipoEdificio ?e ?te)
                                (necesita ?te ?tr)
                            )
                        )
                        ; Entonces tiene que estar disponible dicho recurso
                        (generando ?tr)
                    )
            )
            
        )
      :effect
        (and
            ; Se construye dicho edificio
            (construido ?e)
            ; Se construye el edificio
            (en ?e ?l)
        )
    )
    
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
            (forall (?tr - tipoRecurso)
                    (imply
                        ; Si el tipo de unidad necesita el recurso
                        (exists (?tu - tipoUnidad)
                            (and 
                                (esTipoUnidad ?u ?tu)
                                (necesita ?tu ?tr)
                            )
                        )
                        ; Entonces tiene que estar disponible dicho recurso
                        (generando ?tr)
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
            (en ?u ?l)
            (Reclutada ?u)
        )
    )
)