(define (problem starcrfp3)
    (:domain starcrfd3)
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
        VCE1 VCE2 VCE3 - Unidad
        ; Edificios utilizados
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
        (en Minerales loc2_4)
        (en Minerales loc4_4)
        (en Gas loc1_5)

        ;; Extractor necesita -> Minerales
        (esTipoEdificio Extractor1 Extractor)
        (necesita Extractor Minerales)

        ;; Barracones necesita -> Minerales y Gas
        (esTipoEdificio Barracones1 Barracones)
        (necesita Barracones Minerales)
        (necesita Barracones Gas)

        ;; CentroDeMando en loc1_1
        (esTipoEdificio CentroDeMando1 CentroDeMando)
        (necesita CentroDeMando Minerales) ; necesita mineral
        (en CentroDeMando loc1_1) ; está construido en loc1_1
        (construido CentroDeMando1) ; redundancia, mejora el tiempo considerablemente
        
        ;; Unidad VCE en loc1_1
        ; Se establece el tipo de la Unidad
        (EsTipoUnidad VCE1 VCE) 
        (EsTipoUnidad VCE2 VCE)
        (EsTipoUnidad VCE3 VCE) 
        ; Se establece localizacion de la Unidad
        (en VCE1 loc1_1) 
        (en VCE2 loc1_1) 
        (en VCE3 loc1_1) 
        ;; Las unidades estan libres inicialmente
        (libre VCE1)
        (libre VCE2)
        (libre VCE3)
    )
    (:goal
        ;; El objetivo es construir el barracon en dicha localizacion
        (en Barracones1 loc3_4)
    )
)