#ifndef BL_H
#define BL_H
#include "apc.h"

/**
 * @brief Genera la solucion inicial mediante la funcion random
 * @param pesos los pesos a inicializar, es de salida
 * @param numCaracteristicas el numero de caracteristicas del dataset
*/
void generaSolucionInicial(std::vector<double> &pesos, int numCaracteristicas);
/**
 * @brief Genera y mezcla los indices dado un tamaño
 * @param size el tamaño del vector de indices
 * @return el vector de indices mezclado
*/
std::vector<int> mezclarIndices(int size);

/**
 * @brief Función que implementa el algoritmo de búsqueda local.
 * @param train Dataset de entrenamiento.
 * @return Vector de pesos maximizados a la función objetivo.
 */
double busquedaLocal(const Dataset &train, std::vector<double> &Sact, int &iter, int maxiter);

#endif