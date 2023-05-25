(define (domain starcrfd1)
    (:requirements :strips :typing :fluents :negative-preconditions)
    (:types
        Unidad Edificio Localizacion Recurso - object  
        
    )
    (:constants 
        VCE - Unidad
        CentroDeMando - Edificio
        Barracones - Edificio
        Minerales Gas - Recurso
    )
    (:predicates
        ;; Un edificio o Unidad esta en una Localizacion
        (EdificioEn ?e - Edificio ?l - Localizacion)
        (UnidadEn ?u - Unidad ?l - Localizacion)
        ;; Tipo de Edificio
        (EsEdificio ?e ?y - Edificio)
        ;; Tipo de Unidad
        (EsUnidad ?u ?y - Unidad)
        ;; Existe un camino entre dos localizaciones
        ;; Conectar dos localizaciones para formar el grid
        (Conectado ?l1 - Localizacion ?l2 - Localizacion)
        ;; Asignar un nodo de un recurso concreto a una localizacion
        (HayRecurso ?r - Recurso ?l - Localizacion)
        ;; Tipo de Recurso
        (EsRecurso ?r ?y - Recurso)
        ;; VCE extrae un recurso
        (Extrayendo ?v - Unidad)
        ;; Recurso necesario para construir un Edificio
        (EdificioNecesita ?e - Edificio ?r - Recurso)
        ;; VCE esta construyendo
        (Construyendo ?v - Unidad)
        
        
    )
    (:functions
        (AlmacenRecursos ?r - Recurso)
    )
    
    (:action Navegar
        :parameters (?v - Unidad ?tV - Unidad ?lactual - Localizacion ?ldest - Localizacion)
        :precondition
            (and
                (UnidadEn ?v ?lactual)
                (Conectado ?lactual ?ldest)
                (EsUnidad ?v ?tV)
            )
        :effect
            (and
                (UnidadEn ?v ?ldest)
                (not (UnidadEn ?v ?lactual))
            )
    )

    (:action Asignar
        :parameters (?v - Unidad ?r - Recurso ?tR - Recurso ?l - Localizacion)
        :precondition
            (and
                (HayRecurso ?r ?l)
                (EsRecurso ?r ?tR)
                (not (Extrayendo ?v))
                (UnidadEn ?v ?l)
            )
        :effect
            (and
                (Extrayendo ?v)
                (increase (AlmacenRecursos ?tR) 1)
            )
    )

    (:action Construir
        :parameters (?v - Unidad ?e - Edificio ?l - Localizacion ?tE - Edificio ?tR - Recurso)
        :precondition
            (and
                (EsEdificio ?e ?tE)
                (UnidadEn ?v ?l)
                (EdificioNecesita ?tE ?tR)
                (not (Construyendo ?v))
                (not (EdificioEn ?e ?l))
                (>= (AlmacenRecursos ?tR) 1)
            )
        :effect
            (and
                (EdificioEn ?e ?l)
                (decrease (AlmacenRecursos ?tR) 1)
            )
    )   
    
)