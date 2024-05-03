HOME = .
BIN = $(HOME)/bin
SRC = $(HOME)/src
INCLUDE = $(HOME)/include
LIB = $(HOME)/lib
OBJ = $(HOME)/obj
#######################################
#EJECUTABLES

all: $(LIB)/diccionario.a $(BIN)/usodiccionario $(BIN)/actualizar.sh ejemplos

$(BIN)/usodiccionario : $(OBJ)/usodiccionario.o
	g++ -std=c++11 -o $(BIN)/usodiccionario $(OBJ)/usodiccionario.o

#####################################
#OBJETOS
$(OBJ)/usodiccionario.o : $(SRC)/usodiccionario.cpp $(INCLUDE)/diccionario.h
	@echo "Creando objeto: usodiccionario.o"
	g++ -std=c++11 -I $(INCLUDE) -c $(SRC)/usodiccionario.cpp -o $(OBJ)/usodiccionario.o

#######################

#LIBRERIAS
$(LIB)/diccionario.a : $(OBJ)/usodiccionario.o
	@echo "Creando biblioteca: diccionario.a"
	ar rvs $(LIB)/diccionario.a $(OBJ)/usodiccionario.o
#######################
clean :
	@echo "Borrando objetos"
	-rm obj/*
	@echo "Borrando ejecutables"
	-rm bin/*
	@echo "Borrando librerias"
	-rm lib/*
	@echo "Borrando carpeta doc"
	-rm -R doc/*
	@echo "Borrando carpeta output"
	-rm output/*
##################################################
#Extras
$(BIN)/actualizar.sh:
	@echo "Creando actualizar.sh que contiene el comando:"
	-cd bin && touch actualizar.sh && echo "cd .. && make && cd bin" > actualizar.sh
	@echo "Ejecuta ./actualizar cada vez que modifiques los src para recompilar todo"

documentar:
	@echo "Creando documentacion:"
	-./script.sh
ejemplos:
	@echo "Creando archivos output apartir de los datos de data"
	-./ejemplos.sh
