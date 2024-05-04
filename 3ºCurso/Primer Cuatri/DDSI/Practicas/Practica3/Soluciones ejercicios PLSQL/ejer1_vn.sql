DECLARE
	irpf tabla_impositiva%ROWTYPE;
	resultado REAL;
BEGIN
	BEGIN
		SELECT * INTO irpf FROM tabla_impositiva WHERE 
			base_hasta <= 5750000 AND base_hasta + 
			resto_hasta >= 5750000;
	EXCEPTION
		WHEN no_data_found THEN
			RAISE_APPLICATION_ERROR (-20000, 'Dato no encontrado');
		WHEN OTHERS THEN
			RAISE;
	END;
	resultado := irpf.cuota + (5750000 - irpf.base_hasta) * 
		irpf.tipo_aplicable / 100;
	DBMS_OUTPUT.PUT_LINE ('IRPF para ' || to_char (5750000) ||
		' = ' || to_char (resultado));
END;
/
