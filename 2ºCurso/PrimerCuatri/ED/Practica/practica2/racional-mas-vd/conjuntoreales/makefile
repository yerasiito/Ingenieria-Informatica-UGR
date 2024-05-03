INCLUDE = .
LIB     = .

ejemplo_conjunto_reales : ejemplo_conjunto_reales.cpp  libcr.a  libvd.a
	g++ -L$(LIB) -o ejemplo_conjunto_reales -I$(INCLUDE) ejemplo_conjunto_reales.cpp -lcr -lvd

libcr.a : conjunto_reales.o 
	ar rvs $(LIB)/libcr.a conjunto_reales.o 

conjunto_reales.o : conjunto_reales.cpp
	g++ -c -o conjunto_reales.o -I$(INCLUDE) conjunto_reales.cpp 
	
libvd.a : vector_dinamico.o 
	ar rvs $(LIB)/libvd.a vector_dinamico.o 

vector_dinamico.o : vector_dinamico.cpp
	g++ -c -o vector_dinamico.o -I$(INCLUDE) vector_dinamico.cpp 


