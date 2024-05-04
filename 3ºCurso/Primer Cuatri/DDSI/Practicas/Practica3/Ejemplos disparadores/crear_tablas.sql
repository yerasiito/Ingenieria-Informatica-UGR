CREATE TABLE empleados(
	dni char(9) PRIMARY KEY,
	nombre varchar2(50),
	dni_jefe char(9),
	departamento integer,
	sueldo number(7,2) DEFAULT 1500,
	usuario varchar2(50),
	fecha date,
	FOREIGN KEY (dni_jefe) REFERENCES empleados (dni)
);


CREATE TABLE empleados_baja(
	dni char(9) PRIMARY KEY,
	nombre varchar2(50),
	dni_jefe char(9),
	departamento integer,
	sueldo number(7,2) DEFAULT 1500,
	usuario varchar2(50),
	fecha date
);