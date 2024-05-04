CREATE OR REPLACE TRIGGER comprobarCuenta
BEFORE INSERT OR UPDATE OF identificador ON movimiento
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

CREATE OR REPLACE TRIGGER nuevoSaldo
AFTER INSERT OR DELETE OR UPDATE ON movimiento
FOR EACH ROW 
DECLARE
	cuantos INTEGER;
BEGIN
	IF INSERTING THEN
		UPDATE saldo SET saldo = saldo + :new.cantidad WHERE identificador = :new.identificador;
	ELSIF DELETING THEN
		UPDATE saldo SET saldo = saldo - :old.cantidad WHERE identificador = :old.identificador;
	ELSE 
		UPDATE saldo SET saldo = saldo - :old.cantidad WHERE identificador = :old.identificador;
		UPDATE saldo SET saldo = saldo + :new.cantidad WHERE identificador = :new.identificador;
	END IF;
END;
/
