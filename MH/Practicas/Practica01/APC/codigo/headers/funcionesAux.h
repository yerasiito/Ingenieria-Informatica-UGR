#ifndef FUNCIONES_AUX_H
#define FUNCIONES_AUX_H

#include "dataset.h"
#include <vector>

/**
 * @brief Función para calcular la distancia euclidiana entre dos instancias
 * @param a instancia primera
 * @param b instancia segunda
 * @return la distancia euclidiana entre ambas instancias
*/
double distancia(const Ejemplo& a, const Ejemplo& b);

/**
 * @brief Función para calcular la distancia euclidiana ponderada entre dos instancias
 * @param a instancia primera
 * @param b instancia segunda
 * @param w los pesos ponderados
 * @return la distancia euclidiana ponderada entre ambas instancias
*/
double distanciaPonderada(const Ejemplo& a, const Ejemplo& b, std::vector<double> w);

/**
 * @brief Funcion para calcular la tasa de reduccion
 * @param pesos los pesos del cual se calcula la tasa
 * @return la tasa de reduccion
*/
double calcularTasaRed(std::vector<double> pesos);


void normalizar(Dataset &train, Dataset &test);

#endif