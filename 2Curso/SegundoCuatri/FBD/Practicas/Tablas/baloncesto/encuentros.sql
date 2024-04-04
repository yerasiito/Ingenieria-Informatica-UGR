CREATE TABLE encuentros(
    ELocal CONSTRAINT ELocEnc_clave_externa_equipos REFERENCES equipos(codE),
    EVisitante CONSTRAINT EVisEnc_clave_externa_equipos REFERENCES equipos(codE),
    fecha DATE,
    PLocal INT DEFAULT 0 CONSTRAINT PLocal_valor_positivo CHECK (PLocal > 0),
    PVisitante INT DEFAULT 0 CONSTRAINT PVisitante_valor_positivo CHECK (PVisitante > 0),
        CONSTRAINT Enc_clave_primaria PRIMARY KEY(ELocal, EVisitante)
    

)
