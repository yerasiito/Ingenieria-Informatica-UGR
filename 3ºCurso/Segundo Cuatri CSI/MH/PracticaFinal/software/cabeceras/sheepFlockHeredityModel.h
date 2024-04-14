#ifndef SHEEPFLOCKHEREDITYMODEL_H
#define SHEEPFLOCKHEREDITYMODEL_H

#include <vector>
#include "dataset.h"
#include "apc.h"
#include "poblacion.h"

/**
 * @brief Obtiene un indice de inviduo de la poblacion sin repetir. Autogenera indices si esta vacio
 * @param pop Poblacion
 * @param indices Indices de donde se obtiene el nuevo indice. Se actualizan cuando esta vacio
 * @param idx Indice que devuelve
 * @return el individuo de la poblacion en el indice obtenido
 */
std::vector<double> getFromIndex(const Poblacion &pop, std::vector<int> &indices, int &idx);

/**
 * @brief Cruce subcromosoma. Usa el numero de ovejas y tamaño para cruzarse eficientemente
 * @param padre Cromosoma o peso
 * @param numOvejas numero de subcromosomas
 * @param sizeOvejas tamanio de cada subcromosoma
 */
void cruceSPX(std::vector<double> &padre, int numOvejas, int sizeOvejas);

/**
 * @brief Cruce romosoma. Se intercambian padres entre si
 * @param padre1 Cromosoma o peso
 * @param padre2 Cromosoma o peso
 */
void cruceSPX(std::vector<double> &padre1, std::vector<double> &padre2);

/**
 * @brief Heuristica R-R. Utiliza el fitness medio para reemplazar cromosomas por debajo de la media
 * @param paret Cromosoma a evaluar
 * @param train Datos para evaluar
 * @param meanFitness Fitness medio de la poblacion actual
 * @note Sin usar debido a una alta inestabilidad en los resultados
 */
void robust_replace(std::pair<std::vector<double>, double> &parent, const Dataset &train, double meanFitness);

// Implementada en la practica previa. Se encuentra en apc.h
///**
// * @brief Mutacion de punto. Modifica el valor aleatoriamente en un punto
// * @param w Vector de pesos
// * @param i Indice a mutar
// * @param varianza coeficiente de varianza para el valor de mutacion
// */
//void Mov(vector<double> &w, const int &i, const double &varianza);

/**
 * @brief Mutacion inversa. Dadas dos posiciones aleatorias, intercambian valores hasta invertirse
 * @param w Vector de pesos
 */
void inverseMov(std::vector<double> &w);

/**
 * @brief Nuevo algoritmo genetico de rebanio de ovejas
 * @param train datos de entrenamiento para evaluar
 * @param maxIters criterio de parada
 * @param operador Usa operador SPX
 * @return el peso con mejor fitness
 */
std::vector<double> SFHMA(const Dataset &train, int maxIters, const std::string& operador);

/**
 * @brief Nuevo algoritmo genetico de rebanio de ovejas MEJORADO con Busqueda Local
 * @param train datos de entrenamiento para evaluar
 * @param maxIters criterio de parada
 * @param operador Usa operador SPX
 * @return el peso con mejor fitness
 */
std::vector<double> SFHMA_hibrido(const Dataset &train, int maxIters, const std::string& operador);

#endif //SHEEPFLOCKHEREDITYMODEL_H
