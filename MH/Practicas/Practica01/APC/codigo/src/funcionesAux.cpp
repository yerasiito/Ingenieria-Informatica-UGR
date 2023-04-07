#include "funcionesAux.h"

const std::string path = "../Instancias_APC/";

// Funcion para leer todos los ficheros con el nombre dado
int leerFicheros(std::string fichero, Dataset &train, Dataset &test, int k){ 
    if(fichero != "diabetes" && fichero != "ozone-320" && fichero != "spectf-heart"){
        std::cout << "Los parametros admitidos son: diabetes, ozone-320 o spectf-heart\n";
        return EXIT_FAILURE;
    }
    train = {}, test = {};
    for(int i = 1; i <= 5; i++){
        std::string file = path + fichero + "_" + std::to_string(i) + ".arff";
        std::ifstream f(file);
        
        //Lee el fichero y lo integra en el objeto dataset. Si falla entra en el if
        if(i == k+1){
            if(test.read(f)){
                std::cerr << "No se pudo abrir - '"
                    << file << "'" << std::endl;
                return EXIT_FAILURE;
            }
        }
        else if(train.read(f)){
            std::cerr << "No se pudo abrir - '"
                << file << "'" << std::endl;
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

// Función para calcular la distancia euclidiana ponderada entre dos instancias
double distancia(const Ejemplo& a, const Ejemplo& b, std::vector<double> w) {
    double dist = 0;
    for (int i = 0; i < a.caracteristicas.size(); i++) {
        if(w[i] < 0.1){
            continue;
        }
            dist += w[i]*pow(a.caracteristicas[i] - b.caracteristicas[i], 2);
    }
    return sqrt(dist);
}

//Funcion para normalizar el conjunto de train y test
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