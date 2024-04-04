--------------------------------------------------------
--  DDL para Tabla ALUMNO
-------------------------------------------------------- 
  
  CREATE TABLE Alumno 
   (DNI NUMBER PRIMARY KEY,  
	Nombre VARCHAR2(40), 
	Fecha_Nac DATE, 
	Direccion VARCHAR2(60), 
	Beca CHAR(5) DEFAULT 'False' CONSTRAINT Beca_es_S_o_N CHECK (Beca IN ('True','False')) 
   ) ;
   
--------------------------------------------------------
--  DDL para Tabla AULAS
--------------------------------------------------------   
  CREATE TABLE Aulas 
   (Cod_Aula VARCHAR2(5) PRIMARY KEY,  
	Capacidad NUMBER (3)
   ) ; 
   
   
 --------------------------------------------------------
--  DDL para Tabla DEPARTAMENTOS
--------------------------------------------------------   
  CREATE TABLE Departamentos 
   (Cod_Dep VARCHAR2(5) PRIMARY KEY,  
	Nombre VARCHAR2(40)
   ) ;   
   
--------------------------------------------------------
--  DDL para Tabla PROFESORES
-------------------------------------------------------- 
  
CREATE TABLE Profesores
   (NRP NUMBER PRIMARY KEY,  
	Nombre VARCHAR2(40), 
	Categoria VARCHAR2(25), 
	Area VARCHAR2(30),
	Pertenece NOT NULL REFERENCES Departamentos(Cod_Dep), -- Código del departamento al que pertenece
	Dirige CONSTRAINT Un_solo_director UNIQUE REFERENCES Departamentos(Cod_Dep), -- Código del departamento que dirige, este puede ser nulo. 
	-- Pero es clave candidata para evitar que un departamento esté dirigido por dos profesores
	CONSTRAINT Dirige_igual_pertenece CHECK (Dirige IS NULL or Dirige=Pertenece) -- Restringe que o bien dirige es NULO o si no debe ser igual a pertenece
   ) ;  
   
  
 --------------------------------------------------------
--  DDL para Tabla ASIGNATURAS
--------------------------------------------------------

  CREATE TABLE Asignaturas 
   (Cod_Asig VARCHAR2(4) PRIMARY KEY, 
	Nombre VARCHAR2(30), 
	Creditos NUMBER(2,1), 
	Caracter CHAR(2) CONSTRAINT Carácter_es_tr_ob_op_lc CHECK (Caracter IN ('Troncal','Optativa','Obligatoria','Libre')),
	Curso NUMBER(1) CONSTRAINT  Curso_in_1_5 CHECK (Curso BETWEEN 1 AND 5 )
   ) ;  
  
--------------------------------------------------------
--  DDL para Tabla GRUPO
--------------------------------------------------------

  CREATE TABLE Grupo 
   (Cod_Asig REFERENCES Asignaturas(Cod_Asig), 
	Cod_Grupo NUMBER(2), 
	Tipo VARCHAR2(9) CONSTRAINT Tipo_es_Teoría_o_Práctica CHECK (Tipo IN ('Teoría','Práctica')), 
	Max_Al NUMBER(3),
	NRP REFERENCES Profesores(NRP),
	PRIMARY KEY (Cod_Asig,Cod_Grupo,Tipo)
   ) ;

 
--------------------------------------------------------
--  DDL para Tabla MATRICULAS
--------------------------------------------------------

  CREATE TABLE Matriculas 
   (Cod_Asig, 
	Cod_Grupo, 
	Tipo CONSTRAINT Tipo__es_Teoría_o_Práctica CHECK (Tipo IN ('Teoría','Práctica')), 
	DNI REFERENCES Alumno(DNI),
	Convocatoria VARCHAR2(10) CONSTRAINT Formato_YYYYORD_o_YYYYEXTRA CHECK (Convocatoria LIKE '____ORD' OR  Convocatoria LIKE '____EXTRA'),
	Calificacion NUMBER (3,1) CONSTRAINT Calif_0_10  CHECK (Calificacion BETWEEN 0 AND 10),
	FOREIGN KEY (Cod_Asig,Cod_Grupo,Tipo) REFERENCES Grupo(Cod_Asig,Cod_Grupo,Tipo),
	PRIMARY KEY(Cod_Asig,Tipo,DNI,Convocatoria) --Al quitar Cod_grupo de la clave primaria evito que un alumno se matricule 
	-- de dos grupos de practicas o de teoría de la misma asignatura en la misma convocatoria
   ) ;
   
--------------------------------------------------------
--  DDL para Tabla Clases
--------------------------------------------------------

CREATE TABLE Clases 
   (Cod_Asig, 
	Cod_Grupo, 
	Tipo CONSTRAINT Tipo___es_Teoría_o_Práctica CHECK (Tipo IN ('Teoría','Práctica')), 
	Dia VARCHAR2(1) CONSTRAINT Dia_sem_in_L_M_X_J_V CHECK (Dia IN ('Lunes','Martes','Miércoles','Jueves','Viernes')),
	Hora NUMBER(4,2) CONSTRAINT Hora_8_30_a_21_30 CHECK (hora-0.3 in (8,9,10,11,12,13,14,15,16,17,18,19,20,21)),
	Cod_Aula REFERENCES Aulas(Cod_Aula) NOT NULL,
	FOREIGN KEY (Cod_Asig,Cod_Grupo,Tipo) REFERENCES Grupo(Cod_Asig,Cod_Grupo,Tipo),
	PRIMARY KEY(Cod_Asig,Cod_Grupo,Tipo,Dia,Hora),
    UNIQUE (Dia,Hora,Cod_Aula)
   ) ;



   
Insert into DEPARTAMENTOS (COD_DEP,NOMBRE) values ('CCIA','Ciencias de la Comp. e I.A.');
Insert into DEPARTAMENTOS (COD_DEP,NOMBRE) values ('LSI','Lenguajes y Sistemas Informáticos');   

Insert into Profesores (NRP,NOMBRE,CATEGORIA,AREA,PERTENECE,DIRIGE) values (111,'Pepe','Catedrático','CCIA','CCIA',NULL);
Insert into Profesores (NRP,NOMBRE,CATEGORIA,AREA,PERTENECE,DIRIGE) values (222,'Juan','Titular','LSI','LSI','LSI');
Insert into Profesores (NRP,NOMBRE,CATEGORIA,AREA,PERTENECE,DIRIGE) values (333,'Luis','Titular','LSI','LSI','LSI');
Insert into Profesores (NRP,NOMBRE,CATEGORIA,AREA,PERTENECE,DIRIGE) values (333,'Antonio','Titular','LSI','LSI','CCIA');