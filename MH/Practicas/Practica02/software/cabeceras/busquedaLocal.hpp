#ifndef BL_H
#define BL_H

#include <iostream>
#include "apc.h"
using namespace std;
using Random = effolkronium::random_static;

/**
 * @brief Funcion objetivo a MAXIMIZAR, maximiza el fitness
 * @param train el dataset de entrenamiento a evaluar
 * @param pesos los valores ponderados para la distancia
 * @return el calculo del fitness
*/
double funObjetivo(Dataset train, vector<double> pesos){
    int aciertos = 0;

    // Clasificar train para obtener aciertos para el fitness
    clasificarTrain(train, pesos, aciertos);
    
    return calcularFitness(aciertos, train.numEjemplos(), pesos);
}

/**
 * @brief Genera la solucion inicial mediante la funcion random
 * @param pesos los pesos a inicializar, es de salida
 * @param numCaracteristicas el numero de caracteristicas del dataset
*/
void generaSolucionInicial(vector<double> &pesos, int numCaracteristicas){
    pesos = Random::get<std::vector>(0.0, 1.0, numCaracteristicas);
}

/**
 * @brief Genera y mezcla los indices dado un tamaño
 * @param size el tamaño del vector de indices
 * @return el vector de indices mezclado
*/
vector<int> mezclarIndices(int size){
    // Definir lista de índices aleatorios
    std::vector<int> indices(size);
    for (int i = 0; i < size; i++) {
        indices[i] = i;
    }
    Random::shuffle(indices);

    return indices;
}

/**
 * @brief Función que implementa el algoritmo de búsqueda local.
 * @param train Dataset de entrenamiento.
 * @return Vector de pesos maximizados a la función objetivo.
 */
vector<double> busquedaLocal(Dataset train){
    int iter = 0, itervecinos = 0;
    int aciertos;
    vector<double> Sact;
    bool mejora = true;

    // Generar vector inicial
    generaSolucionInicial(Sact, train.numCaracteristicas());

    // Calcula objetivo
    double objetivoActual = funObjetivo(train, Sact);

    vector<double> S = Sact;
    double objetivo = 0;

    // Bucle principal del algoritmo
    while(itervecinos < 20*Sact.size() && iter < 15000){
        // Generar índices de vecindario
        vector<int> indices = mezclarIndices(S.size());

        mejora = false;

        // Bucle para generar vecinos
        for(int i = 0; !mejora && i < indices.size(); i++){
            // Generar vecino
            Mov(S,indices[i],0.8);

            // Calcular objetivo tras mutacion
            objetivo = funObjetivo(train, S);

            // Comprobar si se ha mejorado la solución
            if(objetivo > objetivoActual){
                itervecinos = 0;
                objetivoActual = objetivo;
                Sact = S;
                mejora = true;
            }
            else
                S = Sact;
                
            itervecinos++;
        }
        iter++;
    }

    // Devolver la solución encontrada
    return Sact;
}


#endif