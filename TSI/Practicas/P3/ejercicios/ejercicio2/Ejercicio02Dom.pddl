(define (domain starcrfd2)
    (:requirements :strips :typing :fluents :negative-preconditions :disjunctive-preconditions)
    (:types
        Unidad Edificio Localizacion Recurso - object  
        
    )
    (:constants 
        VCE - Unidad
        CentroDeMando
        Extractor
        Barracones - Edificio
        Minerales
        Gas - Recurso
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
        :parameters (?v - Unidad ?r - Recurso ?tR - Recurso ?l - Localizacion ?e - Edificio)
        :precondition
            (and
                (not (Extrayendo ?v))
                (UnidadEn ?v ?l)
                (HayRecurso ?r ?l)
                (EsRecurso ?r ?tR)
                (or
                    (and
                        (EsRecurso ?r Gas)
                        (EdificioEn ?e ?l)
                        (EsEdificio ?e Extractor)
                    )
                    (not (EsRecurso ?r Gas))
                )
            )
            
        :effect
            (and
                (Extrayendo ?v)
                (increase (AlmacenRecursos ?tR) 1)
            )
    )

    (:action Construir
        :parameters (?v - Unidad ?e - Edificio ?l - Localizacion ?tE - Edificio ?r - Recurso ?tR - Recurso)
        :precondition
            (and
                (UnidadEn ?v ?l)
                (EsEdificio ?e ?tE)
                (EdificioNecesita ?tE ?tR)
                (not (EdificioEn ?e ?l))
                (>= (AlmacenRecursos ?tR) 1)
                (or
                    (and
                        (EsEdificio ?e Extractor)
                        (HayRecurso ?r ?l)                  
                        (EsRecurso ?r Gas)
                    )
                    (not (EsEdificio ?e Extractor))
                )
            )
        :effect
            (and
                (EdificioEn ?e ?l)
                (decrease (AlmacenRecursos ?tR) 1)
            )
    )
    
)