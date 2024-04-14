#ifndef APC_H
#define APC_H

#include <chrono>
#include "funcionesAux.h"
/**************************************CLASIFICADOR**************************************/

/**
 * @brief predice una etiqueta de un ejemplo a partir de un dataset dado a partir de unos pesos ponderados
 * @param test_ejemplo es el ejemplo cuya etiqueta queremos predecir
 * @param training_set es el conjunto de datos del cual predeciremos
 * @param w son los pesos a aplicar a las distancias
 * @return la etiqueta predicha para el ejemplo
 */
std::string clasificador1NN(const Dataset &train, const Ejemplo &test_ejemplo, const std::vector<double> &w, int leave_out=-1);
/***********************************ALGORITMO DE GREEDY***********************************/
/**
 * @brief Funcion para actualizar los pesos de las características
 * @param inst ejemplo del cual actualizaremos el peso
 * @param dataset el conjunto de datos a predecir
 * @param weights son los pesos que se obtienen de salida
 */
void actualizar_pesos(const Ejemplo &inst, const Dataset &dataset, std::vector<double> &weights, const int &leave_out=-1);

// Función para seleccionar las k características con los pesos más altos
// std::vector<int> select_features(const std::vector<double>& weights, int k);

/**
 * @brief Función principal para ejecutar el algoritmo Greedy Relief
 * @param dataset el conjunto de datos cuyos pesos queremos obtener
 * @return un vector de pesos para optimizar las distancias del dataset
 */
std::vector<double> greedy_relief(const Dataset &dataset);

/**************************************CLASIFICAR**************************************/

/**
 * @brief Funcion para calcular los aciertos en train. Aplica leave one out
 * @param train el dataset de entrenamiento
 * @param pesos los pesos ponderados aplicados a la distancia
 * @param acierto_train el numero de aciertos al clasificar, variable de salida
 */
void clasificarTrain(const Dataset &train, const std::vector<double> &pesos, int &acierto_train);

/**
 * @brief Funcion para calcular los aciertos en test
 * @param train el dataset de entrenamiento
 * @param test el dataset de test
 * @param pesos los pesos ponderados aplicados a la distancia
 * @param acierto_test el numero de aciertos al clasificar, variable de salida
 */
void clasificarTest(const Dataset &train, const Dataset &test, const std::vector<double> &pesos, int &acierto_test);

/**
 * @brief Función principal de clasificacion de los dataset de train y test
 * @param train el dataset de train a clasificar
 * @param test el dataset de test a clasificar
 * @param pesos el vector de pesos ponderados, si greedy ni bl no se ejecutan se inicializan a 1
 * @param acierto_train el acierto de train de salida
 * @param acierto_test el acierto de test de salida
 * @param tasa_train un booleano para determinar si calcular o no el tasa train, por defecto false
 */
void clasificar(const Dataset &train, const Dataset &test, const std::vector<double> &pesos, int &acierto_train,
                int &acierto_test, bool tasa_train = false);

/***************************************RENDIMIENTO***************************************/

/**
 * @brief Funcion para calcular la tasa de reduccion
 * @param pesos los pesos del cual se calcula la tasa
 * @return la tasa de reduccion
 */
double calcularTasaRed(const std::vector<double> &pesos);

/**
 * @brief Funcion para calcular el accuracy de un algoritmo
 * @param acierto el numero de aciertos
 * @param numEjemplos el numero de ejmplos del dataset
 * @param pesos los pesos ponderados
 * @return el valor de fitness en funcion de los parámetros dados
 */
double calcularFitness(const int &acierto, const int &numEjemplos, const std::vector<double> &pesos);

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
std::vector<double> calcularRendimiento(int acierto_train, int acierto_test, const Dataset &train, const Dataset &test,
                                        const std::vector<double> &w,
                                        std::chrono::high_resolution_clock::time_point momentoInicio);

/**
 * @brief Imprime la tabla de rendmiento
 * @param resultados la matriz de resultados calculada por calcularRendimiento
 */
void imprimeRendimiento(int i, const std::vector<double> &resultados, std::vector<double> &mediaResultados);

/***************************************PESOS***************************************/

/**
 * @brief Funcion objetivo a MAXIMIZAR, maximiza el fitness
 * @param train el dataset de entrenamiento a evaluar
 * @param pesos los valores ponderados para la distancia
 * @return el calculo del fitness
*/
double funObjetivo(const Dataset &train, const std::vector<double> &pesos);

/**
 * @brief Funcion de mutacion para generar vecinos
 * @param w los pesos a mutar
 * @param i el indice a mutar
 * @param varianza la varianza de la distribucion normal
*/
void Mov(std::vector<double> &w, const int &i, const double &varianza);

/**
 * @brief Imprime los pasos de cada particion
 * @param pesosT matriz con todos los pasos de cada particion
 */
void imprimePesos(const std::vector<std::vector<double>> &pesosP);

/**
 * @brief Imprime el peso medio
 * @param pesosT el vector de pesos sumados de todas las particiones
 */
void imprimeResultadosMedios(const std::vector<double> &resultadosMedios, std::vector<double> &pesosT, int n);

#endif