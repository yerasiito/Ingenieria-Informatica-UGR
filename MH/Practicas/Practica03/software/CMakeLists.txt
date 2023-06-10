# Establece la versión mínima requerida de CMake
cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_FLAGS "-O2")
# Establece el nombre del proyecto
project(practica3)

# Agrega los archivos de origen
add_executable(practica3
  fuentes/main.cpp 
  fuentes/dataset.cpp 
  fuentes/apc.cpp
  fuentes/funcionesAux.cpp
        fuentes/busquedaLocal.cpp
  fuentes/algoritmosTrayectoria.cpp
  fuentes/enfriamientoSimulado.cpp)

# Agrega los archivos de encabezado
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cabeceras)
