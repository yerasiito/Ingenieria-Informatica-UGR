CREATE OR REPLACE TRIGGER nuevoSaldo
AFTER INSERT OR DELETE ON movimiento
FOR EACH ROW 
DECLARE
	cuantos INTEGER;
BEGIN
	IF INSERTING THEN
		SELECT COUNT(*) INTO cuantos FROM saldo WHERE identificador = :new.identificador;
		IF (cuantos = 0) THEN
			INSERT INTO saldo VALUES (:new.identificador, :new.cantidad);
		ELSE
			UPDATE saldo SET saldo = saldo + :new.cantidad WHERE identificador = :new.identificador;
		END IF;
	ELSE
		UPDATE saldo SET saldo = saldo - :old.cantidad WHERE identificador = :old.identificador;
	END IF;
END;
/
