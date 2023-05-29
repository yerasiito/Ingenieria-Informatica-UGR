#include <algorithm>
#include "algoritmosGeneticos.h"
#include "apc.h"
#include "random.hpp"
#include "busquedaLocal.h"

using namespace std;
using Random = effolkronium::random_static;

bool compare(const std::pair<double, int>& a, const std::pair<double, int>& b) {
    return a.first < b.first;
}

class Poblacion{
    // Una poblacion es un conjunto de pesos
private:
    int worstFitness, worstSecondFitness, bestFitness;
    vector<pair<double,bool>> fitness_pop;
    vector<vector<double>> poblacion;
public:
    Poblacion(){
        worstFitness = -1;
        worstSecondFitness = -1;
        bestFitness = -1;
        if(!poblacion.empty())
            poblacion.clear();
        if(!fitness_pop.empty())
            fitness_pop.clear();
    }

    [[nodiscard]] int numPoblacion() const{
        return (int) poblacion.size();
    }

    [[nodiscard]] int numCaracteristicas() const{
        return (int) poblacion[0].size();
    }

    vector<double> & getMIndividuo(int i){
        fitness_pop[i].second = false;
        return poblacion[i];
    }

    [[nodiscard]] vector<double> getIndividuo(int i) const{
        return poblacion[i];
    }

    void addIndividuo(const vector<double> & individuo){
        poblacion.push_back(individuo);
        fitness_pop.emplace_back(-1, false);
    }

    void setIndividuo(int i, const vector<double> & individuo){
        if(poblacion[i] != individuo)
            fitness_pop[i].second = false;

        poblacion[i] = individuo;
    }

    void setFitness(int i, double fitness){
        fitness_pop[i].first = fitness;
        fitness_pop[i].second = true;
    }

    void setIndividuoyFitness(int i, const vector<double> & individuo, double fitness){
        if(poblacion[i] != individuo)
            fitness_pop[i].second = false;

        poblacion[i] = individuo;
        setFitness(i, fitness);
    }

    void nuevas_soluciones(int tamPoblacion, int numCaracteristicas){

        if(!poblacion.empty())
            poblacion.clear();

        for(int i = 0; i < tamPoblacion; i++){ //Matriz aleatoria
            poblacion.push_back(Random::get<std::vector>(0.0, 1.0, numCaracteristicas));
            fitness_pop.emplace_back(-1, false);
        }
    }

    bool estaEvaluado(int i){
        return i < fitness_pop.size() && fitness_pop[i].second;
    }

    void calcularfitness_pop(const Dataset& train, int &iter){
        for(int i = 0; i < fitness_pop.size(); i++){
            if(estaEvaluado(i))
                continue;

            fitness_pop[i].first = funObjetivo(train, poblacion[i]);
            fitness_pop[i].second = true;
            iter++;
        }

        // Obtener el peor fitness del vector
        auto minFitness = min_element(fitness_pop.begin(), fitness_pop.end());

        // Obtener el segundo peor fitness
        auto secondMinFitness = min_element(fitness_pop.begin(), fitness_pop.end(), [&](const auto& a, const auto& b) {
            return a < b && a != *minFitness;
        });

        // Obtener el mejor fitness del vector
        auto maxFitness = max_element(fitness_pop.begin(), fitness_pop.end());

        // Si no está el vector vacio, guarda el peor y mejor fitness
        if (!fitness_pop.empty()) {
            worstFitness = (int) distance(fitness_pop.begin(), minFitness);
            worstSecondFitness = (int) distance(fitness_pop.begin(), secondMinFitness);
            bestFitness = (int) distance(fitness_pop.begin(), maxFitness);
        }
    }

    [[nodiscard]] int getPosWorst() const{
        return worstFitness;
    }

    [[nodiscard]] int getSecondPosWorst() const{
        return worstSecondFitness;
    }

    [[nodiscard]] int getPosBest() const{
        return bestFitness;
    }

    double getFitness(int pos = -1){
        return (pos == -1) ? fitness_pop[worstFitness].first : fitness_pop[pos].first;
    }

