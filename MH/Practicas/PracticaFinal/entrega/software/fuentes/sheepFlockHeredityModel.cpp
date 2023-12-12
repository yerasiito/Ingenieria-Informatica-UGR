#include "sheepFlockHeredityModel.h"
#include "random.hpp"
#include "busquedaLocal.h"

using namespace std;
using Random = effolkronium::random_static;

void cruceSPX(vector<double> &padre, int numOvejas, int sizeOvejas){

    // oveja 1
    int pos_ove1 = sizeOvejas * Random::get(0, numOvejas-1); // Posicion random

    // oveja 2
    int pos_ove2 = sizeOvejas * Random::get(0, numOvejas-1); // Posicion random
    while(pos_ove1 == pos_ove2)
        pos_ove2 = sizeOvejas * Random::get(0, numOvejas-1); // Posicion random

    // Stage 1 cruce
    int punto = Random::get(0, sizeOvejas-1); // Posicion random

    // Simula el cromosoma plegado e intercambia 2 subcromosomas a partir de "punto"
    for (size_t i = punto; i < punto+sizeOvejas && pos_ove1+i < padre.size() && pos_ove2+i < padre.size(); ++i) {
        double aux = padre[pos_ove1 + i];
        padre[pos_ove1 + i] = padre[pos_ove2 + i];
        padre[pos_ove2 + i] = aux;
    }

}

void cruceSPX(vector<double> &padre1, vector<double> &padre2){
    vector<vector<double>> hijos;

    // Stage 2 cruce
    int punto = Random::get(0, (int) padre1.size()); // Posicion random

    // A partir de "punto" se cruzan los cromosomas
    for (size_t i = punto; i < padre1.size(); ++i) {

        double aux = padre1[i];
        padre1[i] = padre2[i];
        padre2[i] = aux;
    }
    // Verificar restricciones
    checkPesos(padre1);
    checkPesos(padre2);
}

vector<double> getFromIndex(const Poblacion &pop, vector<int> &indices, int &idx){
    idx = indices.back();
    indices.pop_back();

    // Si está vacio, genera indices de nuevo
    if(indices.empty())
        indices = mezclarIndices(pop.numPoblacion());

    return pop.getIndividuo(idx);
}

void robust_replace(pair<vector<double>, double> &par1, const Dataset &train, double meanFitness){

    // Si está por debajo del fitness medio, reemplaza el cromosoma por completo
    if(par1.second < meanFitness){
        par1.first = Random::get<std::vector>(0.0, 1.0, train.numCaracteristicas());
        checkPesos(par1.first);
        par1.second = funObjetivo(train, par1.first);
    }
}

void inverseMov(vector<double> &w) {
    int pos1 = Random::get(0, (int) w.size()); // Posicion random
    int pos2 = Random::get(pos1, (int) w.size()); // Posicion random

    // Desde la posicion 1 a la 2, intercambian valores
    for(int i = 0; pos1 + i < pos2-i ; i++){
        double aux = w[pos1+i];
        w[pos1+i] = w[pos2-i];
        w[pos2-i] = aux;
    }

}

std::vector<double> SFHMA(const Dataset &train, int maxIters, const string& operador){
    // Probabilidad de mutacion
    double pmut = 0.1, pcross = 0.7;

    // Tamaño de subcromosoma (oveja)
    int tam_ovejas = 4;
    int num_ovejas = train.numCaracteristicas()/tam_ovejas;

    int rebanios = 50, iter = 0;

    int numCaracteristicas = train.numCaracteristicas();

    Poblacion pop;

    // Inicializar el vector
    pop.nuevas_soluciones(rebanios, numCaracteristicas); // Aleatorio

    // Calcular el fitness de la poblacion en train
    pop.calcularfitness_pop(train, iter);

    // Indices para recorrer cada padre de la población
    vector<int> indices = mezclarIndices(pop.numPoblacion());

    pair<vector<double>, double> parent1, parent2, parent3;
    int idx1, idx2, idx3;
    while(iter < maxIters){
        /* Stage 1 - Operaciones subcromosoma*/

        // Seleccionar padre sin repeticion
        parent1.first = getFromIndex(pop, indices, idx1);

        // Cruce subcromosoma
        if(Random::get(0.0, 1.0) <= pcross){
            cruceSPX(parent1.first, num_ovejas, tam_ovejas);
        }

        // Mutacion subcromosoma
        if(Random::get(0.0, 1.0) <= pmut) {
            int posi = Random::get(0, pop.numCaracteristicas()); // Posicion random
            inverseMov(parent1.first); // Mutacion inversa
            Mov(parent1.first, posi ,0.3); //Mutacion 1 punto
        }

        /* Stage 2 - Operaciones Cromosomas */

        // Selecciona dos padres sin repeticion
        parent2.first = getFromIndex(pop, indices, idx2);
        parent3.first = getFromIndex(pop, indices, idx3);

        // Cruce cromosoma
        if(Random::get(0.0, 1.0) <= pcross){
            cruceSPX(parent2.first, parent3.first);
        }

        // Mutacion Cromosoma
        if(Random::get(0.0, 1.0) <= pmut) {
            int posi = Random::get(1, pop.numCaracteristicas()); // Posicion random

            // Mutacion inversa
            inverseMov(parent2.first);
            inverseMov(parent3.first);

            // Mutacion 1 punto
            Mov(parent2.first, posi ,0.3);
            Mov(parent3.first, posi ,0.3);
        }

        // Calcular el fitness de cada individuo modificado
        parent1.second = funObjetivo(train, parent1.first);
        parent2.second = funObjetivo(train, parent2.first);
        parent3.second = funObjetivo(train, parent3.first);

        // Guarda los padres modificados
        pop.setIndividuoyFitness(idx1, parent1.first, parent1.second);
        pop.setIndividuoyFitness(idx2, parent2.first, parent2.second);
        pop.setIndividuoyFitness(idx3, parent3.first, parent3.second);

        // 3 evaluacion objetivo = +3 iteraciones
        iter += 3;
    }

    return pop.mejor();
}

