DECLARE
	TYPE tipo_tabla IS TABLE OF INTEGER INDEX BY BINARY_INTEGER;
	tabla tipo_tabla;
BEGIN
	tabla(1) := 1;
	tabla(2) := 2;
	tabla(3) := 3;
	tabla(5) := 5;
	tabla(7) := 7;
	tabla(11) := 11;
	DBMS_OUTPUT.PUT_LINE ('Entrada 1: ' || to_char (tabla(1)));
	DBMS_OUTPUT.PUT_LINE ('Entrada 2: ' || to_char (tabla(2)));
	DBMS_OUTPUT.PUT_LINE ('Entrada 3: ' || to_char (tabla(3)));
	DBMS_OUTPUT.PUT_LINE ('Entrada 5: ' || to_char (tabla(5)));
	DBMS_OUTPUT.PUT_LINE ('Entrada 7: ' || to_char (tabla(7)));
	DBMS_OUTPUT.PUT_LINE ('Entrada 11: ' || to_char (tabla(11)));
	tabla.DELETE;
END;
/
