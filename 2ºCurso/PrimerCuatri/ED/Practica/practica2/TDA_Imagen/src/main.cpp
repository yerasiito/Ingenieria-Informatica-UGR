/*
 * @file main.cpp
 * @brief Archivo main para ejecutar con cualquier imagen dentro del dir $PATH
 * @author Yeray Lopez Ramirez
 * @author Jaime Castillo Ucles
*/

#include <iostream>
#include "imagenES.h"
#include "imagen.h"

using namespace std;

int main (int argc, char *argv[]){
	int id;
    const string DIR_IMAGENES = "../imagenes/";

    string auxE = DIR_IMAGENES;
    string fich1;
    cout << "Escribe el nombre de un fichero dentro del $PATH =" << DIR_IMAGENES << endl
         << "vacas.pgm, cameraman.pgm, celulas.pgm, etc..." << endl << ": ";
    cin >> fich1;

    auxE += fich1; //fusionamos el dir con el archivo
	const char *ficheroEntrada = auxE.c_str();

    cout << "Entrada:  " << ficheroEntrada << endl;
    Imagen img=TransformadorFichImg(ficheroEntrada);
    cout << "El n de filas:" << img.num_filas() << endl;
    cout << "El n de columnas:" << img.num_columnas() << endl;
	
	cout << " Menu de manipulacion de la imagen\n"<<
		"Pulse 1 para crear una imagen umbralizada de la actual\n" <<
		"Pulse 2 para crear un icono a partir de la imagen\n" <<
		"Pulse 3 para aumentar el contraste de la imagen\n" <<
		"Pulse 4 para crear un morphing de la imagen  a partir de otra que se pedirá\n" <<
		"Pulse otra tecla para salir del programa"
		<< endl;
	cin >> id;

	switch(id) {

	case 1: {
        //"crear" archivo de salida(con string es mas facil trabajar)
        string auxS = ficheroEntrada;
        auxS.erase(auxS.find_last_of("."), string::npos); //Quitamos la extension
        auxS += "UMBR.pgm"; //Le añadimos nombre y extension
        const char* ficheroSalida = auxS.c_str();

        //ejecutar el metodo
        cout << "Umbralizando...(Puede tardar segun el archivo. Mala señal si eso pasa...)" << endl;
		umbralizarES(ficheroEntrada, ficheroSalida);
    }
	break;
	case 2: {
		int filas, columnas;
		cout << "Elige las dimensiones de tu icono" << endl;
		cout << "Número de filas" << endl;
		cin >> filas;
		cout << "Número de columnas" << endl;
		cin >> columnas;

        //"crear" archivo de salida(con string es mas facil trabajar)
        string auxS = ficheroEntrada;
        auxS.erase(auxS.find_last_of("."), string::npos); //Quitamos la extension
        auxS += ".ico"; //Le añadimos nombre y extension
        const char* ficheroSalida = auxS.c_str();
        cout << "Iconizando..." << endl;
		iconizarES(ficheroEntrada, ficheroSalida, filas, columnas);
    }
	break;
	case 3: {
        int max, min;
		cout << "Fija un máximo de contraste" << endl;
        cin >> max;
		cout << "Fija un minimo de constraste" << endl;
        cin >> min;

        //"crear" archivo de salida(con string es mas facil trabajar)
        string auxS = ficheroEntrada;
        auxS.erase(auxS.find_last_of("."), string::npos); //Quitamos la extension
        auxS += "CONTRAS.pgm"; //Le añadimos nombre y extension

        const char* ficheroSalida = auxS.c_str();
        cout << "Contrastando..." << endl;
        ContrastarES(ficheroEntrada, ficheroSalida, (::byte) min, (::byte)max);
    }
	break;
	case 4:
    {
        //"crear" archivo de salida(con string es mas facil trabajar)
        string auxS = DIR_IMAGENES;
        string fich2;
        cout << "Introduce el fichero de 'salida' ";
        cin >> fich2;

        auxS += fich2;
        const char *ficheroSalida = auxS.c_str();
        cout << "Salida " << ficheroSalida << endl;
        cout << "Generando Morphing..." << endl;
		MorphingES(ficheroEntrada, ficheroSalida, "../imagenes/Morphing");
    }
    break;
	
	default:
		cout << "El valor introducido no es 1, ni 2, ni 3, ni 4. Intenta de nuevo " << endl;
	}
	
	cout<<"Fin del programa!"<<endl;

}
