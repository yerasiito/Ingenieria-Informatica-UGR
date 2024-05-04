CREATE OR REPLACE TRIGGER nuevoSaldo
AFTER INSERT OR DELETE OR UPDATE ON movimiento
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
	ELSIF DELETING THEN
		SELECT COUNT(*) INTO cuantos FROM saldo WHERE identificador = :old.identificador;
		IF (cuantos = 0) THEN
			DELETE FROM saldo WHERE identificador = :old.identificador;
		ELSE
			UPDATE saldo SET saldo = saldo - :old.cantidad WHERE identificador = :old.identificador;
		END IF;
	ELSE 
		SELECT COUNT(*) INTO cuantos FROM saldo WHERE identificador = :new.identificador;
		IF (cuantos = 0) THEN
			DELETE FROM saldo WHERE identificador = :old.identificador;
		ELSE
			UPDATE saldo SET saldo = saldo - :old.cantidad WHERE identificador = :old.identificador;
		END IF;
		SELECT COUNT(*) INTO cuantos FROM saldo WHERE identificador = :new.identificador;
		IF (cuantos = 0) THEN
			INSERT INTO saldo VALUES (:new.identificador, :new.cantidad);
		ELSE
			UPDATE saldo SET saldo = saldo + :new.cantidad WHERE identificador = :new.identificador;
		END IF;
	END IF;
END;
/