std::vector<double> SFHMA_hibrido(const Dataset &train, int maxIterSFMA, const string& operador){
    //Iteraciones Busqueda Local
    int maxiterBL = 1000;

    // Probabilidad de mutacion
    double pmut = 0.1, pcross = 0.7;

    // Tamaño de subcromosoma (oveja)
    int tam_ovejas = 4;
    int num_ovejas = train.numCaracteristicas()/tam_ovejas;

    int rebanios = 50, iter = 0, it = 0;

    int numCaracteristicas = train.numCaracteristicas();

    Poblacion pop;

    // Inicializar el vector
    pop.nuevas_soluciones(rebanios, numCaracteristicas); // Aleatorio

    // Calcular el fitness de la poblacion en train
    pop.calcularfitness_pop(train, iter);

    // Indices para recorrer cada padre de la población
    vector<int> indices = mezclarIndices(pop.numPoblacion());
    vector<int> bestFitness;

    pair<vector<double>, double> parent1, parent2, parent3;
    int idx1, idx2, idx3;
    while(iter < maxIterSFMA){

        /* Stage 1 - Operaciones subcromosoma */

        // Seleccionar padre sin repeticion
        parent1.first = getFromIndex(pop, indices, idx1);

        // Cruce subcromosoma
        if(Random::get(0.0, 1.0) <= pcross){
            cruceSPX(parent1.first, num_ovejas, tam_ovejas);
        }

        // Mutacion subcromosoma
        if(Random::get(0.0, 1.0) <= pmut) {
            int posi = Random::get(0, pop.numCaracteristicas()); // Posicion random
            inverseMov(parent1.first); // Mutacion inversa
            Mov(parent1.first, posi ,0.3); //Mutacion 1 punto
        }

        // Stage 2 - Operaciones Cromosoma

        // Selecciona dos padres sin repeticion
        parent2.first = getFromIndex(pop, indices, idx2);
        parent3.first = getFromIndex(pop, indices, idx3);

        // Cruce cromosoma
        if(Random::get(0.0, 1.0) <= pcross){
            cruceSPX(parent2.first, parent3.first);
        }

        // Mutacion cromosoma
        if(Random::get(0.0, 1.0) <= pmut) {
            int posi = Random::get(1, pop.numCaracteristicas()); // Posicion random

            // Mutacion inversa
            inverseMov(parent2.first);
            inverseMov(parent3.first);

            // Mutacion 1 punto
            Mov(parent2.first, posi ,0.3); //Mutacion
            Mov(parent3.first, posi ,0.3); //Mutacion
        }

        // Calcular el fitness de cada individuo modificado
        parent1.second = funObjetivo(train, parent1.first);
        parent2.second = funObjetivo(train, parent2.first);
        parent3.second = funObjetivo(train, parent3.first);

        // Guarda los padres modificados
        pop.setIndividuoyFitness(idx1, parent1.first, parent1.second);
        pop.setIndividuoyFitness(idx2, parent2.first, parent2.second);
        pop.setIndividuoyFitness(idx3, parent3.first, parent3.second);

        iter += 3;

        // Uso de busqueda local con el 10% mejor fitness cada 10 evaluaciones
        if(iter % 10 == 0) {
            bestFitness = pop.getOrderedFitness();
            for (int i = 0; i < (int)bestFitness.size() * pmut && iter < maxIterSFMA; i++) {
                it = 0;
                pop.setFitness(bestFitness[i], busquedaLocal(train, pop.getMIndividuo(bestFitness[i]),
                                                             it, maxiterBL));
                iter += it;
            }
        }
    }

    return pop.mejor();
}
