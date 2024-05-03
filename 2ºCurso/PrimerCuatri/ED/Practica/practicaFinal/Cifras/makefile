HOME = .
BIN = $(HOME)/bin
SRC = $(HOME)/src
OBJ = $(HOME)/obj
INCLUDE = $(HOME)/include
#######################################
#EJECUTABLES

all: $(BIN)/testcifras $(BIN)/actualizar.sh


$(BIN)/testcifras  : $(OBJ)/testcifras.o $(OBJ)/cifras.o 
	@echo "Creando el testcifras"
	g++ -I -o $(INCLUDE) $(BIN)/testcifras $(OBJ)/testcifras.o $(OBJ)/cifras.o 

#####################################
#OBJETOS
$(OBJ)/testcifras.o : $(SRC)/testcifras.cpp
	@echo "Creando el objeto testcifras.o"
	g++  -std=c++11 -I $(INCLUDE) -c $(SRC)/testcifras.cpp -o $(OBJ)/testcifras.o

$(OBJ)/cifras.o : $(SRC)/cifras.cpp
	@echo "Creando el objeto cifras.o"
	g++  -std=c++11 -I $(INCLUDE) -c $(SRC)/cifras.cpp -o $(OBJ)/cifras.o

#######################

clean :
	@echo "Borrando objetos"
	-rm obj/*
	@echo "Borrando ejecutables"
	-rm bin/*
	@echo "Borrando carpeta doc"
	-rm -R doc/

##################################################
#Extras
$(BIN)/actualizar.sh:
	@echo "Creando actualizar.sh que contiene el comando:"
	-cd bin && touch actualizar.sh && echo "cd .. && make && cd bin" > actualizar.sh
	@echo "Ejecuta ./actualizar cada vez que modifiques los src para recompilar todo"
