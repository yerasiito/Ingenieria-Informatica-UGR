(define (problem starcrfp2)
    (:domain starcrfd2)
    (:objects
        ; localizaciones disponibles
        loc1_1
        loc1_2
        loc1_3
        loc1_4
        loc1_5
        loc2_1
        loc2_2
        loc2_3
        loc2_4
        loc3_1
        loc3_2
        loc3_3
        loc3_4
        loc4_2
        loc4_3
        loc4_4 - Localizacion
        ; Unidades VCE
        VCE1 VCE2 - Unidad
        ; Centro de mando donde se generan unidades
        CentroDeMando1 - Edificio
        ; Extractor de gas
        Extractor1 - Edificio
    )
    (:init
        ;; Mapa
        (Conectado loc1_1 loc1_2)
        (Conectado loc1_1 loc2_1)

        (Conectado loc1_2 loc1_1)
        (Conectado loc1_2 loc2_2)
        
        (Conectado loc1_3 loc2_3)
        
        (Conectado loc1_4 loc1_5)
        (Conectado loc1_4 loc2_4)


        (Conectado loc1_5 loc1_4)
        (Conectado loc1_5 loc4_4)

        (Conectado loc2_1 loc1_1)
        (Conectado loc2_1 loc3_1)

        (Conectado loc2_2 loc1_2)
        (Conectado loc2_2 loc2_3)
        (Conectado loc2_2 loc3_2)

        (Conectado loc2_3 loc1_3)
        (Conectado loc2_3 loc2_2)
        (Conectado loc2_3 loc2_4)
        (Conectado loc2_3 loc3_3)

        (Conectado loc2_4 loc1_4)
        (Conectado loc2_4 loc2_3)

        (Conectado loc3_1 loc2_1)
        (Conectado loc3_1 loc3_2)

        (Conectado loc3_2 loc2_2)
        (Conectado loc3_2 loc3_1)
        (Conectado loc3_2 loc4_2)

        (Conectado loc3_3 loc2_3)

        (Conectado loc3_4 loc4_4)

        (Conectado loc4_2 loc3_2)
        (Conectado loc4_2 loc4_3)

        (Conectado loc4_3 loc4_4)
        (Conectado loc4_3 loc4_2)

        (Conectado loc4_4 loc4_3)
        (Conectado loc4_4 loc1_5)
        (Conectado loc4_4 loc3_4)

        ;; Nodos de mineral en el mapa
        (en Minerales loc2_4)
        (en Minerales loc4_4)
        (en Gas loc1_5)

        ;; Extractor necesita -> Minerales
        (esTipoEdificio Extractor1 Extractor)
        (necesita Extractor Minerales)

        ;; CentroDeMando en loc1_1
        (esTipoEdificio CentroDeMando1 CentroDeMando)
        (en CentroDeMando1 loc1_1)
        
        ;; Unidad VCE en loc1_1
        (esTipoUnidad VCE1 VCE) ;; Se establece el tipo de la Unidad
        (esTipoUnidad VCE2 VCE) ;; Se establece el tipo de la Unidad
        (en VCE1 loc1_1) ;; Se establece localizacion de la Unidad
        (en VCE2 loc1_1) ;; Se establece localizacion de la Unidad
    )
    (:goal
        ;; El objetivo es extraer gas
        (ExtrayendoRecurso Gas)
    )
)