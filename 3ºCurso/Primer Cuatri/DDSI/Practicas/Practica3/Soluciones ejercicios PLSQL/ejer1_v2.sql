DECLARE
	TYPE fila_tabla IS RECORD (
		cuota NUMBER,
		base_hasta NUMBER,
		tipo_aplicable NUMBER(4,1));
	registro_tabla fila_tabla;
	resultado REAL;
BEGIN
	SELECT cuota, base_hasta, tipo_aplicable INTO registro_tabla FROM 	
		tabla_impositiva WHERE base_hasta <= 34558.2 AND 
		base_hasta + resto_hasta >= 34558.2;
	resultado := registro_tabla.cuota + (34558.2 - 
		registro_tabla.base_hasta) * registro_tabla.tipo_aplicable / 
		100;
	DBMS_OUTPUT.PUT_LINE ('IRPF para ' || to_char (34558.2) ||
		' = ' || to_char (resultado));
END;
/
