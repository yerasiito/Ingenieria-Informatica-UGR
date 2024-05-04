CREATE OR REPLACE PROCEDURE saldoConsistente2 AS
	CURSOR saldos IS SELECT * FROM saldo;
	registro_saldo saldos%ROWTYPE;
	cid INTEGER;
	sentencia VARCHAR2(500);
	cant movimiento.cantidad%TYPE;
	nfilas INTEGER;
	leidas INTEGER;
	suma saldo.saldo%TYPE;
BEGIN
	OPEN saldos;
	FETCH saldos INTO registro_saldo;
	sentencia := 'SELECT cantidad FROM movimiento WHERE identificador = :id';
	WHILE (saldos%FOUND) LOOP
		suma := 0;
		cid := DBMS_SQL.OPEN_CURSOR;
		DBMS_SQL.PARSE (cid, sentencia, DBMS_SQL.V7);
		DBMS_SQL.BIND_VARIABLE (cid, ':id', registro_saldo.identificador);
		DBMS_SQL.DEFINE_COLUMN (cid, 1, cant);
		nfilas := DBMS_SQL.EXECUTE (cid);
		leidas := DBMS_SQL.FETCH_ROWS (cid);
		WHILE (leidas > 0) LOOP
			DBMS_SQL.COLUMN_VALUE (cid, 1, cant);
			suma := suma + cant;
			leidas := DBMS_SQL.FETCH_ROWS (cid);
		END LOOP;
		DBMS_SQL.CLOSE_CURSOR (cid);
		IF (registro_saldo.saldo <> suma) THEN
			UPDATE saldo SET saldo = suma WHERE identificador = registro_saldo.identificador;
		END IF;
		FETCH saldos INTO registro_saldo;
	END LOOP;
	CLOSE saldos;
EXCEPTION
	WHEN OTHERS THEN
		IF (saldos%ISOPEN) THEN
			CLOSE saldos;
		END IF;
		IF (DBMS_SQL.IS_OPEN (cid)) THEN
			DBMS_SQL.CLOSE_CURSOR (cid);
		END IF;
END;
/
