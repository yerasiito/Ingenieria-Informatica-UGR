(define (problem starcrfp7)
    (:domain starcrfd7)
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

        ;; Nodos de recursos en el mapa
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
        (necesita Marine Gas)
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

        ; Tipos de unidades
        (esTipoUnidad Marine1 Marine)
        (esTipoUnidad Marine2 Marine)
        (esTipoUnidad Soldado1 Soldado)

        ;; Llevara la cuenta de las acciones dadas (Al principio 0)
        (= (NumeroAcciones) 0)

        ;; Llevara la cuenta de los recursos disponibles (Al principio 0)
        (= (AlmacenRecursos Minerales) 0)
        (= (AlmacenRecursos Gas) 0)

        ;; Recursos requeridos por las Entidades
        ;; Barracones -> 40 Minerales & 10 Gas
        (= (necesitaRecurso Barracones Minerales) 40)
        (= (necesitaRecurso Barracones Gas) 10)

        ;; Extractor -> 10 Minerales & 0 Gas
        (= (necesitaRecurso Extractor Minerales) 10)
        (= (necesitaRecurso Extractor Gas) 0)

        ;; VCE -> 5 Minerales & 0 Gas
        (= (necesitaRecurso VCE Minerales) 5)
        (= (necesitaRecurso VCE Gas) 0)

        ;; Marine -> 10 Minerales & 15 Gas
        (= (necesitaRecurso Marine Minerales) 10)
        (= (necesitaRecurso Marine Gas) 15)

        ;; Soldado -> 30 Minerales & 40 Gas
        (= (necesitaRecurso Soldado Minerales) 30)
        (= (necesitaRecurso Soldado Gas) 40)
    )
    (:goal
        (and 
            ;; El objetivo es reclutar 3 unidades: 2 marines y un soldado con costes asociados
            ; (<= (NumeroAcciones) 58) ; optimo 
            
            (en Barracones1 loc3_3)  
            (en Marine1 loc3_1)
            (en Marine2 loc2_4)
            (en Soldado1 loc1_2)         
        )
    )
)
