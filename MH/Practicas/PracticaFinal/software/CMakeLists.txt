# Establece la versión mínima requerida de CMake
cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_FLAGS "-O2")
# Establece el nombre del proyecto
project(practica2)

# Agrega los archivos de origen
add_executable(practica2
  fuentes/main.cpp 
  fuentes/dataset.cpp 
  fuentes/apc.cpp
  fuentes/funcionesAux.cpp
  fuentes/algoritmosGeneticos.cpp
  fuentes/busquedaLocal.cpp
  fuentes/sheepFlockHeredityModel.cpp
  fuentes/poblacion.cpp)

# Agrega los archivos de encabezado
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cabeceras)
