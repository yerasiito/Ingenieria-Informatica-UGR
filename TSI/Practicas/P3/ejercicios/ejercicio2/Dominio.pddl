(define (domain starcrfd1)
    (:requirements :strips :typing :fluents :negative-preconditions)
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
        (en ?e - object ?l - Localizacion) ; QUE UNA ENTIDAD CUALQUIERA ESTÉ LOCALIZADA EN UN SITIO CONCRETO. UNIFICAR AMBOS PREDICADOS

        ;; Existe un camino entre dos localizaciones
        ;; Conectar dos localizaciones para formar el grid
        (conectado ?l1 - Localizacion ?l2 - Localizacion)
        
        ;; No se necesita para el ejercicio
        ;; (Construido ?e - Edificio)

        ;; VCE extrae un tipo de recurso
        (estaExtrayendo ?v - Unidad)

        (extrayendoRecurso ?r - tipoRecurso)

        ; Tipo de edificio
        (esTipoEdificio ?e - edificio ?t - tipoEdificio)

        ; Tipo de Unidad
        (esTipoUnidad ?u - unidad ?t - tipoUnidad)

        ; Materiales que el edificio necesita
        (necesita ?te - tipoEdificio ?tr - tipoRecurso)
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
        :parameters (?u - Unidad ?l - Localizacion)
        :precondition
            (and
                ; La unidad está en la localización
                (en ?u ?l)

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
                (estaExtrayendo ?u)
                
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
      :parameters (?u - Unidad ?e - Edificio ?l - Localizacion ?tr - tipoRecurso)
      :precondition
         (and
            ; La unidad no está extrayendo
            (not (estaExtrayendo ?u))
            
            ; El edificio necesita recursos especificos de su tipo
            (exists (?te - tipoEdificio)
               (and 
                  (esTipoEdificio ?e ?te)
                  (necesita ?te ?tr)
                  (extrayendoRecurso ?tr)
               )
            )
            ; Está en la localización
            (en ?u ?l)
         )
      :effect
         (and
            ; Se construye el edificio
            (en ?e ?l)
         )
   )
)