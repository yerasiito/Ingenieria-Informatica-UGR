(define (domain starcrfd4)
    (:requirements :strips :typing :fluents :negative-preconditions :disjunctive-preconditions :conditional-effects)
    (:types
        Unidad Edificio Localizacion Recurso - object  
        
    )
    (:constants 
        VCE
        Marine
        Segador - Unidad
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
        (EdificioNecesita ?tE - Edificio ?tR - Recurso)
        ;; Una Unidad necesita también recursos para ser creada
        (UnidadNecesita ?tU - Unidad ?tR - Recurso)
        ;; Un Edificio Recluta una Unidad
        (EdificioRecluta ?tE - Edificio ?tU - Unidad)
        
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
                (EsUnidad ?v VCE) ;; Son los que pueden recolectar
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
        :parameters (?v - Unidad ?e - Edificio ?l - Localizacion ?tE - Edificio ?r - Recurso)
        :precondition
            (and
                (UnidadEn ?v ?l)
                (EsEdificio ?e ?tE)
                (not (EdificioEn ?e ?l))
                ;; Hasta aquí si o sí se ha cumplido
                (or
                    ;; O Bien es el Extractor lo que se quiere construir
                    (and
                        (EsEdificio ?e Extractor)
                        (exists (?r_gas - Recurso)
                            (and
                                (HayRecurso ?r_gas ?l)
                                (EsRecurso ?r Gas)
                            )
                        
                        )
                    )
                    (not (EsEdificio ?e Extractor))
                )
                ;; Para ver si se construye el extractor o no
                 
                ;; Ahora que se sabe qué edificio se construye se ve los materiales
                (or
                    ;; Y bien que:
                    (and
                        (EdificioNecesita ?tE Gas)
                        (>= (AlmacenRecursos Gas) 1)
                    )
                    (not (EdificioNecesita ?tE Gas))
                )
                ;; Y de aquí, lo mismo le hace falta otro o no (Mineral)
                ;; O bien que:
                (or
                    (and
                        (EdificioNecesita ?tE Minerales)
                        (>= (AlmacenRecursos Minerales) 1)
                    )
                    (not (EdificioNecesita ?tE Minerales))
                )
            )
            
        :effect
            (and
                (EdificioEn ?e ?l)
                (when (EdificioNecesita ?e Gas)
                   (decrease (AlmacenRecursos Gas) 1)
                )
                (when (EdificioNecesita ?e Minerales)
                   (decrease (AlmacenRecursos Minerales) 1)
                )

            )
    )

    (:action Reclutar
        :parameters (?v - Unidad ?e - Edificio ?l - Localizacion ?tU - Unidad ?tE - Edificio)
        :precondition
            (and
                (EsUnidad ?v ?tU)
                (EsEdificio ?e ?tE)
                (EdificioEn ?e ?l)
                (EdificioRecluta ?tE ?tU)
                
                (or
                    ;; O necesita Gas:
                    (and
                        (UnidadNecesita ?tU Gas)
                        (>= (AlmacenRecursos Gas) 1)
                    )
                    (not (UnidadNecesita ?tU Gas))
                )

                (or
                    ;; O Minerales
                    (and
                        (UnidadNecesita ?tU Minerales)
                        (>= (AlmacenRecursos Minerales) 1)
                    )
                    (not (UnidadNecesita ?tU Minerales))
                )
            )
            
        :effect
            (and
                (UnidadEn ?v ?l)
                (when (UnidadNecesita ?v Gas)
                   (decrease (AlmacenRecursos Gas) 1)
                )
                (when (UnidadNecesita ?v Minerales)
                   (decrease (AlmacenRecursos Minerales) 1)
                )

            )
    )
    
)