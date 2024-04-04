insert into equipos values('RMA','Real Madrid','Madrid','Pablo Laso','13/05/1931');
insert into equipos values('FCB','Barcelona Regal','Barcelona','Xavi Pascual','24/08/1926');
insert into equipos values('UNI','Unicaja','Malaga','Luis Casimiro','05/10/1977');
insert into equipos values('VAL','Valencia','Valencia Basket','Velimir Perasovic','04/03/1986');
insert into equipos values('CAL','Caja Laboral','Vitoria','Dusko Ivanovic','24/11/1959');
insert into equipos values ('REG','Regal FC Barcelona','Barcelona','Xavier Pascual','24/08/1926');
insert into equipos values ('BIZ','Bizkaia Bilbao Basket','Bilbao','Fotis Katsikaris','01/01/2000');
insert into equipos values ('BLR','Blancos de Rueda Valladolid','Valladolid','Luis Casimiro','01/01/1976');
insert into equipos values ('VLB','Valencia Basket','Valencia','Pacos Olmos','01/01/1986');



insert into jugadores values('A1','CAL','Pau Ribas');
insert into jugadores values('A2','CAL','F. San Emeterio');
insert into jugadores values('A3','CAL','Unai Calbarro');
insert into jugadores values('A4','CAL','Andres Nocioni');
insert into jugadores values('A5','CAL','Pablo Prigioni');

insert into jugadores values('B1','RMA','Carlos Suarez');
insert into jugadores values('B2','RMA','Felipe Reyes');
insert into jugadores values('B3','RMA','Sergio Rodriguez');
insert into jugadores values('B4','RMA','Sergio Llull');
insert into jugadores values('B5','RMA','Ante Tomic');

insert into jugadores values('C1','FCB','Victor Sada');
insert into jugadores values('C2','FCB','Juan Carlos Navarro');
insert into jugadores values('C3','FCB','Fran Vazquez');
insert into jugadores values('C4','FCB','Joe Ingles');
insert into jugadores values('C5','FCB','Boniface Ndong');

insert into jugadores values('D1','UNI','Berni Rodriguez');
insert into jugadores values('D2','UNI','Jorge Garbajosa');
insert into jugadores values('D3','UNI','Luka Zoric');
insert into jugadores values('D4','UNI','Alberto Diaz');
insert into jugadores values('D5','UNI','Joel Freeland');

insert into jugadores values('E1','VAL','Rodrigo San Miguel');
insert into jugadores values('E2','VAL','Victor Claver');
insert into jugadores values('E3','VAL','Alberto Perez');
insert into jugadores values('E4','VAL','Taquan Dean');
insert into jugadores values('E5','VAL','Juanlu Navarro');

insert into jugadores values ('F1','REG','Huertas, Marcelinho');
insert into jugadores values ('F2','REG','Jawai, Nathan');
insert into jugadores values ('F3','REG','Lorbek, Eraem');
insert into jugadores values ('F4','REG','Tomic, Ante');
insert into jugadores values ('F5','REG','Jasikeviius, Arnas');

insert into jugadores values ('G1','BIZ','Zisis, Nikolaos');
insert into jugadores values ('G2','BIZ','Rakovich, Milovan');
insert into jugadores values ('G3','BIZ','Pilepic, Fran');
insert into jugadores values ('G4','BIZ','Hamilton, Lamont');
insert into jugadores values ('G5','BIZ','Vasileiadis, Kostas');

insert into jugadores values ('H1','BLR','Faverani, Vitor');
insert into jugadores values ('H2','BLR','Markovick, Stefan');
insert into jugadores values ('H3','BLR','Doellman, Justin');
insert into jugadores values ('H4','BLR','Dubljevic, Bojan');
insert into jugadores values ('H5','BLR','Hanley, Will');

insert into jugadores values ('I1','VLB','Pietrus, Florent');
insert into jugadores values ('I2','VLB','Kelati, Thomas');
insert into jugadores values ('I3','VLB','Robinson, Jason');
insert into jugadores values ('I4','VLB','Hrycaniuk, Adam');
insert into jugadores values ('I5','VLB','Martinez, Rafa ');




insert into encuentros values('CAL','VAL','23/10/2011','72','82');
insert into encuentros values('UNI','VAL','26/02/2012','58','68');
insert into encuentros values('RMA','VAL','04/11/2011','81','64');
insert into encuentros values('RMA','FCB','04/01/2012','78','74');
insert into encuentros values('UNI','RMA','13/11/2011','80','96');
insert into encuentros values('CAL','FCB','18/12/2011','71','60');
insert into encuentros values('FCB','UNI','11/12/2011','72','62');
insert into encuentros values('FCB','VAL','24/05/2012','84','57');
insert into encuentros values('RMA','CAL','22/01/2012','84','73');
insert into encuentros values('UNI','CAL','26/11/2011','79','66');
insert into encuentros values ('REG','BIZ','29/09/2012','73','89');
insert into encuentros values ('BLR','VLB','01/10/2012','78','111');
insert into encuentros values ('REG','BLR','09/10/2012','101','89');
insert into encuentros values ('BIZ','VLB','12/10/2012','87','99');
insert into encuentros values ('VLB','REG','15/10/2012','120','80');
insert into encuentros values ('BLR','BIZ','18/10/2012','110','99');
insert into encuentros values ('REG','VLB','29/10/2012','91','99');
insert into encuentros values ('BIZ','BLR','01/11/2012','97','89');
insert into encuentros values ('BIZ','REG','07/11/2012','79','88');
insert into encuentros values ('VLB','BLR','12/11/2012','71','88');

insert into alineaciones values ('F1' ,'REG','BIZ',1);
insert into alineaciones values ('G3' ,'REG','BIZ',2);
insert into alineaciones values ('F4' ,'REG','BIZ',2);
insert into alineaciones values ('G2' ,'REG','BIZ',3);
insert into alineaciones values ('G1' ,'REG','BIZ',1);

insert into alineaciones values ('C3' ,'FCB','UNI',4); 
insert into alineaciones values ('D5' ,'FCB','UNI',3); 
insert into alineaciones values ('C5' ,'FCB','UNI',2); 
insert into alineaciones values ('D1' ,'FCB','UNI',3); 
insert into alineaciones values ('D4' ,'FCB','UNI',1); 

insert into alineaciones values ('B3' ,'RMA','VAL',1);
insert into alineaciones values ('B2' ,'RMA','VAL',1);
insert into alineaciones values ('E1' ,'RMA','VAL',2);
insert into alineaciones values ('E5' ,'RMA','VAL',3);
insert into alineaciones values ('B5' ,'RMA','VAL',4);
insert into alineaciones values ('B1' ,'RMA','VAL',4);
insert into alineaciones values ('E2' ,'RMA','VAL',4);

insert into alineaciones values ('F5' ,'VLB','REG',1);
insert into alineaciones values ('I3' ,'VLB','REG',1); 
insert into alineaciones values ('I4' ,'VLB','REG',1);
insert into alineaciones values ('F2' ,'VLB','REG',1);
 



 
