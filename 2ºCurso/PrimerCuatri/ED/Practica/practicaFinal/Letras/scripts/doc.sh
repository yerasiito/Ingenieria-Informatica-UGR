# 1- Ejecuta el archivo .doxy
doxygen Doxyfile.doxy
# 2- Genera el pdf a partir de los archivos latex
cd doc/latex && make && cd ../..
# 3- Abre la documentacion html en firefox
google-chrome doc/html/index.html &
# 4- Abre el pdf generado por latex. (Mi lector de pdf es Okular)
okular doc/latex/refman.pdf &

