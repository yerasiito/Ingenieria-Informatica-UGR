#include "apc.h"
#include "busquedaLocal.h"
#include "random.hpp"

using namespace std;
using Random = effolkronium::random_static;

void generaSolucionInicial(vector<double> &pesos, int numCaracteristicas){
    pesos = Random::get<std::vector>(0.0, 1.0, numCaracteristicas);
}

void mezclarkIndices(vector<int> &indices, int maxrango, int k){
    // Definir lista de índices aleatorios
    std::vector<int> idx(maxrango);
    indices.clear();
    // Para cada atributo crea un vector de indices
    for (int i = 0; i < k; i++) {
        iota(idx.begin(), idx.end(), 0);
        Random::shuffle(idx);

        //Concatenar
        indices.insert(indices.begin(), idx.begin(), idx.end());

    }
}

double busquedaLocal(const Dataset &train, vector<double> &Sact, int maxiter, int k){
    int iter = 0;
    int generacion = 0;
    bool mejora;

    // Generar vector inicial si Sact está vacío
    if(Sact.empty()) {
        generaSolucionInicial(Sact, train.numCaracteristicas());
    }

    // Calcula objetivo
    double objetivoActual = funObjetivo(train, Sact);
    iter++;

    vector<double> S = Sact;
    vector<int> kindices, indices;

    double objetivo = 0;
    int n = S.size();

    vector<int>::iterator itIdx,fin;
    // Bucle principal del algoritmo
    while(generacion < 20*n && iter < maxiter){
        // Generar índices de vecindario
        mezclarkIndices(indices, n, k); // genera k vecindarios

        // Inicio de indice de mutacion
        itIdx = indices.begin();

        mejora = false;
        // Bucle para generar vecinos
        while(!mejora && itIdx < indices.end()){
            // Obtener indices de mutacion segun k atributos
            fin = (itIdx + k > indices.end()) ? indices.end() : itIdx + k;

            // Generar vecino con k atributos mutados
            Mov(S, {itIdx, fin}, VARIANZA);

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
            itIdx += k;
        }
    }
    // Devolver la solución encontrada
    return objetivoActual;
}