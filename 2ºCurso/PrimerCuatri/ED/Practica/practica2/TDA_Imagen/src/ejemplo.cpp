/*
 * @file ejemplo.cpp
 * @brief Archivo de ejemplo/test de TDA IMAGEN
 * @author Yeray Lopez Ramirez
 * @author Jaime Castillo Ucles
*/

#include "imagenES.h"
#include "imagen.h"
#include <iostream>

using namespace std;

int main (int argc, char *argv[]){
    cout << "Umbralizando..." << endl;
    umbralizarES("../imagenes/celulas.pgm","../imagenes/ejer/ejer2.pgm");

    cout << "\nIconizando..." << endl;
    iconizarES("../imagenes/vacas.pgm","../imagenes/ejer/ejer4.pgm",64,64);

    cout << "Contrastando..." << endl;
    ContrastarES("../imagenes/cameraman.pgm","../imagenes/ejer/ejer5.pgm", (byte) 30, (byte) 220);

    cout << "Generando Morphing..." << endl;
    MorphingES("../imagenes/castillo.pgm","../imagenes/cameraman.pgm","../imagenes/ejer/MorphingEjemplo");

    cout << "Programa terminado" << endl;
}
