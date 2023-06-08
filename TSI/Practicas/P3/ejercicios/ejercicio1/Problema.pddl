(define (problem starcrfp1)
    (:domain starcrfd1)
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
        CentroDeMando1 - Edificio
        VCE1 - Unidad
    )
    (:init
        ;; Mapa
        (conectado loc1_1 loc1_2)
        (conectado loc1_1 loc2_1)

        (conectado loc1_2 loc1_1)
        (conectado loc1_2 loc2_2)
        
        (conectado loc1_3 loc2_3)
        
        (conectado loc1_4 loc1_5)
        (conectado loc1_4 loc2_4)


        (conectado loc1_5 loc1_4)
        (conectado loc1_5 loc4_4)

        (conectado loc2_1 loc1_1)
        (conectado loc2_1 loc3_1)

        (conectado loc2_2 loc1_2)
        (conectado loc2_2 loc2_3)
        (conectado loc2_2 loc3_2)

        (conectado loc2_3 loc1_3)
        (conectado loc2_3 loc2_2)
        (conectado loc2_3 loc2_4)
        (conectado loc2_3 loc3_3)

        (conectado loc2_4 loc1_4)
        (conectado loc2_4 loc2_3)

        (conectado loc3_1 loc2_1)
        (conectado loc3_1 loc3_2)

        (conectado loc3_2 loc2_2)
        (conectado loc3_2 loc3_1)
        (conectado loc3_2 loc4_2)

        (conectado loc3_3 loc2_3)

        (conectado loc3_4 loc4_4)

        (conectado loc4_2 loc3_2)
        (conectado loc4_2 loc4_3)

        (conectado loc4_3 loc4_4)
        (conectado loc4_3 loc4_2)

        (conectado loc4_4 loc4_3)
        (conectado loc4_4 loc1_5)
        (conectado loc4_4 loc3_4)


        ;; CentroDeMando en loc1_1
        (esTipoEdificio CentroDeMando1 CentroDeMando) ;; Se establece el tipo de edificio
        (en CentroDeMando1 loc1_1)
        ;; Unidad VCE en loc1_1
        (esTipoUnidad VCE1 VCE) ;; Se establece el tipo de la Unidad
        (en VCE1 loc1_1)

        ;; Nodos de mineral en el mapa
        (en Minerales loc2_4)
        (en Minerales loc4_4)
    )
    (:goal
        (extrayendoRecurso Minerales)
    )
)