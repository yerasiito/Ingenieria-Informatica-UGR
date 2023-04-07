#ifndef ACP_H
#define ACP_H
#include "dataset.h"
#include <chrono>

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

/**
 * @brief Función principal de clasificacion de los dataset de train y test
 * @param train el dataset de train a clasificar
 * @param test el dataset de test a clasificar
 * @param pesos el vector de pesos ponderados, si greedy ni bl no se ejecutan se inicializan a 1
 * @param acierto_train el acierto de train de salida
 * @param acierto_test el acierto de test de salida
*/
void clasificar(Dataset train, Dataset test, std::vector<double> pesos, int &acierto_train, int &acierto_test);

/**
 * @brief Funcion para calcular la tasa de reduccion
 * @param pesos los pesos del cual se calcula la tasa
 * @return la tasa de reduccion
*/
double calcularTasaRed(std::vector<double> pesos);

/**
 * @brief Función para calcular el rendimiento de los algoritmos tras clasificar con 1nn
 * @param acierto_train el número de aciertos en train
 * @param acierto_test el número de acierto en test
 * @param train el dataset de entrenamiento
 * @param test el dataset de test
 * @param w el vector de pesos ponderados obtenido por greedy o bl
 * @param momentoInicio el tiempo de inicio del algoritmo
 * @return el vector con el rendimiento: tasa_clas_train, tasa_clas_test, tasa_red, fitness, tiempo
*/
std::vector<double> calcularRendimiento(int acierto_train, int acierto_test, Dataset train, Dataset test, 
    std::vector<double> w, std::chrono::high_resolution_clock::time_point momentoInicio);

/**
 * @brief Imprime la tabla de rendmiento
 * @param resultados la matriz de resultados calculada por calcularRendimiento
*/
void imprimeRendimiento(std::vector<std::vector<double>> resultados);

/**
 * @brief Imprime los pasos de cada particion
 * @param pesosT matriz con todos los pasos de cada particion
*/
void imprimePesos(std::vector<std::vector<double>> pesosP);

/**
 * @brief Imprime el peso medio
 * @param pesosT el vector de pesos sumados de todas las particiones
*/
void imprimePesoMedio(std::vector<double> pesosT);

#endif