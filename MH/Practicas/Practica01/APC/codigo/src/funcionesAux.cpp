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
