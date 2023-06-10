(define (problem starcrfp5)
    (:domain starcrfd5)
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
        ; Unidades Marine
        Marine1 Marine2 - Unidad
        ; Unidades Soldado
        Soldado1 - Unidad
        ; Infraestructura
        CentroDeMando1 Extractor1 Barracones1 Laboratorio1 - Edificio
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

        ;; Nodos de recursos en el mapa
        (en Minerales loc2_2)
        (en Minerales loc4_4)
        (en Gas loc1_5)
        (en Especia loc1_3) ; Nuevo recurso

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

        ;; Laboratorio en loc1_2
        (esTipoEdificio Laboratorio1 Laboratorio)
        (necesita Laboratorio Minerales)
        (necesita Laboratorio Gas)

        ;; Investigacion
        (necesita spartan Minerales)
        (necesita spartan Gas)
        (necesita spartan Especia)
        
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

        ; Se establece el tipo de la Unidad
        (esTipoUnidad VCE1 VCE) 
        (esTipoUnidad VCE2 VCE)
        (esTipoUnidad VCE3 VCE)

        (en VCE1 loc1_1) ;; Se establece localizacion de la Unidad

        ; Las unidades están dispononibles inicialmente
        (libre VCE1)
        (libre VCE2)
        (libre VCE3)
        (libre Marine1)
        (libre Marine2)
        (libre Soldado1)

        ; Especifica de que tipo son las unidades
        (esTipoUnidad Marine1 Marine)
        (esTipoUnidad Marine2 Marine)
        (esTipoUnidad Soldado1 Soldado)
    )
    (:goal
        (and
            ;; El objetivo es reclutar 3 unidad: 2 marines y 1 soldado
            ;; El soldado debe investigar previamente spartan
            ;; Para investigar se construye el laboratorio en loc1_4
            (en Barracones1 loc1_4)
            (en Laboratorio1 loc1_2)  
            (en Marine1 loc1_4)
            (en Marine2 loc1_4)
            (en Soldado1 loc1_4)          
        )
    )
)