#ifndef FUNCIONES_AUX_H
#define FUNCIONES_AUX_H

#include "dataset.h"

/**
 * @brief lee los ficheros
 * @param fichero el tipo de datos a leer, puede ser: diabetes, ozono, spectf-heart
 * @param train el conjunto de datos de entrenamiento
 * @param test conjunto de datos de test
 * @param k el indice de particion (el numero indica el test)
*/
int leerFicheros(std::string fichero, Dataset &train, Dataset &test, int k);

/**
 * @brief Función para calcular la distancia euclidiana ponderada entre dos instancias
 * @param a instancia primera
 * @param b instancia segunda
 * @param w los pesos ponderados
 * @return la distancia euclidiana ponderada entre ambas instancias
*/
double distancia(const Ejemplo& a, const Ejemplo& b, std::vector<double> w);

/**
 * @brief Función para normalizar los datos de entrenamiento y test
 * @param train el dataset de train a normalizar, es de salida
 * @param test el dataset de test a normalizar, es de salida
*/
void normalizar(Dataset &train, Dataset &test);

#endif