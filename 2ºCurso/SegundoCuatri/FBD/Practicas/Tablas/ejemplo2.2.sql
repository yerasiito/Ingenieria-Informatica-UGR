INSERT INTO plantilla(dni,nombre,estadocivil,fechaalta)
    values('12345678', 'Pepe','soltero', SYSDATE);
INSERT INTO plantilla(dni,nombre,estadocivil,fechaalta)
    values('87654321', 'Juan','casado', SYSDATE);
INSERT INTO serjefe VALUES('87654321', '12345678');
INSERT INTO plantilla (dni, estadocivil) VALUES ('11223344', 'soltero');