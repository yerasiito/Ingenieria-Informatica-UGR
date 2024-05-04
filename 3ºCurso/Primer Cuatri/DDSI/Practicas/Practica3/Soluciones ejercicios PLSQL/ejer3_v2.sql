CREATE OR REPLACE TRIGGER comprobarCuenta
BEFORE INSERT ON movimiento
FOR EACH ROW 
DECLARE
	cuantos INTEGER;
BEGIN
	SELECT COUNT(*) INTO cuantos FROM saldo WHERE identificador = :new.identificador;
	IF (cuantos = 0) THEN
		INSERT INTO saldo VALUES (:new.identificador, 0);
	END IF;
END;
/
