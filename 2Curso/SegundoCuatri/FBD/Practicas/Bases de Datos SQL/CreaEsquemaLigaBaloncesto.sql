-- Esquema de la Base de Datos de la Liga de Baloncesto
create table equipos(
  codE varchar(3)  constraint codE_clave_primaria primary key,
    nombreE varchar(30) constraint nombreE_no_nulo not null constraint nombreE_unico unique,
    localidad varchar(30) constraint localidad_no_nulo not null,
    entrenador varchar(30) constraint entrenador_no_nulo not null,
    fecha_crea date default sysdate   
);

create table jugadores(
  codJ varchar(3) constraint codJ_clave_primaria primary key,
  codE constraint codE_no_nulo_jugadores not null constraint codE_clave_externa references equipos(codE),
  nombreJ char(30) constraint nombreJ_no_nulo not null constraint nombreJ_unico unique
);

create table encuentros(
  ELocal constraint eq1_clave_externa references equipos(codE),
  EVisitante constraint eq2_clave_externa references equipos(codE),
  fecha date constraint fecha_no_nulo not null,
  Plocal number(3) default 0 constraint res1_mayor_0 check (Plocal>=0),
  PVisitante number(3) default 0 constraint res2_mayor_0 check (PVisitante>=0), 
  constraint eq1eq2_distintos check (ELocal <> EVisitante),
  constraint eq1eq2_clave_primaria primary key(ELocal, Evisitante)
);

create table alineaciones(
  codJ constraint codJ_no_nulo_alineaciones not null,
  ELocal constraint eq1_no_nulo_alineaciones not null,
  EVisitante constraint eq2_no_nulo_alineaciones not null,
  Faltas number(1) default 0 constraint valor_entre_0_5 check (Faltas>=0 and Faltas<=5),
  constraint codJEq1Eq2_clave_primaria primary key(codJ, ELocal, EVisitante),
  constraint eq1eq2_clave_externa foreign key(ELocal, EVisitante) references encuentros(ELocal, EVisitante),
  constraint codj_clave_externa foreign key(codJ) references jugadores(codJ)
);


 
