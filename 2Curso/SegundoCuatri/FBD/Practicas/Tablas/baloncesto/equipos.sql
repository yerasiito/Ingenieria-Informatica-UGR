CREATE TABLE equipos(
    codE VARCHAR2(3) CONSTRAINT codEquipo_clave_primaria PRIMARY KEY,
    nombreE VARCHAR2(15) CONSTRAINT nombreE_no_nulo NOT NULL CONSTRAINT equipo_unico UNIQUE,
    localidad VARCHAR2(20) CONSTRAINT localidad_no_nula NOT NULL,
    entrenador VARCHAR2(15) CONSTRAINT entrenador_no_nulo NOT NULL,
    fecha_crea DATE CONSTRAINT fechaEquipo NOT NULL
)