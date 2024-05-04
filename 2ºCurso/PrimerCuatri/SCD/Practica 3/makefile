##FUNCIONAMENTO DEL MAKEFILE
##Compilar: nombre del archivo + _mpi_exe. Por ejemplo: make prodcons_mpi_exe te compila prodcons.cpp
##Ejecutar: aliases descritos debajo. Por ejemplo: make pcauto te compila prodcons_automat.cpp y te lo ejecuta

.SUFFIXES:
.PHONY:    pc,pc2,pcm,fp,f,fi,fc,clean

compilador := mpicxx 
flagsc     := -std=c++11 -g
NoCuda := --mca opal_warn_on_missing_libcuda 0

pc: prodcons_mpi_exe
	mpirun -oversubscribe -np  3 ./$< $(NoCuda)

pc2: prodcons2_mpi_exe
	mpirun -oversubscribe  -np  3 ./$< $(NoCuda)

pcnm: prodcons-nmu_mpi_exe
	mpirun -oversubscribe  -np  11 ./$< $(NoCuda)

pcauto: prodconsAutomat_mpi_exe
	mpirun -oversubscribe  -np  10 ./$< $(NoCuda)
	
fp: filosofos-plantilla_mpi_exe 
	mpirun -oversubscribe  -np 10 ./$< $(NoCuda)

%_mpi_exe: %.cpp
	$(compilador) $(flagsc) -o $@ $<

clean:
	rm -rf *_exe *.dSYM
