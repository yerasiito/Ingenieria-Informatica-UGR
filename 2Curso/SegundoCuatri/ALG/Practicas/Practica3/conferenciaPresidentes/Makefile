CPP=$(wildcard *.cpp)
EXE=$(basename $(CPP))

# Modifica aquí para ajustar el nivel de optimización (de 0 a 3):
CPPFLAGS=-O0 -std=gnu++0x
DAT=conferenciaTiempos.dat

.PHONY: default clean tiempos

default: $(EXE)

clean:
	rm -f $(EXE) $(DAT)

# Modifica aquí para cambiar los puntos de inicio, fin y los saltos:
ini=100
fin=2000
incremento=100

tiempos: $(DAT)

all_tiempos: $(ALL_DAT)

# Calculo de tiempos. NO MODIFICAR
.SILENT:
conferenciaTiempos.dat: conferenciaTiempos
	for (( i=$(ini); i <= $(fin); i+=$(incremento) )); do \
		cmd="./$< $$i"; \
		echo -en "\r$$cmd"; \
		$$cmd >> $@; \
	done

