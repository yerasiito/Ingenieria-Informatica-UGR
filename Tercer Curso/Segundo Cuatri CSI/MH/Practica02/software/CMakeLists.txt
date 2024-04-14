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
  fuentes/busquedaLocal.cpp)

# Agrega los archivos de encabezado
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cabeceras)

# Regla "clean_files" para limpiar el directorio bin de archivos temporales
add_custom_target(clean_files
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/cmake_install.cmake
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/CMakeFiles
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/CMakeCache.txt
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/practica2
)