    [[nodiscard]] vector<int> getOrderedFitness() const{
        std::vector<std::pair<double, int>> indicesValores;
        for (int i = 0; i < fitness_pop.size(); ++i) {
            indicesValores.push_back(std::make_pair(fitness_pop[i].first, i));
        }
        std::sort(indicesValores.begin(), indicesValores.end(), compare);

        std::vector<int> indicesOrdenados;
        for (const auto& elemento : indicesValores) {
            indicesOrdenados.push_back(elemento.second);
        }

        return indicesOrdenados;
    }

    [[nodiscard]] int torneo_binario() const{
        int candidato1, candidato2;

        // Obtiene 2 indices aleatorios (sin repeticion)
        candidato1 = Random::get(1, numPoblacion()); // Rango de números aleatorios
        candidato2 = Random::get(1, numPoblacion()); // Rango de números aleatorios
        while (candidato1 == candidato2) {
            candidato2 = Random::get(1, numPoblacion());
        }

        // Debug
        // cout << "Candidatos:\n";
        // cout << candidato1 << " " << fitness_pop[candidato1] << "\n";
        // cout << candidato2 << " " << fitness_pop[candidato2] << "\n";
        // cout << endl;

        return (fitness_pop[candidato1] > fitness_pop[candidato2]) ? candidato1 : candidato2;
    }

    vector<double> mejor(){
        return poblacion[worstFitness];
    }

    void elitismo(int betterFitness, const vector<double>& betterIndv){
        setIndividuo(worstFitness, betterIndv); //Cambia el peor de newpop por el mejor de pop
        worstFitness = betterFitness;
    }

    void imprimir() {
        // Imprimir la matriz
        cout << "Poblacion " << poblacion.size() << " " << poblacion[0].size() << endl;
        for (auto & i : poblacion) {
            for (double j : i) {
                std::cout << j << " ";
            }
            cout << endl;
        }
    }

    void setValor(int i, int j, double valor){
        if(poblacion[i][j] != valor)
            fitness_pop[i].second = false;

        poblacion[i][j] = valor;
    }

    void copy(Poblacion otro){
        if(&otro != this){
            clear();

            worstFitness = otro.worstFitness;
            bestFitness = otro.bestFitness;

            for(auto fit : otro.fitness_pop)
                fitness_pop.push_back(fit);

            for(const auto& i : otro.poblacion)
                poblacion.push_back(i);
        }

    }

    void clear(){
        worstFitness = -1;
        bestFitness = -1;
        if(!poblacion.empty())
            poblacion.clear();
        if(!fitness_pop.empty())
            fitness_pop.clear();
    }

};

void aplicarTorneo(const Poblacion &pop, Poblacion &seleccionados){
    seleccionados.clear();

    int posi;
    for(int i = 0; i < pop.numPoblacion(); i++){
        posi = pop.torneo_binario();
        seleccionados.addIndividuo(pop.getIndividuo(posi));
    }
}

void checkPesos(vector<double> &peso){
    for(int i = 0; i < peso.size(); i++){
        if(peso[i] < 0.1)
            peso[i] = 0;
        if(peso[i] > 1)
            peso[i] = 1;
    }
}

// Devuelve 2 hijos
vector<vector<double>> cruceAritmetrico(vector<double> padre1, vector<double> padre2){
    vector<vector<double>> hijos;
    hijos.resize(2); //Se generan 2 hijos

    double alpha = Random::get(0.0, 1.0);
    double gen1, gen2;
    for (size_t i = 0; i < padre1.size(); ++i) {
        gen1 = alpha * padre1[i] + (1 - alpha) * padre2[i];
        gen2 = alpha * padre2[i] + (1 - alpha) * padre1[i];

        hijos[0].push_back(gen1);
        hijos[1].push_back(gen2);
    }

    return hijos;
}

vector<vector<double>> cruceBLX(vector<double> padre1, vector<double> padre2, float alpha = 0.3){
    double minVal, maxVal, range, gen1, gen2;
    double minRange, maxRange;
    std::vector<std::vector<double>> hijos;
    hijos.resize(2); // Se generan 2 hijos

    for (size_t i = 0; i < padre1.size(); ++i) {
        minVal = std::min(padre1[i], padre2[i]);
        maxVal = max(padre1[i], padre2[i]);

        range = maxVal - minVal;

        minRange = minVal - alpha * range;
        maxRange = maxVal + alpha * range;

        gen1 = Random::get(minRange, maxRange);
        gen2 = Random::get(minRange, maxRange);

        hijos[0].push_back(gen1);
        hijos[1].push_back(gen2);
    }

    return hijos;
}

