# 1- Ejecuta el archivo .doxy
doxygen Doxyfile.doxy
# 2- Genera el pdf a partir de los archivos latex
cd doc/latex && make -s && cd ../..

