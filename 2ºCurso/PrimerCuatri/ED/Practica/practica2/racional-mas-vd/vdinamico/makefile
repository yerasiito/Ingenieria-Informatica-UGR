INCLUDE = .
LIB     = .

usovd : usovd.cpp libvd.a
	g++ -L$(LIB) -o usovd -I$(INCLUDE) usovd.cpp -lvd

libvd.a : vector_dinamico.o 
	ar rvs $(LIB)/libvd.a vector_dinamico.o 

vector_dinamico.o : vector_dinamico.cpp
	g++ -c -o vector_dinamico.o -I$(INCLUDE) vector_dinamico.cpp 

