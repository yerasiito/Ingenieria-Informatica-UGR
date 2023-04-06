#include <algorithm>
#include "acp.h"
#include "funcionesAux.h"

// Función para actualizar los pesos de las características
void Greedy::actualizar_pesos(const Ejemplo& inst, const Dataset& dataset, std::vector<double>& weights) {
    double amigo_dist = INFINITY;
    double enemigo_dist = INFINITY;
    int amigo_idx, enemigo_idx;

    for (int i = 0; i < dataset.numEjemplos(); i++) {
        double dist = distancia(inst, dataset.getEjemplo(i));
        if (inst.etiqueta == dataset.getEtiqueta(i)) { //Amigo
            if (dist < amigo_dist && dist > 0.0) {
                amigo_dist = dist;
                amigo_idx = i;
            }
        } else { //Enemigo
            if (dist < enemigo_dist) {
                enemigo_dist = dist;
                enemigo_idx = i;
            }
        }
    }

    for (int i = 0; i < weights.size(); i++) {
        weights[i] += fabs(inst.caracteristicas[i] - dataset.getCaracteristica(enemigo_idx, i)) - 
                      fabs(inst.caracteristicas[i] - dataset.getCaracteristica(amigo_idx, i));
    }
}

// Función principal para ejecutar el algoritmo Greedy Relief
std::vector<double> Greedy::greedy_relief(const Dataset &dataset) {
    std::vector<double> weights(dataset.numCaracteristicas());
    for (int i = 0; i < dataset.numEjemplos(); i++) {
        Ejemplo inst = dataset.getEjemplo(i);
        actualizar_pesos(inst, dataset, weights);
    }
    double w_max = *max_element(weights.begin(), weights.end());
    for(int i = 0; i < weights.size();i++){
        if(weights[i] < 0){
            weights[i] = 0;
        }
        else{
            weights[i] /= w_max;
        }
    }
    return weights;
}

int Clasificador::unoNN(Ejemplo test_ejemplo, Dataset training_set) {
    int min_index = 0;
    double min_distance = INFINITY;

    for (int i = 0; i < training_set.numEjemplos(); i++) {
        double distance = distancia(test_ejemplo, training_set.getEjemplo(i));
        if (distance < min_distance && distance != 0) {
            min_index = i;
            min_distance = distance;
        }
    }
    return training_set.getEjemplo(min_index).etiqueta;
}

int Clasificador::unoNNponderado(Ejemplo test_ejemplo, Dataset training_set, std::vector<double> w) {
    int min_index = 0;
    double min_distance = INFINITY;

    for (int i = 0; i < training_set.numEjemplos(); i++) {
        double distance = distanciaPonderada(test_ejemplo, training_set.getEjemplo(i), w);
        if (distance < min_distance && distance > 0) {
            min_index = i;
            min_distance = distance;
        }
    }
    return training_set.getEjemplo(min_index).etiqueta;
}