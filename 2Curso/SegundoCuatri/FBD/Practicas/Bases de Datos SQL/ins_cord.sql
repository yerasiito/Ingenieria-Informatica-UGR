INSERT INTO customers VALUES('A01','TKB SPORT SHOP','West');
INSERT INTO customers VALUES('A02','VOLLYRITE','North');
INSERT INTO customers VALUES('A03','JUST TENNIS','North');
INSERT INTO customers VALUES('A04','EVERY MOUNTAIN','South');
INSERT INTO customers VALUES('A05','SHAPE UP','South');
INSERT INTO customers VALUES('A06','SHAPE UP','West');
INSERT INTO customers VALUES('A07','WOMENS SPORTS','South');
INSERT INTO customers VALUES('A08','NORTH WOODS HEALTH AND FITNESS SUPPLY CENTER','East');
INSERT INTO orders(ord_id,ord_date,cust_code) VALUES(610,to_date('11-NOV-97','DD-MON-YY'),'A01');    
INSERT INTO orders(ord_id,ord_date,cust_code) VALUES(611,to_date('15-NOV-97','DD-MON-YY'),'A02');    
INSERT INTO orders(ord_id,ord_date,cust_code) VALUES(612,to_date('19-NOV-97','DD-MON-YY'),'A04');    
INSERT INTO orders(ord_id,ord_date,cust_code) VALUES(601,to_date('05-MAR-97','DD-MON-YY'),'A06');    
INSERT INTO orders(ord_id,ord_date,cust_code) VALUES(602,to_date('09-ABR-97','DD-MON-YY'),'A02');    
INSERT INTO orders(ord_id,ord_date,cust_code) VALUES(600,to_date('05-MAR-97','DD-MON-YY'),'A03');    
INSERT INTO orders(ord_id,ord_date,cust_code) VALUES(604,to_date('19-ABR-97','DD-MON-YY'),'A06');    
INSERT INTO orders(ord_id,ord_date,cust_code) VALUES(605,to_date('18-MAY-97','DD-MON-YY'),'A06');    
INSERT INTO orders(ord_id,ord_date,cust_code) VALUES(607,to_date('22-MAY-97','DD-MON-YY'),'A04');    
INSERT INTO orders(ord_id,ord_date,cust_code) VALUES(608,to_date('29-MAY-97','DD-MON-YY'),'A04');    
INSERT INTO orders(ord_id,ord_date,cust_code) VALUES(603,to_date('09-ABR-97','DD-MON-YY'),'A02');    
INSERT INTO orders(ord_id,ord_date,cust_code) VALUES(613,to_date('06-DIC-97','DD-MON-YY'),'A08');    
INSERT INTO orders(ord_id,ord_date,cust_code) VALUES(614,to_date('06-DIC-97','DD-MON-YY'),'A02');    
INSERT INTO orders(ord_id,ord_date,cust_code) VALUES(616,to_date('08-DIC-97','DD-MON-YY'),'A03');    
INSERT INTO orders(ord_id,ord_date,cust_code) VALUES(619,to_date('27-DIC-97','DD-MON-YY'),'A04');    
INSERT INTO orders(ord_id,ord_date,cust_code) VALUES(617,to_date('10-DIC-97','DD-MON-YY'),'A05');    
INSERT INTO orders(ord_id,ord_date,cust_code) VALUES(615,to_date('06-DIC-97','DD-MON-YY'),'A07');    
INSERT INTO orders(ord_id,ord_date,cust_code) VALUES(618,to_date('20-DIC-97','DD-MON-YY'),'A02');    
commit;