#include "funcionesAux.h"

double distancia(const Ejemplo& a, const Ejemplo& b) {
    double dist = 0;
    for (int i = 0; i < a.caracteristicas.size(); i++) {
        dist += pow(a.caracteristicas[i] - b.caracteristicas[i], 2);
    }
    return sqrt(dist);
}

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
