secuencia='secuencia.txt'

all: genera-compraventa main

.SILENT:
ejecutar:
ifdef num_elem
	./genera-compraventa $(num_elem) > $(secuencia)
else
	./genera-compraventa 10 > $(secuencia)
endif
	./main $(secuencia)

genera-compraventa: genera-compraventa.cpp
	g++ -o genera-compraventa genera-compraventa.cpp

main: main.cpp
	g++ -o main main.cpp
