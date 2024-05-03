CPP=$(wildcard *.cpp)
EXE=$(basename $(CPP))
# Modifica aquí para ajustar el nivel de optimización (de 0 a 3):
CPPFLAGS=-O0
DAT=tiempos_busqueda.dat tiempos_ej3.dat

.PHONY: default clean tiempos

default: $(EXE)

clean:
	rm -f $(EXE) $(DAT)

# Modifica aquí para cambiar los puntos de inicio, fin y los saltos:
inicio_busq=100
fin_busq=1000000
incremento=1000
inicio_ej3=1024
fin_ej3=1000000000
factor=2

tiempos: $(DAT)

tiempos_busqueda.dat: busqueda_lineal
	for (( i=$(inicio_busq); i < $(fin_busq); i+=$(incremento) )); do \
		cmd="./$< $$i 10000"; \
		echo -en "\r$$cmd"; \
		$$cmd >> $@; \
	done

tiempos_ej3.dat: ejercicio3
	for (( i=$(inicio_ej3); i < $(fin_ej3); i*=$(factor) )); do \
		cmd="./$< $$i 10000"; \
		echo -en "\r$$cmd"; \
		$$cmd >> $@; \
	done
