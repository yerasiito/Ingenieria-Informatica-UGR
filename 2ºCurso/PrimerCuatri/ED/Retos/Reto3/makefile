HOME = .
BIN = $(HOME)/bin
SRC = $(HOME)/src
OBJ = $(HOME)/obj
#######################################
#EJECUTABLES

all: $(BIN)/ejer16 $(BIN)/ejer19 $(BIN)/ejer20 $(BIN)/ejer21 $(BIN)/ejer24 $(BIN)/actualizar.sh

$(BIN)/ejer16 : $(OBJ)/ejercicio16.o
	@echo "Creando el ejercicio 16"
	g++ -o $(BIN)/ejer16 $(OBJ)/ejercicio16.o

$(BIN)/ejer19 : $(OBJ)/ejercicio19.o
	@echo "Creando el ejercicio 19"
	g++ -o $(BIN)/ejer19 $(OBJ)/ejercicio19.o

$(BIN)/ejer20 : $(OBJ)/ejercicio20.o
	@echo "Creando el ejercicio 20"
	g++ -o $(BIN)/ejer20 $(OBJ)/ejercicio20.o

$(BIN)/ejer21 : $(OBJ)/ejercicio21.o
	@echo "Creando el ejercicio 21"
	g++ -o $(BIN)/ejer21 $(OBJ)/ejercicio21.o

$(BIN)/ejer24 : $(OBJ)/ejercicio24.o
	@echo "Creando el ejercicio 24"
	g++ -o $(BIN)/ejer24 $(OBJ)/ejercicio24.o

#####################################
#OBJETOS
$(OBJ)/ejercicio16.o : $(SRC)/ejercicio16.cpp
	@echo "Creando el objeto ejercicio16.o"
	g++  -std=c++11 -c $(SRC)/ejercicio16.cpp -o $(OBJ)/ejercicio16.o

$(OBJ)/ejercicio19.o : $(SRC)/ejercicio19.cpp
	@echo "Creando el objeto ejercicio19.o"
	g++  -std=c++11 -c $(SRC)/ejercicio19.cpp -o $(OBJ)/ejercicio19.o

$(OBJ)/ejercicio20.o : $(SRC)/ejercicio20.cpp
	@echo "Creando el objeto ejercicio20.o"
	g++  -std=c++11 -c $(SRC)/ejercicio20.cpp -o $(OBJ)/ejercicio20.o

$(OBJ)/ejercicio21.o : $(SRC)/ejercicio21.cpp
	@echo "Creando el objeto ejercicio21.o"
	g++  -std=c++11 -c $(SRC)/ejercicio21.cpp -o $(OBJ)/ejercicio21.o

$(OBJ)/ejercicio24.o : $(SRC)/ejercicio24.cpp
	@echo "Creando el objeto ejemplo.o"
	g++  -std=c++11 -c $(SRC)/ejercicio24.cpp -o $(OBJ)/ejercicio24.o
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
