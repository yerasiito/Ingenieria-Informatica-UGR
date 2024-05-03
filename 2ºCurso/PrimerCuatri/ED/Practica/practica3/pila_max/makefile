HOME = .
BIN = $(HOME)/bin
SRC = $(HOME)/src
LIB = $(HOME)/lib
OBJ = $(HOME)/obj
#######################################
#EJECUTABLES

all: $(BIN)/usopila_max $(BIN)/actualizar.sh $(BIN)/pila_teclado

$(BIN)/usopila_max : $(OBJ)/usopila_max.o $(OBJ)/Pila_max_Cola.o
	g++ -std=c++11 -o $(BIN)/usopila_max $(OBJ)/usopila_max.o $(OBJ)/Pila_max_Cola.o

$(BIN)/pila_teclado : $(OBJ)/pila_teclado.o $(OBJ)/Pila_max_Cola.o
	g++ -std=c++11 -o $(BIN)/pila_teclado $(OBJ)/pila_teclado.o $(OBJ)/Pila_max_Cola.o

#####################################
#OBJETOS
$(OBJ)/usopila_max.o : $(SRC)/usopilas_max.cpp
	@echo "Creando objeto: usopila_max.o"
	g++ -std=c++11 -c $(SRC)/usopilas_max.cpp -o $(OBJ)/usopila_max.o

$(OBJ)/pila_teclado.o : $(SRC)/pila_teclado.cpp
	@echo "Creando objeto: pila_teclado.o"
	g++ -std=c++11 -c $(SRC)/pila_teclado.cpp -o $(OBJ)/pila_teclado.o

$(OBJ)/Pila_max_Cola.o : $(SRC)/Pila_max_Cola.cpp $(SRC)/cola.h
	@echo "Creando objeto: Pila_max_Cola.o"
		g++ -std=c++11 -I $(SRC) -c $(SRC)/Pila_max_Cola.cpp -o $(OBJ)/Pila_max_Cola.o
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
