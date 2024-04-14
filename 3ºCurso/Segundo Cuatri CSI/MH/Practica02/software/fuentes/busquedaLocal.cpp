#include "apc.h"
#include "busquedaLocal.h"
#include "apc.h"
#include "random.hpp"

using namespace std;
using Random = effolkronium::random_static;

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
double busquedaLocal(const Dataset &train, vector<double> &Sact, int &iter, int maxiter){
    int generacion = 0;
    bool mejora;

    // Generar vector inicial
    if(Sact.empty()) {
        generaSolucionInicial(Sact, train.numCaracteristicas());
    }

    // Calcula objetivo
    double objetivoActual = funObjetivo(train, Sact);
    iter++;

    vector<double> S = Sact;
    vector<int> indices;
    double objetivo = 0;

    // Bucle principal del algoritmo
    while(generacion < 20*Sact.size() && iter < maxiter){
        // Generar índices de vecindario
        indices = mezclarIndices(S.size());

        mejora = false;

        // Bucle para generar vecinos
        for(int i = 0; !mejora && i < indices.size(); i++){
            // Generar vecino
            Mov(S,indices[i],0.8);

            // Calcular objetivo tras mutacion
            objetivo = funObjetivo(train, S);
            iter++;
            // Comprobar si se ha mejorado la solución
            if(objetivo > objetivoActual){
                generacion = 0;
                objetivoActual = objetivo;
                Sact = S;
                mejora = true;
            }
            else
                S = Sact;

            generacion++;
        }
    }

    // Devolver la solución encontrada
    return objetivoActual;
}