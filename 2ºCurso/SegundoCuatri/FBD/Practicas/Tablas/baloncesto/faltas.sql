CREATE TABLE FALTAS(
    codJ CONSTRAINT codJ_clave_externa REFERENCES JUGADORES(codJ),
    ELocal CONSTRAINT ELocal_clave_externa REFERENCES EQUIPOS(codE),
    EVisitante CONSTRAINT EVisitante_clave_externa REFERENCES EQUIPOS(codE),
    num INT DEFAULT 0 CONSTRAINT numF_entre_0_5 CHECK (0<=num AND num<=5),
    CONSTRAINT claves_primarias PRIMARY KEY (codJ,ELocal, EVisitante)   
)
