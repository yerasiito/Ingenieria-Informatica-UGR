#ifndef ACP_H
#define ACP_H
#include "dataset.h"

struct Clasificador{
    /**
     * @brief predice una etiqueta de un ejemplo a partir de un dataset dado a partir de unos pesos ponderados
     * @param test_ejemplo es el ejemplo cuya etiqueta queremos predecir
     * @param training_set es el conjunto de datos del cual predeciremos
     * @param w son los pesos a aplicar a las distancias
     * @return la etiqueta predicha para el ejemplo
    */
    std::string unoNN(Ejemplo test_ejemplo, Dataset training_set, std::vector<double> w);
};

struct Greedy{
    /**
     * @brief Funcion para actualizar los pesos de las características
     * @param inst ejemplo del cual actualizaremos el peso
     * @param dataset el conjunto de datos a predecir
     * @param weights son los pesos que se obtienen de salida
    */
    void actualizar_pesos(const Ejemplo& inst, const Dataset& dataset, std::vector<double>& weights);

    // Función para seleccionar las k características con los pesos más altos
    // std::vector<int> select_features(const std::vector<double>& weights, int k);

    /**
     * @brief Función principal para ejecutar el algoritmo Greedy Relief
     * @param dataset el conjunto de datos cuyos pesos queremos obtener
     * @return un vector de pesos para optimizar las distancias del dataset
    */
    std::vector<double> greedy_relief(const Dataset &dataset);
};

#endif