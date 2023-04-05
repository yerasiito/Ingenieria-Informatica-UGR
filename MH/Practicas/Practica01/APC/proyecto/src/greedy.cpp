#include <algorithm>
#include "greedy.h"
#include "funcionesAux.h"

// Función para calcular la distancia euclidiana entre dos instancias

// Función para actualizar los pesos de las características
void Greedy::actualizar_pesos(const Ejemplo& inst, Dataset& dataset, std::vector<double>& weights) {
    double amigo_dist = INFINITY;
    double enemigo_dist = INFINITY;
    int amigo_idx, enemigo_idx;

    for (int i = 0; i < dataset.numEjemplos(); i++) {
        if (inst.etiqueta == dataset.getEtiqueta(i)) {
            double dist = distancia(inst, dataset.getEjemplo(i));
            if (dist < amigo_dist) {
                amigo_dist = dist;
                amigo_idx = i;
            }
        } else {
            double dist = distancia(inst, dataset.getEjemplo(i));
            if (dist < enemigo_dist) {
                enemigo_dist = dist;
                enemigo_idx = i;
            }
        }
    }

    for (int i = 0; i < inst.caracteristicas.size(); i++) {
        weights[i] += abs(inst.caracteristicas[i] - dataset.getCaracteristica(amigo_idx, i) - 
                        abs(inst.caracteristicas[i] - dataset.getCaracteristica(enemigo_idx, i)));
    }
}

// Función para seleccionar las k características con los pesos más altos
std::vector<int> Greedy::select_features(const std::vector<double>& weights, int k) {
    std::vector<int> indices(weights.size());
    for (int i = 0; i < weights.size(); i++) {
        indices[i] = i;
    }

    std::sort(indices.begin(), indices.end(), [&](int a, int b) {
        return weights[a] > weights[b];
    });

    return std::vector<int>(indices.begin(), indices.begin() + k);
}

// Función principal para ejecutar el algoritmo Greedy Relief
std::vector<double> Greedy::greedy_relief(Dataset &dataset) {
    std::vector<double> weights(dataset.numCaracteristicas());
    for (int i = 0; i < dataset.numEjemplos(); i++) {
        Ejemplo inst = dataset.getEjemplo(i);
        actualizar_pesos(inst, dataset, weights);
    }
    double w_max = *max_element(weights.begin(), weights.end());
    for(int i = 0; i < weights.size();i++){
        if(weights[i] < 0)
            weights[i] = 0;
        else{
            weights[i] /= w_max;
        }
    }
    return weights;
    //select_features(weights, k);
}
