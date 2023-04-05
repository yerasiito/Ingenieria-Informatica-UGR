#ifndef GREEDY_H
#define GREEDY_H
#include "dataset.h"

class Greedy{
// Función para calcular la distancia euclidiana entre dos instancias
    public:
        // Función para actualizar los pesos de las características
        void actualizar_pesos(const Ejemplo& inst, Dataset& dataset, std::vector<double>& weights);

        // Función para seleccionar las k características con los pesos más altos
        std::vector<int> select_features(const std::vector<double>& weights, int k);

        // Función principal para ejecutar el algoritmo Greedy Relief
        std::vector<double> greedy_relief(Dataset &dataset);
};

#endif