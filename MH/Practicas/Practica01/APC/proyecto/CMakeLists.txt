# Establece la versión mínima requerida de CMake
cmake_minimum_required(VERSION 3.16)

# Establece el nombre del proyecto
project(mi_proyecto)

# Agrega los archivos de origen
add_executable(mi_ejecutable 
  src/main.cpp 
  src/dataset.cpp 
  src/greedy.cpp
  src/funcionesAux.cpp
)

# Agrega los archivos de encabezado
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/headers)