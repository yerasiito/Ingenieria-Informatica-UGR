HOME = .
BIN = $(HOME)/bin
SRC = $(HOME)/src
LIB = $(HOME)/lib
OBJ = $(HOME)/obj
#######################################
#EJECUTABLES

all: $(BIN)/usocola_max $(BIN)/cola_teclado $(BIN)/actualizar.sh

$(BIN)/usocola_max : $(OBJ)/usocolas_max.o $(OBJ)/Cola_max_Pila.o
	g++ -std=c++11 -o $(BIN)/usocola_max $(OBJ)/usocolas_max.o $(OBJ)/Cola_max_Pila.o

$(BIN)/cola_teclado : $(OBJ)/cola_teclado.o $(OBJ)/Cola_max_Pila.o
	g++ -std=c++11 -o $(BIN)/cola_teclado $(OBJ)/cola_teclado.o $(OBJ)/Cola_max_Pila.o

#####################################
#OBJETOS
$(OBJ)/usocolas_max.o : $(SRC)/usocolas_max.cpp
	@echo "Creando objeto: usocolas_max.o"
	g++ -std=c++11 -c $(SRC)/usocolas_max.cpp -o $(OBJ)/usocolas_max.o

$(OBJ)/cola_teclado.o : $(SRC)/cola_teclado.cpp
	@echo "Creando objeto: cola_teclado.o"
	g++ -std=c++11 -c $(SRC)/cola_teclado.cpp -o $(OBJ)/cola_teclado.o

$(OBJ)/Cola_max_Pila.o : $(SRC)/Cola_max_Pila.cpp $(SRC)/pila.h
	@echo "Creando objeto: Cola_max_Pila.o"
	g++ -std=c++11 -I $(SRC) -c $(SRC)/Cola_max_Pila.cpp -o $(OBJ)/Cola_max_Pila.o
#######################
clean :
	@echo "Borrando objetos"
	-rm obj/*
	@echo "Borrando ejecutables"
	-rm bin/*
	@echo "Borrando librerias"
	-rm lib/*
	@echo "Borrando carpeta doc"
	-rm -R doc/

##################################################
#Extras
$(BIN)/actualizar.sh:
	@echo "Creando actualizar.sh que contiene el comando:"
	-cd bin && touch actualizar.sh && echo "cd .. && make && cd bin" > actualizar.sh
	@echo "Ejecuta ./actualizar cada vez que modifiques los src para recompilar todo"
