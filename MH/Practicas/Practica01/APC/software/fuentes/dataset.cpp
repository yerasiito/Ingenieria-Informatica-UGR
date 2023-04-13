#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>

#include "dataset.h"
using namespace std;

//Metodo de lectura
int Dataset::read(ifstream &f){

    string info, linea;
    bool is_data = false;

    //Devolver error si no puede abrirlo
    if (!f.is_open()) {
        return EXIT_FAILURE;
    }
    
    // Ignora la cabecera hasta encontrar @data
    while(!is_data){
        getline(f, info, '\n');
        if(info == "@data")
            is_data = true;
        info = "";
    }

    //Lee la matriz de datos
    while (getline(f, linea)){
        Ejemplo e;

        // Lee la línea de datos
        istringstream fila_ss(linea); 

        string value_str;
        bool excepcion = false;

        // Leer cada valor en la línea
        while (getline(fila_ss, value_str, ',')) { 

            // Evalua si el valor es numérico, en otro caso lo mete como etiqueta
            try {
                double value = stof(value_str); // Convertir la cadena a un número entero
                e.caracteristicas.push_back(value);
            } catch (const exception&) { // Si salta es que el valor no es numérico y debe ser la etiqueta
                e.etiqueta = value_str;
                excepcion = true;
            }
        }

        // Mete la ultima columna como etiqueta y la saca de los datos
        if(!excepcion){ 
            e.etiqueta = e.caracteristicas.back();
            e.caracteristicas.pop_back();
        }

        insertEjemplo(e);
    }

    f.close();

    return EXIT_SUCCESS;
}

//Métodos get
Ejemplo &Dataset::getEjemplo(int i){
    return ejemplos[i];
}

const Ejemplo &Dataset::getEjemplo(int i) const{
    return ejemplos[i];
}

int Dataset::numEjemplos() const{
    return ejemplos.size();
}

int Dataset::numCaracteristicas() const{
    return ejemplos[0].caracteristicas.size();
}

int Dataset::numEtiquetas() const{
    return labelNames.size();
}

double &Dataset::getCaracteristica(int i, int j){
    return ejemplos[i].caracteristicas[j];
}

double Dataset::getCaracteristica(int i, int j) const{
    return ejemplos[i].caracteristicas[j];
}

const string &Dataset::getEtiqueta(int i) const{
    return ejemplos[i].etiqueta;
}

const string &Dataset::getLabelName(int i) const {
    return labelNames[i];
}

//Método set
void Dataset::setCaracteristica(int i, int j, double valor){
    getCaracteristica(i,j) = valor;
}

//Método insert
void Dataset::insertEjemplo(Ejemplo e){
    ejemplos.push_back(e);
}

//Metodos print
void Dataset::dataPrint(){
    // Imprime los datos de cada ejemplo y su etiqueta
    for(int i = 0; i < numEjemplos(); i++){
        getEjemplo(i).imprimirCaracteristicas();
        cout << "," << getEjemplo(i).etiqueta;
    }
    cout << endl;
}

void Dataset::dimensionPrint(){
    cout << "Tamaño de matrix: " << numEjemplos() << "x" << numCaracteristicas() << endl;
}

//Método de cómputo 
const Dataset Dataset::leave_one_out(int i) const{ 
    Dataset loo = *this;
    loo.ejemplos.erase(loo.ejemplos.begin() + i);
    return loo;    
}