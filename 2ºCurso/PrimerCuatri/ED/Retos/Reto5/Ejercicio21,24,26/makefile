INCLUDE = -I ./include

./bin/usobintree : ./obj/usobintree.o
	g++ -std=c++11 -g -o ./bin/usobintree ./obj/usobintree.o

./obj/usobintree.o : ./src/usobintree.cpp ./src/ejercicios.cpp ./include/bintree.hxx
	g++ -std=c++11 -g $(INCLUDE) -c ./src/usobintree.cpp -o ./obj/usobintree.o
