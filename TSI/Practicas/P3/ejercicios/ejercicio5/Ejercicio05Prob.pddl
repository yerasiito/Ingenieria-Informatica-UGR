(define (problem starcrfp5)
    (:domain starcrfd5)
    (:objects
        loc1_1
        loc1_2
        loc1_3
        loc1_4
        loc1_5
        loc2_1
        loc2_2
        loc2_3
        loc2_4
        loc2_5
        loc3_1
        loc3_2
        loc3_3
        loc3_4
        loc3_5
        loc4_1
        loc4_2
        loc4_3
        loc4_4
        loc4_5
        loc5_1
        loc5_2
        loc5_3
        loc5_4
        loc5_5 - Localizacion
        mando
        barracon
        extractr
        bahia - Edificio
        trabajador
        trabajador2
        trabajador3
        trabajador4
        recluta1
        recluta2
        recluta3 - Unidad
        gas1
        gas2
        minerales1
        minerales2
        minerales3 - Recurso
        impulso - Investigacion

    )
    (:init
        ;; Tablero 5x5
        (Conectado loc1_1 loc2_1)
        (Conectado loc1_1 loc1_2)
        (Conectado loc1_2 loc2_2)
        (Conectado loc1_2 loc1_3)
        (Conectado loc1_2 loc1_1)
        (Conectado loc1_3 loc2_3)
        (Conectado loc1_3 loc1_4)
        (Conectado loc1_3 loc1_2)
        (Conectado loc1_4 loc2_4)
        (Conectado loc1_4 loc1_5)
        (Conectado loc1_4 loc1_3)
        (Conectado loc1_5 loc2_5)
        (Conectado loc1_5 loc1_4)
        (Conectado loc2_1 loc1_1)
        (Conectado loc2_1 loc3_1)
        (Conectado loc2_1 loc2_2)
        (Conectado loc2_2 loc1_2)
        (Conectado loc2_2 loc3_2)
        (Conectado loc2_2 loc2_3)
        (Conectado loc2_2 loc2_1)
        (Conectado loc2_3 loc1_3)
        (Conectado loc2_3 loc3_3)
        (Conectado loc2_3 loc2_4)
        (Conectado loc2_3 loc2_2)
        (Conectado loc2_4 loc1_4)
        (Conectado loc2_4 loc3_4)
        (Conectado loc2_4 loc2_5)
        (Conectado loc2_4 loc2_3)
        (Conectado loc2_5 loc1_5)
        (Conectado loc2_5 loc3_5)
        (Conectado loc2_5 loc2_4)
        (Conectado loc3_1 loc2_1)
        (Conectado loc3_1 loc4_1)
        (Conectado loc3_1 loc3_2)
        (Conectado loc3_2 loc2_2)
        (Conectado loc3_2 loc4_2)
        (Conectado loc3_2 loc3_3)
        (Conectado loc3_2 loc3_1)
        (Conectado loc3_3 loc2_3)
        (Conectado loc3_3 loc4_3)
        (Conectado loc3_3 loc3_4)
        (Conectado loc3_3 loc3_2)
        (Conectado loc3_4 loc2_4)
        (Conectado loc3_4 loc4_4)
        (Conectado loc3_4 loc3_5)
        (Conectado loc3_4 loc3_3)
        (Conectado loc3_5 loc2_5)
        (Conectado loc3_5 loc4_5)
        (Conectado loc3_5 loc3_4)
        (Conectado loc4_1 loc3_1)
        (Conectado loc4_1 loc5_1)
        (Conectado loc4_1 loc4_2)
        (Conectado loc4_2 loc3_2)
        (Conectado loc4_2 loc5_2)
        (Conectado loc4_2 loc4_3)
        (Conectado loc4_2 loc4_1)
        (Conectado loc4_3 loc3_3)
        (Conectado loc4_3 loc5_3)
        (Conectado loc4_3 loc4_4)
        (Conectado loc4_3 loc4_2)
        (Conectado loc4_4 loc3_4)
        (Conectado loc4_4 loc5_4)
        (Conectado loc4_4 loc4_5)
        (Conectado loc4_4 loc4_3)
        (Conectado loc4_5 loc3_5)
        (Conectado loc4_5 loc5_5)
        (Conectado loc4_5 loc4_4)
        (Conectado loc5_1 loc4_1)
        (Conectado loc5_1 loc5_2)
        (Conectado loc5_2 loc4_2)
        (Conectado loc5_2 loc5_3)
        (Conectado loc5_2 loc5_1)
        (Conectado loc5_3 loc4_3)
        (Conectado loc5_3 loc5_4)
        (Conectado loc5_3 loc5_2)
        (Conectado loc5_4 loc4_4)
        (Conectado loc5_4 loc5_5)
        (Conectado loc5_4 loc5_3)
        (Conectado loc5_5 loc4_5)
        (Conectado loc5_5 loc5_4)
        ;; CentroDeMando en alguna localizacion
        (EsEdificio mando CentroDeMando)
        (EdificioEn mando loc3_4)
        (EsEdificio barracon Barracones)
        (EsEdificio extractr Extractor)
        (EsEdificio bahia BahiaDeIngenieria)
        ;; Una Unidad VCE en el mapa
        (EsUnidad trabajador VCE) ;; Se establece el tipo de la Unidad
        (UnidadEn trabajador loc2_3)
        ;; Las Unidades que se crearan se deben inicializar
        (EsUnidad recluta1 Marine)
        (EsUnidad recluta2 Marine)
        (EsUnidad recluta3 Segador)
        ;; Serán necesarios más trabajadores
        (EsUnidad trabajador2 VCE)
        (EsUnidad trabajador3 VCE)
        (EsUnidad trabajador4 VCE)
        ;; Tres nodos de mineral en el mapa
        (EsRecurso minerales1 Minerales) ;; Se indica el tipo del Recurso
        (HayRecurso minerales1 loc4_3)
        (EsRecurso minerales2 Minerales)
        (HayRecurso minerales2 loc5_3)
        (EsRecurso minerales3 Minerales)
        (HayRecurso minerales3 loc1_3)
        ;; Dos nodos de gas en el mapa
        (EsRecurso gas1 Gas)
        (HayRecurso gas1 loc2_2)
        (EsRecurso gas2 Gas)
        (HayRecurso gas2 loc3_3)
        ;; Centro de Mando necesita -> Minerales & Gas
        (EdificioNecesita CentroDeMando Minerales)
        (EdificioNecesita CentroDeMando Gas)
        ;; Barracones necesita -> Gas
        (EdificioNecesita Barracones Minerales)
        ;; Centro de Mando necesita -> Minerales
        (EdificioNecesita Extractor Minerales)
        ;; Bahia de Ingenieria necesita -> Minerales & Gas
        (EdificioNecesita BahiaDeIngenieria Minerales)
        (EdificioNecesita BahiaDeIngenieria Gas)
        ;; Una Unidad VCE necesita -> Minerales
        (UnidadNecesita VCE Minerales)
        ;; Una Unidad Marine necesita -> Minerales
        (UnidadNecesita Marine Minerales)
        ;; Una Unidad Segador requiere -> Minerales & Gas
        (UnidadNecesita Segador Minerales)
        (UnidadNecesita Segador Gas)
        ;; Un CentroDeMando recluta -> VCE
        (EdificioRecluta CentroDeMando VCE)
        ;; Un Barracones recluta -> Marine & Segador
        (EdificioRecluta Barracones Marine)
        (EdificioRecluta Barracones Segador)
        ;; Tipo de Investigacion
        (EsInvestigacion impulso ImpulsorSegador)
        ;; Llevara la cuenta de los materiales disponibles (Al principio 0)
        (= (AlmacenRecursos Minerales) 0)
        (= (AlmacenRecursos Gas) 0)

    )
    (:goal
        (and
            (UnidadEn recluta1 loc2_5)
            (UnidadEn recluta2 loc4_2)
            (UnidadEn recluta3 loc4_2)
        )
        

    )
)