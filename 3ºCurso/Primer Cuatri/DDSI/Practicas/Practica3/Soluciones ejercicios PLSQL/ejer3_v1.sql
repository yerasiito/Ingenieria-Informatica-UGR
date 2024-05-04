CREATE TABLE saldo (identificador NUMBER(5) PRIMARY KEY, saldo NUMBER);
INSERT INTO saldo VALUES (1, 50);
INSERT INTO saldo VALUES (2, 20);
CREATE TABLE movimiento (identificador NUMBER(5) REFERENCES saldo, cantidad NUMBER);
INSERT INTO movimiento VALUES (1, 100);
INSERT INTO movimiento VALUES (1, -50);
INSERT INTO movimiento VALUES (2, 20);
