SET SERVEROUTPUT ON;
DECLARE
	base_hasta tabla_impositiva.base_hasta%TYPE;
	cuota tabla_impositiva.cuota%TYPE;
	tipo tabla_impositiva.tipo_aplicable%TYPE;
	resultado REAL;
BEGIN
	SELECT base_hasta, cuota, tipo_aplicable INTO base_hasta, cuota, tipo FROM tabla_impositiva WHERE 
		base_hasta <= 34558.2 AND base_hasta + 
		resto_hasta >= 34558.2;
	resultado := cuota + (34558.2 - base_hasta) * tipo / 100;
	DBMS_OUTPUT.PUT_LINE ('IRPF para ' || to_char (34558.2) ||
		' = ' || to_char (resultado));
END;
/