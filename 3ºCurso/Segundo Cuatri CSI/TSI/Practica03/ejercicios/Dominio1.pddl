(define (domain starcrfd1)
    (:requirements :strips :typing :fluents :negative-preconditions)
    (:types
        ;; Los recursos no tienen objetos, solo tipos de recursos
        ;; Las unidades y los edificios pueden ser instanciados, por eso hay tipo y no tipos.
        Unidad tipoUnidad Edificio tipoEdificio Localizacion tipoRecurso - object
    )
    (:constants
        ; subclases de cada objeto
        VCE - tipoUnidad
        CentroDeMando Barracones - tipoEdificio
        Minerales Gas - tipoRecurso
    )
    (:predicates
        ;; Un edificio, Unidad o Recurso esta en una Localizacion concreta
        (en ?e - object ?l - Localizacion)

        ;; Existe un camino entre dos localizaciones
        ;; Conectar dos localizaciones para formar el grid
        (conectado ?l1 - Localizacion ?l2 - Localizacion)

        ;; VCE está extrayendo un tipo de recurso
        (estaExtrayendo ?v - Unidad)
        
        ;; El recurso está disponible (se asume ilimitados)
        (extrayendoRecurso ?r - tipoRecurso)

        ; Tipo de edificio. No se usa en este ejercicio
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
                ; Unidad esta en origen
                (en ?v ?lorig)
                ; Origen y destino estan conectados
                (conectado ?lorig ?ldest)
            )
        :effect
            (and
                ; Unidad se mueva a destino
                (en ?v ?ldest)
                ; Unidad ya no está en origen
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

                ; Solo extrae VCEs
                (esTipoUnidad ?v VCE)

                ; Que no esté ya extrayendo
                (not (estaExtrayendo ?v))
            )
        :effect
            (and
                ; Esa unidad extrae recurso y no hace otra cosa más
                (estaExtrayendo ?v)

                ; El recurso está disponible
                (extrayendoRecurso ?tR)
            )
    )
)