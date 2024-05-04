CREATE OR REPLACE PROCEDURE saldoConsistente AS
	CURSOR saldos IS SELECT * FROM saldo;
	registro_saldo saldos%ROWTYPE;
	cuantos INTEGER;
BEGIN
	OPEN saldos;
	FETCH saldos INTO registro_saldo;
	WHILE (saldos%FOUND) LOOP
		SELECT COUNT(*) INTO cuantos FROM movimiento WHERE identificador = registro_saldo.identificador;
		IF (cuantos = 0) THEN
			DELETE FROM saldo WHERE identificador = registro_saldo.identificador;
		END IF;
		FETCH saldos INTO registro_saldo;
	END LOOP;
	CLOSE saldos;
EXCEPTION
	WHEN OTHERS THEN
		IF (saldos%ISOPEN) THEN
			CLOSE saldos;
		END IF;
END;
/
