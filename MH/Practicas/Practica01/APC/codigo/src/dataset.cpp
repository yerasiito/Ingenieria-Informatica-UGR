#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "dataset.h"
using namespace std;

/**
 * @brief Funcion auxiliar para limpiar los espacios de un string
 * @param str el string a limpiar
 * @return str el mismo string sin espacios en blanco
*/
string limpiarEspacios(string str){
    // Eliminar espacios en blanco al principio del string
    str.erase(str.begin(), find_if(str.begin(), str.end(), [](unsigned char c) {
        return !isspace(c);
    }));

    // Eliminar espacios en blanco al final del string
    str.erase(find_if(str.rbegin(), str.rend(), [](unsigned char c) {
        return !isspace(c);
    }).base(), str.end());

    return str;
}

//Metodos de lectura
int Dataset::read(ifstream &f){
    string info, linea;
    //Devolver error si no puede abrirlo
    if (!f.is_open()) {
        return EXIT_FAILURE;
    }
    
    //Ignora la cabecera hasta encontrar @data
    bool is_data = false;
    while(!is_data){
        getline(f, info, '\n');
        if(info == "@data")
            is_data = true;
        info = "";
    }
    //Lee la matriz de datos
    while (getline(f, linea)){
        Ejemplo e;
        istringstream fila_ss(linea); //Lee la linea de datos
        string value_str;
        bool excepcion = false;
        while (getline(fila_ss, value_str, ',')) { // Leer cada valor en la línea
            //Evalua si el valor es numérico, en otro caso lo mete como etiqueta
            try {
                double value = stof(value_str); // Convertir la cadena a un número entero
                e.caracteristicas.push_back(value);
            } catch (const exception&) { //Si salta es que el valor no es numérico
                value_str = limpiarEspacios(value_str); //Limpia espacios si tiene
                e.etiqueta = etiquetar(value_str);
                excepcion = true;
            }

        }
        if(!excepcion){ //Mete la ultima columna como etiqueta y la saca de los datos
            e.etiqueta = e.caracteristicas.back();
            e.caracteristicas.pop_back();
        }

        insertEjemplo(e);
    }
    f.close();

    return EXIT_SUCCESS;
}

int Dataset::etiquetar(string nombre){
    auto it = find(labelNames.begin(), labelNames.end(), nombre);

    if(it == labelNames.end()){
        labelNames.push_back(nombre);
        it = find(labelNames.begin(), labelNames.end(), nombre);
    }
    int pos = it - labelNames.begin();

    return pos;
}

//Métodos get
Ejemplo &Dataset::getEjemplo(int i){
    return ejemplos[i];
}

const Ejemplo &Dataset::getEjemplo(int i) const{
    return ejemplos[i];
}

const int Dataset::numEjemplos() const{
    return ejemplos.size();
}

const int Dataset::numCaracteristicas() const{
    return ejemplos[0].caracteristicas.size();
}

const int Dataset::numEtiquetas(){
    return labelNames.size();
}

const double Dataset::getCaracteristica(int i, int j) const{
    return ejemplos[i].caracteristicas[j];
}

const int &Dataset::getEtiqueta(int i) const{
    return ejemplos[i].etiqueta;
}

const string &Dataset::getLabelName(int i){
    return labelNames[i];
}

//Métodos set
void Dataset::insertEjemplo(Ejemplo e){
    ejemplos.push_back(e);
}

void Dataset::dataPrint(){
    for(int i = 0; i < numEjemplos(); i++){
        getEjemplo(i).imprimirCaracteristicas();
        cout << "," << getLabelName(getEjemplo(i).etiqueta);
    }
    cout << endl;
}

void Dataset::dimensionPrint(){
    cout << "Tamaño de matrix: " << numEjemplos() << "x" << numCaracteristicas() << endl;
}