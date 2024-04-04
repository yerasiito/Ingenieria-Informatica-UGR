cmake_minimum_required(VERSION 2.8)

project(Motor_Grafico_Belkan)

#########################################################
# FIND GLUT
#########################################################
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)

#########################################################
# FIND OPENGL
#########################################################
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

#########################################################
# FIND OPENMP
#########################################################
find_package(OpenMP REQUIRED)
include_directories(${OpenMP_INCLUDE_DIRS})
link_directories(${OpenMP_LIBRARY_DIRS})
add_definitions(${OpenMP_DEFINITIONS})
if(NOT OPENMP_FOUND)
    message(ERROR " OPENMP not found!")
endif(NOT OPENMP_FOUND)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")

#########################################################
# FIND LIBJPEG
#########################################################
find_package(JPEG REQUIRED)
include_directories(${JPEG_INCLUDE_DIRS})
link_directories(${JPEG_LIBRARY_DIRS})
add_definitions(${JPEG_DEFINITIONS})
if(NOT JPEG_FOUND)
    message(ERROR " JPEG not found!")
endif(NOT JPEG_FOUND)


#########################################################
# Source code...
#########################################################
file(GLOB SOURCES "src/*.cpp" "src/*.cxx" "src/*.cc")
file(GLOB SOURCES_LIB3D "src/obj3dlib/*.cpp" "src/obj3dlib/*.cxx" "src/obj3dlib/*.cc" "src/obj3dlib/*/*.cpp" "src/obj3dlib/*/*.cxx" "src/obj3dlib/*/*.cc")
file(GLOB SOURCES_LIBMOTOR "src/motorlib/*.cpp" "src/motorlib/*.cxx" "src/motorlib/*.cc")
file(GLOB SOURCES_MODELOS "src/modelos/*/*.cpp" "src/modelos/*/*.cxx" "src/modelos/*.cc" "src/modelos/*.cpp" "src/modelos/*.cxx" "src/modelos/*.cc")
file(GLOB SOURCES_GLUI "src/glui/*.cpp" "src/glui/*.cxx" "src/glui/*.cc")
file(GLOB SOURCES_COMPORTAMIENTOS "src/comportamientos/*.cpp" "src/comportamientos/*.cxx" "src/comportamientos/*.cc" "Comportamientos_Jugador/*.cpp")
include_directories("include")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11 -lglut")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

########################################################
# Compiling & stuff
#########################################################
add_library(obj3DLib ${SOURCES_LIB3D})
target_link_libraries(obj3DLib ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${JPEG_LIBRARIES} "-lpthread")

add_library(GLUILib ${SOURCES_GLUI})
target_link_libraries(GLUILib ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

add_library(modelosBelkanLib ${SOURCES_MODELOS})
target_link_libraries(modelosBelkanLib obj3DLib ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${OPENMP_LIBRARIES} "-lpthread")

add_library(comportamientosLib ${SOURCES_COMPORTAMIENTOS})
target_link_libraries(comportamientosLib ${OPENMP_LIBRARIES} "-lpthread")

add_library(motorLib ${SOURCES_LIBMOTOR})
target_link_libraries(motorLib obj3DLib GLUILib comportamientosLib ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${OPENMP_LIBRARIES} "-lpthread")

add_executable(practica2 "bin_src/juego.cc" ${SOURCES})
target_link_libraries(practica2 obj3DLib motorLib modelosBelkanLib ${OPENMP_LIBRARIES} "-lpthread")

add_executable(practica2SG "bin_src/juegoSG.cc" ${SOURCES})
target_link_libraries(practica2SG   obj3DLib motorLib modelosBelkanLib ${OPENMP_LIBRARIES} "-lpthread")
