(define (domain starcrfd6)
    (:requirements :strips :typing :fluents :negative-preconditions :disjunctive-preconditions :conditional-effects)
    (:types
        Unidad Edificio Localizacion Recurso Investigacion Accion - object  
    )
    (:constants 
        VCE
        Marine
        Segador - Unidad
        CentroDeMando
        Extractor
        Barracones
        BahiaDeIngenieria
        Deposito - Edificio
        Minerales
        Gas - Recurso
        ImpulsorSegador - Investigacion
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
        (Extrayendo ?v - Unidad ?tR - Recurso)
        ;; Recurso necesario para construir un Edificio
        (EdificioNecesita ?tE - Edificio ?tR - Recurso)
        ;; Una Unidad necesita también recursos para ser creada
        (UnidadNecesita ?tU - Unidad ?tR - Recurso)
        ;; Un Edificio Recluta una Unidad
        (EdificioRecluta ?tE - Edificio ?tU - Unidad)
        ;; Tipo de la Investigacion
        (EsInvestigacion ?i ?y - Investigacion)
        (Investigada ?i - Investigacion)
        (InvestigacionNecesita ?tI - Investigacion ?tR - Recurso)
        
    )
    (:functions
        (AlmacenRecursos ?r - Recurso)
        (CapacidadRecursos)
        (InvestigacionNecesitaRecursos ?tI - Investigacion ?r - Recurso)
        (UnidadNecesitaRecursos ?tU - Unidad ?r - Recurso)
        (EdificioNecesitaRecursos ?tE - Edificio ?r - Recurso)
        (RecolectaRecurso)
        (NumeroVCE ?tR - Recurso) ;; Un trabajador en un determinado recurso
        (AumentoCapacidad)
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

    (:action Asignar ;; Asignar ya no recolecta solo pone un VCE a extraer recursos
        :parameters (?v - Unidad ?r - Recurso ?tR - Recurso ?l - Localizacion ?e - Edificio)
        :precondition
            (and
                (EsUnidad ?v VCE) ;; Son los que pueden recolectar
                (not (Extrayendo ?v ?tR))
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
                (Extrayendo ?v ?tR)
                (increase (NumeroVCE ?tR) 1)
            )
    )

    (:action Construir
        :parameters (?v - Unidad ?e - Edificio ?l - Localizacion ?tE - Edificio ?r - Recurso)
        :precondition
            (and
                (UnidadEn ?v ?l)
                (EsUnidad ?v VCE)
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
                        (>= (AlmacenRecursos Gas) (EdificioNecesitaRecursos ?tE Gas))
                    )
                    (not (EdificioNecesita ?tE Gas))
                )
                ;; Y de aquí, lo mismo le hace falta otro o no (Mineral)
                ;; O bien que:
                (or
                    (and
                        (EdificioNecesita ?tE Minerales)
                        (>= (AlmacenRecursos Minerales) (EdificioNecesitaRecursos ?tE Minerales))
                    )
                    (not (EdificioNecesita ?tE Minerales))
                )
            )
            
        :effect
            (and
                (EdificioEn ?e ?l)
                (when (EdificioNecesita ?tE Gas)
                   (decrease (AlmacenRecursos Gas) (EdificioNecesitaRecursos ?tE Gas))
                )
                (when (EdificioNecesita ?tE Minerales)
                   (decrease (AlmacenRecursos Minerales) (EdificioNecesitaRecursos ?tE Minerales))
                )
                (when (EsEdificio ?e Deposito)
                   (increase (CapacidadRecursos) (AumentoCapacidad))
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
                    ;; Si es un Segador, primero necesita ImpulsorSegador
                    (and
                        (EsUnidad ?v Segador)
                        (Investigada ImpulsorSegador)
                    )
                    (not (EsUnidad ?v Segador))
                )
                (or
                    ;; O necesita Gas:
                    (and
                        (UnidadNecesita ?tU Gas)
                        (>= (AlmacenRecursos Gas) (UnidadNecesitaRecursos ?tU Gas))
                    )
                    (not (UnidadNecesita ?tU Gas))
                )

                (or
                    ;; O Minerales
                    (and
                        (UnidadNecesita ?tU Minerales)
                        (>= (AlmacenRecursos Minerales) (UnidadNecesitaRecursos ?tU Minerales))
                    )
                    (not (UnidadNecesita ?tU Minerales))
                )
            )
            
        :effect
            (and
                (UnidadEn ?v ?l)
                (when (UnidadNecesita ?v Gas)
                   (decrease (AlmacenRecursos Gas) (UnidadNecesitaRecursos ?tU Gas))
                )
                (when (UnidadNecesita ?v Minerales)
                   (decrease (AlmacenRecursos Minerales) (UnidadNecesitaRecursos ?tU Minerales))
                )                

            )
    )

    (:action Investigar
        :parameters (?i - Investigacion ?e - Edificio ?loc - Localizacion ?tI - Investigacion)
        :precondition
            (and
                (EsEdificio ?e BahiaDeIngenieria)
                (EdificioEn ?e ?loc)
                (not (Investigada ?i))

                (or
                    ;; Y bien que necesite GAS:
                    (and
                        (InvestigacionNecesita ?tI Gas)
                        (>= (AlmacenRecursos Gas) (InvestigacionNecesitaRecursos ?tI Gas))
                    )
                    (not (InvestigacionNecesita ?tI Gas))
                )
                ;; Y de aquí, lo mismo le hace falta otro o no (MINERAL)
                (or
                    (and
                        (InvestigacionNecesita ?tI Minerales)
                        (>= (AlmacenRecursos Minerales) (InvestigacionNecesitaRecursos ?tI Minerales))
                    )
                    (not (InvestigacionNecesita ?tI Minerales))
                )
            )
        :effect
            (and
                (Investigada ?i)
                (when (InvestigacionNecesita ?i Gas)
                   (decrease (AlmacenRecursos Gas) (InvestigacionNecesitaRecursos ?tI Gas))
                )
                (when (InvestigacionNecesita ?i Minerales)
                   (decrease (AlmacenRecursos Minerales) (InvestigacionNecesitaRecursos ?tI Minerales))
                )
            )
    )

    (:action Recolectar
        :parameters (?v - Unidad ?r - Recurso ?tR - Recurso)
        :precondition
            (and
                (EsUnidad ?v VCE) ;; Son los que pueden recolectar
                (Extrayendo ?v ?tR)
                (or
                    (and
                        (EsRecurso ?r Minerales)
                        (>= (CapacidadRecursos) (+ (AlmacenRecursos Minerales) (* (NumeroVCE ?tR) (RecolectaRecurso))))
                    )
                    (not (EsRecurso ?r Minerales))
                )
                (or
                    (and
                        (EsRecurso ?r Gas)
                        (>= (CapacidadRecursos) (+ (AlmacenRecursos Gas) (* (NumeroVCE ?tR) (RecolectaRecurso))))
                    )
                    (not (EsRecurso ?r Gas))
                )
            )
            
        :effect
            (and
                (increase (AlmacenRecursos ?tR) 
                    (* (NumeroVCE ?tR) (RecolectaRecurso))
                )
            )
    )

    (:action Desacoplar
        :parameters (?v - Unidad ?r - Recurso ?tR - Recurso)
        :precondition
            (and
                (Extrayendo ?v ?tR)
                (EsRecurso ?r ?tR)
            )
            
        :effect
            (and
                (not (Extrayendo ?v ?tR))
                (decrease (NumeroVCE ?tR) 1)
            )
    )
    
)