(define (domain starcrfd3)
    (:requirements :strips :typing :fluents :negative-preconditions :conditional-effects :disjunctive-preconditions :universal-preconditions)
    (:types
        Unidad tipoUnidad Edificio tipoEdificio Localizacion tipoRecurso - object
    )
    (:constants 
        VCE - tipoUnidad
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
        (extrayendoRecurso ?r - tipoRecurso)

        ; La unidad está asignada (a un recurso)
        (libre ?u)

        ; Tipo de edificio
        (esTipoEdificio ?e - edificio ?t - tipoEdificio)

        ; Tipo de Unidad
        (esTipoUnidad ?u - unidad ?t - tipoUnidad)

        ; Materiales que el edificio necesita
        (necesita ?te - tipoEdificio ?tr - tipoRecurso)

        ; Si un edificio está construido
        (construido ?e - Edificio)
    )
    
    ;; Navegar: mueve una unidad entre dos localizaciones
    ;; Parámetros: Unidad, Localizacion Origen, Localizacion destino
    (:action Navegar
        :parameters (?v - Unidad ?lorig - Localizacion ?ldest - Localizacion)
        :precondition
            (and
                ; La unidad está en la localizacion origen
                (en ?v ?lorig)

                ; La unidad está libre
                (libre ?v)

                ; Están conectadas las localizaciones
                (conectado ?lorig ?ldest)
            )
        :effect
            (and
                ; La unidad se mueva a localizacion de destino
                (en ?v ?ldest)

                ; La unidad ya no está en la localización de origen
                (not (en ?v ?lorig))
            )
    )

    ;; Asignar: asigna un VCE a un nodo recurso
    ;; Parámetros: Unidad, Recurso, Tipo de Recurso, Localización del recurso
    (:action Asignar
        :parameters (?u - Unidad ?l - Localizacion)
        :precondition
            (and
                ; La unidad está en la localización
                (en ?u ?l)

                ; La unidad está libre
                (libre ?u)

                ; O bien extrae Minerales o Gas
                (or
                    (exists (?e - edificio)
                        (and 
                            (esTipoEdificio ?e Extractor) ; Es un extractor
                            (en ?e ?l) ; El edificio está en la localización
                            (en Gas ?l) ; El gas está en la localización
                        )
                    )
                    (not (en Gas ?l))
                )
            )
        :effect
            (and
                ; La unidad extrae y no hace otra cosa más
                (not(libre ?u))
                
                ; Si hay un desposito de minerales en ?l, extrae minerales
                (when (and (en Minerales ?l))
                    (and
                        (ExtrayendoRecurso Minerales)
                    ) 
                )

                ; Si hay un desposito de gas en ?l, extrae gas
                (when (and (en Gas ?l))
                    (and
                        (ExtrayendoRecurso Gas)
                    )
                )
            )
    )
    

    (:action Construir
      :parameters (?u - Unidad ?e - Edificio ?l - Localizacion)
      :precondition
         (and
            ; Está en la localización
            (en ?u ?l)

            ; No está ya construido
            (not (construido ?e))

            ; La unidad está libre
            (libre ?u)

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
                        (extrayendoRecurso ?tr)
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
)