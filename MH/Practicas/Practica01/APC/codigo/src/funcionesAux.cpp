#include "funcionesAux.h"

// Función para calcular la distancia euclidiana entre dos instancias
double distancia(const Ejemplo& a, const Ejemplo& b) {
    double dist = 0;
    for (int i = 0; i < a.caracteristicas.size(); i++) {
        dist += pow(a.caracteristicas[i] - b.caracteristicas[i], 2);
    }
    return sqrt(dist);
}

// Función para calcular la distancia euclidiana ponderada entre dos instancias
double distanciaPonderada(const Ejemplo& a, const Ejemplo& b, std::vector<double> w) {
    double dist = 0;
    for (int i = 0; i < a.caracteristicas.size(); i++) {
        if(w[i] < 0.1){
            continue;
        }
        dist += w[i]*pow(a.caracteristicas[i] - b.caracteristicas[i], 2);
    }
    return sqrt(dist);
}

// Funcion para calcular la tasa de reduccion de los pesos
double calcularTasaRed(std::vector<double> pesos){
    double tasa_red = 0;
    for(auto it : pesos)
        if(it < 0.1)
            tasa_red++;
    return tasa_red = 100*(tasa_red/pesos.size());
}

void normalizar(Dataset &train, Dataset &test){
    //Para cada ejemplo recorremos cada atributo
    double car = 0;
    std::vector<double> min_atrib = {}, max_atrib = {};

    for(int j = 0; j < train.numCaracteristicas(); j++){
        double min_car = INFINITY, max_car = -INFINITY;
        //Para cada atributo de train buscamos su minimo y maximo
        for(int i = 0; i < train.numEjemplos(); i++){
            car = train.getCaracteristica(i,j);
            if(car > max_car)
                max_car = car;

            if(car < min_car)
                min_car = car;
        }
        //Para cada atributo de test buscamos su minimo y maximo
        for(int i = 0; i < test.numEjemplos(); i++){
            car = test.getCaracteristica(i,j);
            if(car > max_car)
                max_car = car;

            if(car < min_car)
                min_car = car;
        }
        min_atrib.push_back(min_car);
        max_atrib.push_back(max_car);
    }
    //Normaliza el dataset de train
    for(int i = 0; i < train.numEjemplos(); i++){
        for(int j = 0; j < max_atrib.size(); j++){ //Aplicamos la formula
            train.getEjemplo(i).caracteristicas[j] = (train.getCaracteristica(i,j) - min_atrib[j])/(max_atrib[j] - min_atrib[j]);
        }
    }

    //Normaliza el dataset de test
    for(int i = 0; i < test.numEjemplos(); i++){
        for(int j = 0; j < max_atrib.size(); j++){ //Aplicamos la formula
            test.getEjemplo(i).caracteristicas[j] = (test.getCaracteristica(i,j) - min_atrib[j])/(max_atrib[j] - min_atrib[j]);
        }
    }
}