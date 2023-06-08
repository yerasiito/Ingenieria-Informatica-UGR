(define (domain starcrfd1)
    (:requirements :strips :typing :fluents :negative-preconditions)
    (:types
        Unidad tipoUnidad Edificio tipoEdificio Localizacion tipoRecurso - object
    )
    (:constants 
        VCE - tipoUnidad
        CentroDeMando Barracones - tipoEdificio
        Minerales Gas - tipoRecurso
    )
    (:predicates
        ;; Un edificio, Unidad o Recurso esta en una Localizacion concreta
        (en ?e - object ?l - Localizacion) ; QUE UNA ENTIDAD CUALQUIERA ESTÉ LOCALIZADA EN UN SITIO CONCRETO. UNIFICAR AMBOS PREDICADOS

        ;; Existe un camino entre dos localizaciones
        ;; Conectar dos localizaciones para formar el grid
        (conectado ?l1 - Localizacion ?l2 - Localizacion)

        ;; VCE extrae un tipo de recurso
        (estaExtrayendo ?v - Unidad)
        (extrayendoRecurso ?r - tipoRecurso)

        ; Tipo de edificio. No se usa
        (esTipoEdificio ?e - edificio ?t - tipoEdificio)

        ; Tipo de Unidad
        (esTipoUnidad ?u - unidad ?t - tipoUnidad)
    )
    
    ;; Navegar: mueve una unidad entre dos localizaciones
    ;; Parámetros: Unidad, Localizacion Origen, Localizacion destino
    (:action Navegar
        :parameters (?v - Unidad ?lorig - Localizacion ?ldest - Localizacion)
        :precondition
            (and
                (en ?v ?lorig)
                (conectado ?lorig ?ldest)
            )
        :effect
            (and
                (en ?v ?ldest)
                (not (en ?v ?lorig))
            )
    )

    ;; Asignar: asigna un VCE a un nodo recurso
    ;; Parámetros: Unidad, Recurso, Tipo de Recurso, Localización del recurso
    (:action Asignar
        :parameters (?v - Unidad ?l - Localizacion ?tR - tipoRecurso)
        :precondition
            (and
                
                ; La unidad está en la localizacion
                (en ?v ?l)
                ; El recurso está en la localizacion
                (en ?tr ?l)

                ; Solo lo extrae VCEs
                (esTipoUnidad ?v VCE)

                ; Que no esté ya extrayendo
                (not (estaExtrayendo ?v))
            )
        :effect
            (and
                ; Esa unidad extrae recurso
                (estaExtrayendo ?v)

                ; El recurso está disponible
                (extrayendoRecurso ?tR)
            )
    )
)