// cruce==0 ejecuta aritmétrico aleatorio, cruce>0 ejecuta BLX
std::vector<double> AGG(const Dataset &train, int maxIters, double pcross, const string& operador){
    // Probabilidad de mutacion
    double pmut = 0.1;

    int tamPoblacion = 50, iter = 0;
    int numCaracteristicas = train.numCaracteristicas();

    Poblacion pop, newpop;

    // Inicializar el vector
    pop.nuevas_soluciones(tamPoblacion, numCaracteristicas); // Aleatorio

    // Calcular el fitness de la poblacion en train
    pop.calcularfitness_pop(train, iter);

    vector<double> sol1, sol2;
    vector<vector<double>> hijos;
    while(iter < maxIters){
        // Selección por torneo
        aplicarTorneo(pop, newpop);

        int total_cruce = (int) (pop.numPoblacion()*pcross);

        for(int i = 0; i < total_cruce; i+=2){
            sol1 = newpop.getIndividuo(i);
            sol2 = newpop.getIndividuo(i+1);

            if(operador == "Aritmetrico")
                hijos = cruceAritmetrico(sol1, sol2);
            else
                hijos = cruceBLX(sol1, sol2);


            newpop.setIndividuo(i,hijos[0]);
            newpop.setIndividuo(i+1, hijos[1]);
        }

        // Mutacion
        int total_mutar = (int) (pop.numPoblacion() * pmut);
        int posi;

        for(int i = 0; i < total_mutar; i++){
            posi = Random::get(1, newpop.numCaracteristicas()); // Posicion random

            Mov(newpop.getMIndividuo(i), posi ,0.8); //Mutacion
        }

        // Evaluacion
        for(int i = 0; i < newpop.numPoblacion(); i++)
            checkPesos(newpop.getMIndividuo(i));

        newpop.calcularfitness_pop(train, iter);

        // Etilismo, para no empeorar
        if (pop.getFitness(pop.getPosBest()) < newpop.getFitness(newpop.getPosBest())){
            int mejor = pop.getPosBest();
            newpop.elitismo(mejor, pop.getIndividuo(mejor));
        }

        // Reemplazo
        pop.copy(newpop);
    }

    return pop.mejor();
}

void reemplaza_peores(const vector<double>& sol1, double fit1, const vector<double>& sol2, double fit2,
                      Poblacion &pop){
    int worst = pop.getPosWorst();
    int secondWorst = pop.getSecondPosWorst();
    vector<double> mini_pop = {fit1, fit2, pop.getFitness(worst), pop.getFitness(secondWorst)};

    std::sort(mini_pop.rbegin(), mini_pop.rend());

    if(mini_pop[0] == fit1) {
        pop.setIndividuoyFitness(worst, sol1, fit1);
        if(mini_pop[1] == fit2) {
            pop.setIndividuoyFitness(secondWorst, sol2, fit2);

        }
    }
    else if(mini_pop[0] == fit2) {
        pop.setIndividuoyFitness(worst, sol2, fit2);
        if(mini_pop[1] == fit1) {
            pop.setIndividuoyFitness(secondWorst, sol1, fit1);
        }
    }
}

