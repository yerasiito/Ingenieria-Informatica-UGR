HOME = .
BIN = $(HOME)/bin
SRC = $(HOME)/src
LIB = $(HOME)/lib
OBJ = $(HOME)/obj
INC = $(HOME)/include
CXX = g++
FLAGS = -std=c++11 -Wall -Wextra -g
INCLUDES = -I $(INC)
DOXYFILE = Doxyfile.doxy

all: $(BIN)/testLetras $(BIN)/testDiccionario $(BIN)/cantidadLetras $(BIN)/actualizar.sh

###########################################################################################################
#EJECUTABLES
###########################################################################################################

$(BIN)/testDiccionario : $(OBJ)/testDiccionario.o $(OBJ)/diccionario.o
	@echo "Creando ejecutable: testDiccionario.o"
	$(CXX) $(INCLUDES) -o $(@) $(^)

$(BIN)/testLetras : $(OBJ)/testLetras.o $(LIB)/juegoLetras.a
	@echo "Creando ejecutable: testLetras.o"
	$(CXX) $(INCLUDES) -o $(@) $(<) $(LIB)/juegoLetras.a

$(BIN)/cantidadLetras : $(OBJ)/cantidadLetras.o $(OBJ)/diccionario.o $(OBJ)/letra.o $(OBJ)/conjuntoLetras.o
	@echo "Creando ejecutable: cantidadLetras.o"
	$(CXX) $(INCLUDES) -o $(@) $(^)

###########################################################################################################
#OBJETOS
###########################################################################################################

$(OBJ)/letra.o : $(SRC)/letra.cpp
	@echo "Creando objeto: letra.o"
	$(CXX) $(INCLUDES) $(FLAGS) -c $(^) -o $(@)

$(OBJ)/conjuntoLetras.o : $(SRC)/conjuntoLetras.cpp
	@echo "Creando objeto: conjuntoLetras.o"
	$(CXX) $(INCLUDES) $(FLAGS) -c $(^) -o $(@)

$(OBJ)/bolsaLetras.o : $(SRC)/bolsaLetras.cpp
	@echo "Creando objeto: bolsaLetras.o"
	$(CXX) $(INCLUDES) $(FLAGS) -c $(^) -o $(@)

$(OBJ)/diccionario.o : $(SRC)/diccionario.cpp
	@echo "Creando objeto: diccionario.o"
	$(CXX) $(INCLUDES) $(FLAGS) -c $(^) -o $(@)

$(OBJ)/testDiccionario.o : $(SRC)/testDiccionario.cpp
	@echo "Creando objeto: testDiccionario.o"
	$(CXX) $(INCLUDES) $(FLAGS) -c $(^) -o $(@)

$(OBJ)/testLetras.o : $(SRC)/testLetras.cpp
	@echo "Creando objeto: testLetras.o"
	$(CXX) $(INCLUDES) $(FLAGS) -c $(^) -o $(@)

$(OBJ)/cantidadLetras.o : $(SRC)/cantidadLetras.cpp
	@echo "Creando objeto: cantidadLetras.o"
	$(CXX) $(INCLUDES) $(FLAGS) -c $(^) -o $(@)

#LIBRERIAS
$(LIB)/juegoLetras.a : $(OBJ)/diccionario.o $(OBJ)/letra.o $(OBJ)/conjuntoLetras.o $(OBJ)/bolsaLetras.o
	@echo "Creando biblioteca: juegoLetras.a"
	ar rvs $(@) $(^)

############################################################################################################
clean :
	@echo "Borrando objetos"
	-rm obj/*
	@echo "Borrando ejecutables"
	-rm bin/*
	@echo "Borrando librerias"
	-rm lib/*
	@echo "Borrando carpeta doc"
	-rm -R doc/

documentacion:
	-scripts/doc.sh

############################################################################################################
#TESTS
############################################################################################################
testDiccionario:
	-bin/testDiccionario datos/diccionario1000.txt
testCantidadLetras:
	-bin/cantidadLetras datos/spanish.txt datos/letras.txt output/salida.txt
	-cat datos/letras.txt
	-cat output/salida.txt
testLetras:
	-bin/testLetras datos/spanish.txt datos/letras.txt $(ARG1) $(ARG2)
	-tput setaf 1 && echo "Ejemplo Uso: make testLetras ARG1=8 ARG2=L" && tput sgr0



#Extras
$(BIN)/actualizar.sh:
	@echo "Creando actualizar.sh que contiene el comando:"
	-cd bin && touch actualizar.sh && echo "cd .. && make && cd bin" > actualizar.sh
	@echo "Ejecuta ./actualizar cada vez que modifiques los src para recompilar todo"

