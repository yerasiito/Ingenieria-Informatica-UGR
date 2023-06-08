(define (problem starcrfp1)
    (:domain starcrfd3)
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
        loc3_1
        loc3_2
        loc3_3
        loc3_4
        loc4_2
        loc4_3
        loc4_4 - Localizacion
        VCE1 VCE2 VCE3 - Unidad
        Marine1 Marine2 - Unidad
        Soldado1 - Unidad
        CentroDeMando1 Extractor1 Barracones1 - Edificio
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
        (en Minerales loc2_2)
        (en Minerales loc4_4)
        (en Gas loc1_5)

        ;; Extractor -> Minerales
        (esTipoEdificio Extractor1 Extractor)
        (necesita Extractor Minerales)

        ;; Barracones -> Minerales y Gas
        (esTipoEdificio Barracones1 Barracones)
        (necesita Barracones Minerales)
        (necesita Barracones Gas)

        ;; CentroDeMando en loc1_1
        (esTipoEdificio CentroDeMando1 CentroDeMando)
        (necesita CentroDeMando Minerales)
        (en CentroDeMando1 loc1_1)
        (construido CentroDeMando1)
        
        ;; Unidades
        ; Recursos necesarios
        (necesita VCE Minerales)
        (necesita Marine Minerales)
        (necesita Soldado Minerales)
        (necesita Soldado Gas)
        
        ; Donde se reclutan
        (recluta VCE CentroDeMando)
        (recluta Marine Barracones)
        (recluta Soldado Barracones)

        (esTipoUnidad VCE1 VCE) ;; Se establece el tipo de la Unidad
        (esTipoUnidad VCE2 VCE) ;; Se establece el tipo de la Unidad
        (esTipoUnidad VCE3 VCE) ;; Se establece el tipo de la Unidad
        (en VCE1 loc1_1) ;; Se establece localizacion de la Unidad
        (libre VCE1)
        (libre VCE2)
        (libre VCE3)
        (libre Marine1)
        (libre Marine2)
        (libre Soldado1)

        (esTipoUnidad Marine1 Marine)
        (esTipoUnidad Marine2 Marine)
        (esTipoUnidad Soldado1 Soldado)
    )
    (:goal
        (and
            (en Barracones1 loc3_3)  
            (en Marine1 loc3_1)
            (en Marine2 loc2_4)
            (en Soldado1 loc1_2)          
        )
    )
)