// cruce==0 ejecuta aritmétrico aleatorio, cruce>0 ejecuta BLX
std::vector<double> AGE(const Dataset &train, int maxIters, const string& operador){
    // Probabilidad de mutacion
    double pmut = 0.1;

    int tamPoblacion = 50, iter = 0;
    int numCaracteristicas = train.numCaracteristicas();

    Poblacion pop;

    // Inicializar el vector
    pop.nuevas_soluciones(tamPoblacion, numCaracteristicas); // Aleatorio

    // Calcular el fitness de la poblacion en train
    pop.calcularfitness_pop(train, iter);

    int posi1, posi2;
    vector<double> sol1, sol2;
    double fit1, fit2;
    vector<vector<double>> hijos;
    while(iter < maxIters){
        // Selección por torneo
        posi1 = pop.torneo_binario();
        posi2 = pop.torneo_binario();

        // cruzo
        if(operador == "Aritmetrico")
            hijos = cruceAritmetrico(pop.getIndividuo(posi1), pop.getIndividuo(posi2));
        else
            hijos = cruceBLX(pop.getIndividuo(posi1), pop.getIndividuo(posi2));

        sol1 = hijos[0];
        sol2 = hijos[1];

        // Mutacion
        int posi;
        if(Random::get(0.0, 1.0) <= pmut) {
            posi = Random::get(1, pop.numCaracteristicas()); // Posicion random
            Mov(sol1, posi ,0.8); //Mutacion
        }
        if(Random::get(0.0, 1.0) <= pmut) {
            posi = Random::get(1, pop.numCaracteristicas()); // Posicion random
            Mov(sol2, posi ,0.8); //Mutacion
        }

//        auto inicio = chrono::high_resolution_clock::now(); // Contamos el tiempo de los algoritmos

        checkPesos(sol1);
        checkPesos(sol2);

        // Evaluacion
        fit1 = funObjetivo(train, sol1);
        fit2 = funObjetivo(train, sol2);

//        cout << iter << endl;
        iter += 2;

        // Reemplazo los 2 peores
        reemplaza_peores(sol1, fit1, sol2, fit2, pop);
    }

    return pop.mejor();
}
std::vector<double> AM_All(const Dataset &train, int maxIters, double pcross, const string& operador){
    // Probabilidad de mutacion
    double pmut = 0.1;

    int tamPoblacion = 50, iter = 0, generacion = 0;
    int numCaracteristicas = train.numCaracteristicas();
    int maxiter = 2* train.numCaracteristicas();

    Poblacion pop, newpop;

    // Inicializar el vector
    pop.nuevas_soluciones(tamPoblacion, numCaracteristicas); // Aleatorio

    // Calcular el fitness de la poblacion en train
    pop.calcularfitness_pop(train, iter);

    vector<double> sol1, sol2;
    vector<vector<double>> hijos;
    while(iter < maxIters){
        // Selección por torneo
        aplicarTorneo(pop, newpop);

        int total_cruce = (int) (pop.numPoblacion()*pcross);

        for(int i = 0; i < total_cruce; i+=2){
            sol1 = newpop.getIndividuo(i);
            sol2 = newpop.getIndividuo(i+1);

            hijos = cruceBLX(sol1, sol2);

            newpop.setIndividuo(i,hijos[0]);
            newpop.setIndividuo(i+1, hijos[1]);
        }

        // Mutacion
        int total_mutar = (int) (pop.numPoblacion() * pmut);
        int posi;

        for(int i = 0; i < total_mutar; i++){
            posi = Random::get(1, newpop.numCaracteristicas()); // Posicion random
            Mov(newpop.getMIndividuo(i), posi ,0.8); //Mutacion
        }

        // Evaluacion
        for(int i = 0; i < newpop.numPoblacion(); i++)
            checkPesos(newpop.getMIndividuo(i));

        newpop.calcularfitness_pop(train, iter);

        // Etilismo, para no empeorar
        if (pop.getFitness(pop.getPosBest()) < newpop.getFitness(newpop.getPosBest())){
            int mejor = pop.getPosBest();
            newpop.elitismo(mejor, pop.getIndividuo(mejor));
        }

        // Reemplazo
        pop.copy(newpop);

        generacion++;
        int it;
        if(generacion % 10 == 0){
            for(int i = 0; i < pop.numPoblacion() && iter < maxIters; i++) {
                it = 0;
                pop.setFitness(i, busquedaLocal(train, pop.getMIndividuo(i), it, maxiter));
                iter += it;
            }
        }
    }

    return pop.mejor();
}

