DECLARE
	valor NUMBER := 120202.42;
	TYPE fila_tabla IS RECORD (
		cuota NUMBER,
		base_hasta NUMBER,
		tipo_aplicable NUMBER(4,1));
	registro_tabla fila_tabla;
	resultado REAL;
	cuantos INTEGER;
BEGIN
	SELECT COUNT(*) INTO cuantos FROM tabla_impositiva WHERE 
		base_hasta <= valor AND base_hasta + 
		resto_hasta >= valor;
	IF (cuantos > 0) THEN
		SELECT cuota, base_hasta, tipo_aplicable INTO registro_tabla FROM tabla_impositiva WHERE 
			base_hasta <= valor AND base_hasta + resto_hasta >= valor;
		resultado := registro_tabla.cuota + (valor - registro_tabla.base_hasta) * 
			registro_tabla.tipo_aplicable / 100;
		DBMS_OUTPUT.PUT_LINE ('IRPF para ' || to_char (resultado) ||
			' = ' || to_char (resultado));
	ELSE
		DBMS_OUTPUT.PUT_LINE ('No existen datos');
	END IF;
END;
/
