CREATE OR REPLACE TRIGGER nuevoSaldo
AFTER INSERT OR DELETE OR UPDATE ON movimiento
FOR EACH ROW 
DECLARE
	cuantos INTEGER;
BEGIN
	IF INSERTING THEN
		BEGIN
			UPDATE saldo SET saldo = saldo + :new.cantidad WHERE identificador = :new.identificador;
		EXCEPTION
			WHEN no_data_found THEN
				INSERT INTO saldo VALUES (:new.identificador, :new.cantidad);
		END;
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
		BEGIN
			UPDATE saldo SET saldo = saldo + :new.cantidad WHERE identificador = :new.identificador;
		EXCEPTION
			WHEN no_data_found THEN
				INSERT INTO saldo VALUES (:new.identificador, :new.cantidad);
		END;
	END IF;
END;
/
