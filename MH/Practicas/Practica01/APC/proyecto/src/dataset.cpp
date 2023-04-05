#include <iostream>
#include <sstream>
#include <algorithm>
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

const int Dataset::numEjemplos(){
    return ejemplos.size();
}

const int Dataset::numCaracteristicas(){
    return ejemplos[0].caracteristicas.size();
}

const int Dataset::numEtiquetas(){
    return labelNames.size();
}

const double Dataset::getCaracteristica(int i, int j){
    return ejemplos[i].caracteristicas[j];
}

const int &Dataset::getEtiqueta(int i){
    return ejemplos[i].etiqueta;
}

const string &Dataset::getLabelName(int i){
    return labelNames[i];
}

//Métodos set
void Dataset::insertEjemplo(Ejemplo e){
    ejemplos.push_back(e);
}

Dataset Dataset::normalizar(){
    Dataset ds_normalizado = *this;

    //Para cada ejemplo recorremos cada atributo
    double car = 0;
    double min_car = INFINITY, max_car = -INFINITY;
    
    vector<double> min_atrib = {}, max_atrib = {};

    for(int j = 0; j < numCaracteristicas(); j++){
        //Para cada atributo buscamos su minimo y maximo
        for(int i = 0; i < numEjemplos(); i++){
            car = ejemplos[i].caracteristicas[j];
            if(car > max_car)
                max_car = car;

            if(car < min_car)
                min_car = car;
        }
        min_atrib.push_back(min_car);
        max_atrib.push_back(max_car);
    }

    //Normaliza el dataset
    for(int i = 0; i < numEjemplos(); i++){
        Ejemplo &e = ds_normalizado.getEjemplo(i);
        for(int j = 0; j < max_atrib.size(); j++){ //Aplicamos la formula
            e.caracteristicas[j] = (e.caracteristicas[j] - min_atrib[j])/(max_atrib[j] - min_atrib[j]);
        }
    }

    return ds_normalizado;
}

void Dataset::dataPrint(){
    for(int i = 0; i < numEjemplos(); i++){
        cout << endl;
        for(int j = 0; j < numCaracteristicas(); j++)
            cout << getCaracteristica(i,j) << " ";
        cout << getEtiqueta(i);
    }
    cout << endl;
}

void Dataset::dimensionPrint(){
    cout << "Tamaño de matrix: " << numEjemplos() << "x" << numCaracteristicas() << endl;
}