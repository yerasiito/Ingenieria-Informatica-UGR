(define (domain starcrfd1)
    (:requirements :strips :typing :fluents :negative-preconditions)
    (:types
        Unidad Edificio Localizacion tipoRecurso - object
    )
    (:constants 
        VCE - Unidad
        CentroDeMando Barracones - Edificio
        Minerales Gas - tipoRecurso
    )
    (:predicates
        ;; 1. Un edificio o Unidad esta en una Localizacion concreta
        (EntidadEn ?e - object ?l - Localizacion) ; QUE UNA ENTIDAD CUALQUIERA ESTÉ LOCALIZADA EN UN SITIO CONCRETO. UNIFICAR AMBOS PREDICADOS

        ;; 2. Existe un camino entre dos localizaciones
        ;; Conectar dos localizaciones para formar el grid
        (Conectado ?l1 - Localizacion ?l2 - Localizacion)
        
        ;; No se necesita para el ejercicio
        ;; (Construido ?e - Edificio)

        ;; 4. Asignar un nodo de un recurso concreto a una localizacion concreta
        (HayDepositoEn ?tR - tipoRecurso ?l - Localizacion) ; NO HACE FALTA INSTANCIAR NINGUN RECURSO
        
        ;; 5. VCE extrae un tipo de recurso
        (estaExtrayendo ?v - Unidad)
        (ExtrayendoRecurso ?r - tipoRecurso)

        ;; Tipo de Edificio
        (EsEdificio ?e ?tE - Edificio)
        ;; Tipo de Unidad
        (EsUnidad ?v ?tV - Unidad); EsUnidad VCE1 VCE
    )
    
    ;; Navegar: mueve una unidad entre dos localizaciones
    ;; Parámetros: Unidad, Localizacion Origen, Localizacion destino
    (:action Navegar
        :parameters (?v - Unidad ?lorig - Localizacion ?ldest - Localizacion)
        :precondition
            (and
                (EntidadEn ?v ?lorig)
                (Conectado ?lorig ?ldest)
            )
        :effect
            (and
                (EntidadEn ?v ?ldest)
                (not (EntidadEn ?v ?lorig))
            )
    )

    ;; Asignar: asigna un VCE a un nodo recurso
    ;; Parámetros: Unidad, Recurso, Tipo de Recurso, Localización del recurso
    (:action Asignar
        :parameters (?v - Unidad ?l - Localizacion ?tR - tipoRecurso)
        :precondition
            (and
                (HayDepositoEn ?tR ?l)
                (EntidadEn ?v ?l)
                (EsUnidad ?v VCE)
                (not (estaExtrayendo ?v))
            )
        :effect
            (and
                (estaExtrayendo ?v)
                (ExtrayendoRecurso ?tR)
            )
    )
)