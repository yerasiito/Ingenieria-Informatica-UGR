CREATE TABLE JUGADORES(
    codJ VARCHAR2(3) CONSTRAINT codigo_jugador_clave_primaria PRIMARY KEY,
    codE CONSTRAINT cod_equipo_no_nulo NOT NULL CONSTRAINT cod_equipo_clave_externa REFERENCES equipos(codE),
    nombreJ VARCHAR2(15) CONSTRAINT nombre_jugador_no_nulo NOT NULL
)