std::vector<double> AM_Rand(const Dataset &train, int maxIters, double pcross, const string& operador){
    // Probabilidad de mutacion
    double pmut = 0.1;

    int tamPoblacion = 50, iter = 0, generacion = 0;
    int numCaracteristicas = train.numCaracteristicas();
    int maxiter = 2* train.numCaracteristicas();

    Poblacion pop, newpop;

    // Inicializar el vector
    pop.nuevas_soluciones(tamPoblacion, numCaracteristicas); // Aleatorio

    // Calcular el fitness de la poblacion en train
    pop.calcularfitness_pop(train, iter);

    vector<double> sol1, sol2;
    vector<vector<double>> hijos;
    while(iter < maxIters){
        // Selección por torneo
        aplicarTorneo(pop, newpop);

        int total_cruce = (int) (pop.numPoblacion()*pcross);

        for(int i = 0; i < total_cruce; i+=2){
            sol1 = newpop.getIndividuo(i);
            sol2 = newpop.getIndividuo(i+1);

            hijos = cruceBLX(sol1, sol2);

            newpop.setIndividuo(i,hijos[0]);
            newpop.setIndividuo(i+1, hijos[1]);
        }

        // Mutacion
        int total_mutar = (int) (pop.numPoblacion() * pmut);
        int posi;

        for(int i = 0; i < total_mutar; i++){
            posi = Random::get(1, newpop.numCaracteristicas()); // Posicion random

            Mov(newpop.getMIndividuo(i), posi ,0.8); //Mutacion
        }

        // Evaluacion
        for(int i = 0; i < newpop.numPoblacion(); i++)
            checkPesos(newpop.getMIndividuo(i));

        newpop.calcularfitness_pop(train, iter);

        // Etilismo, para no empeorar
        if (pop.getFitness(pop.getPosBest()) < newpop.getFitness(newpop.getPosBest())){
            int mejor = pop.getPosBest();
            newpop.elitismo(mejor, pop.getIndividuo(mejor));
        }

        // Reemplazo
        pop.copy(newpop);

        generacion++;

        int it = 0;
        if (generacion % 10 == 0){
            for (int i = 0; i < pop.numPoblacion() * pmut && iter < maxIters; i++) {
                it = 0;
                pop.setFitness(i, busquedaLocal(train, pop.getMIndividuo(i), it, maxiter));
                iter += it;
            }
        }
    }

    return pop.mejor();
}

std::vector<double> AM_Best(const Dataset &train, int maxIters, double pcross, const string& operador){
    double pmut = 0.1;
    int tamPoblacion = 50, iter = 0, generacion = 0;
    int numCaracteristicas = train.numCaracteristicas();
    int maxiter = 2* train.numCaracteristicas();

    Poblacion pop, newpop;

    // Inicializar el vector
    pop.nuevas_soluciones(tamPoblacion, numCaracteristicas); // Aleatorio

    // Calcular el fitness de la poblacion en train
    pop.calcularfitness_pop(train, iter);

    vector<double> sol1, sol2;
    vector<vector<double>> hijos;
    vector<int> bestFitness;
    while(iter < maxIters){
        // Selección por torneo
        aplicarTorneo(pop, newpop);

        int total_cruce = (int) (pop.numPoblacion()*pcross);

        for(int i = 0; i < total_cruce; i+=2){
            sol1 = newpop.getIndividuo(i);
            sol2 = newpop.getIndividuo(i+1);

            hijos = cruceBLX(sol1, sol2);

            newpop.setIndividuo(i,hijos[0]);
            newpop.setIndividuo(i+1, hijos[1]);
        }

        // Mutacion
        int total_mutar = (int) (pop.numPoblacion() * pmut);
        int posi;

        for(int i = 0; i < total_mutar; i++){
            posi = Random::get(1, newpop.numCaracteristicas()); // Posicion random

            Mov(newpop.getMIndividuo(i), posi ,0.8); //Mutacion
        }

        // Evaluacion
        for(int i = 0; i < newpop.numPoblacion(); i++)
            checkPesos(newpop.getMIndividuo(i));

        newpop.calcularfitness_pop(train, iter);

        // Etilismo, para no empeorar
        if (pop.getFitness(pop.getPosBest()) < newpop.getFitness(newpop.getPosBest())){
            int mejor = pop.getPosBest();
            newpop.elitismo(mejor, pop.getIndividuo(mejor));
        }

        // Reemplazo
        pop.copy(newpop);

        generacion++;

        int it;
        if(generacion % 10 == 0) {
            bestFitness = pop.getOrderedFitness();
            for (int i = 0; i < bestFitness.size() * pmut && iter < maxIters; i++) {
                it = 0;
                pop.setFitness(bestFitness[i], busquedaLocal(train, pop.getMIndividuo(bestFitness[i]),
                                                             it, maxiter));
                iter += it;
            }
        }
    }

    return pop.mejor();
}