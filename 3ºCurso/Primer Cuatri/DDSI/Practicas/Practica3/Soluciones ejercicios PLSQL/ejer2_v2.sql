DECLARE
	TYPE tipo_tabla IS TABLE OF INTEGER INDEX BY BINARY_INTEGER;
	tabla tipo_tabla;
	contador INTEGER;
BEGIN
	FOR contador IN 1..20 LOOP
		tabla(contador) := contador;
	END LOOP;
	FOR contador IN 1..20 LOOP
		DBMS_OUTPUT.PUT_LINE ('Entrada ' || to_char(contador) || ': ' || to_char (tabla(contador)));
	END LOOP;
	tabla.DELETE;
END;
/
