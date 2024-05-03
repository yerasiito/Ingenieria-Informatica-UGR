HOME = .
BIN = $(HOME)/bin
SRC = $(HOME)/src
INCLUDE = $(HOME)/include
LIB = $(HOME)/lib
OBJ = $(HOME)/obj
#######################################
#EJECUTABLES

all: $(BIN)/ejemplo $(BIN)/main $(BIN)/actualizar.sh

$(BIN)/ejemplo : $(OBJ)/ejemplo.o $(OBJ)/imagenES.o $(LIB)/imagen.a $(LIB)/imagenES.a
	@echo "Creando el ejecutable: ejemplo"
	g++ -o $(BIN)/ejemplo $(OBJ)/ejemplo.o $(LIB)/imagen.a $(LIB)/imagenES.a -L $(LIB)

$(BIN)/main : $(OBJ)/main.o $(OBJ)/imagenES.o $(LIB)/imagen.a $(LIB)/imagenES.a
	@echo "Creando el ejecutable: main"
	g++ -o $(BIN)/main $(OBJ)/main.o $(OBJ)/imagenES.o $(LIB)/imagen.a $(LIB)/imagenES.a -L $(LIB)

#####################################
#OBJETOS
$(OBJ)/imagenES.o : $(SRC)/imagenES.cpp $(INCLUDE)/imagenES.h
	@echo "Creando objeto: imagenES.o"
	g++ -c -I$(INCLUDE) -c $(SRC)/imagenES.cpp -o $(OBJ)/imagenES.o

$(OBJ)/imagen.o : $(SRC)/imagen.cpp $(INCLUDE)/imagen.h
	@echo "Creando objeto: imagen.o"
	g++ -c -I$(INCLUDE) -c $(SRC)/imagen.cpp -o $(OBJ)/imagen.o

$(OBJ)/main.o : $(SRC)/main.cpp
	@echo "Creacion del objeto: main.o"
	g++ -c $(SRC)/main.cpp -o $(OBJ)/main.o -I$(INCLUDE) -std=c++11

$(OBJ)/ejemplo.o : $(SRC)/ejemplo.cpp $(INCLUDE)/imagen.h $(INCLUDE)/imagenES.h
	@echo "Creando el objeto ejemplo.o"
	g++ -c $(SRC)/ejemplo.cpp -o $(OBJ)/ejemplo.o -I$(INCLUDE) -std=c++11
######################

#LIBRERIAS
$(LIB)/imagen.a : $(OBJ)/imagen.o
	@echo "Creando biblioteca: imagen.a"
	ar rvs $(LIB)/imagen.a $(OBJ)/imagen.o
$(LIB)/imagenES.a : $(OBJ)/imagenES.o
	@echo "Creación de la librería: imagenES.a"
	ar rvs $(LIB)/imagenES.a $(OBJ)/imagenES.o
#######################

clean :
	@echo "Borrando objetos"
	-rm obj/*
	@echo "Borrando imagenes generadas por Morphing"
	-rm imagenes/Morphing/img*
	-rm imagenes/MorphingEjemplo/img*
	@echo "Borrando ejecutables"
	-rm bin/*
	@echo "Borrando librerias"
	-rm lib/*
	@echo "Borrando ejercicios generados"
	-rm imagenes/ejer/ejer* imagenes/*.ico
	@echo "Borrando carpeta doc"
	-rm -R doc/

##################################################
#Extras
$(BIN)/actualizar.sh:
	@echo "Creando actualizar.sh que contiene el comando:"
	-cd bin && touch actualizar.sh && echo "cd .. && make && cd bin" > actualizar.sh
	@echo "Ejecuta ./actualizar cada vez que modifiques los src para recompilar todo"
