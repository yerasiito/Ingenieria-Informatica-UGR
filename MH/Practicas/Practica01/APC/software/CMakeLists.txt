# Establece la versión mínima requerida de CMake
cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_FLAGS "-O2 -march=native -funroll-loops")
# Establece el nombre del proyecto
project(practica1)

# Agrega los archivos de origen
add_executable(practica1 
  fuentes/main.cpp 
  fuentes/dataset.cpp 
  fuentes/apc.cpp
  fuentes/funcionesAux.cpp
)

# Agrega los archivos de encabezado
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cabeceras)
