#include "algoritmosGeneticos.h"
#include "apc.h"
#include "random.hpp"
#include <algorithm>
#include <chrono>

using namespace std;
using Random = effolkronium::random_static;

class Poblacion{
    // Una poblacion es un conjunto de pesos
    private:
        int worstFitness, worstSecondFitness, bestFitness;
        vector<pair<double,bool>> fitness_pop;
        vector<vector<double>> poblacion;
    public:
        Poblacion(){
            clear();
        }

        int numPoblacion() const{
            return poblacion.size();
        }

        int numCaracteristicas() const{
            return poblacion[0].size();
        }

        vector<double> & getMIndividuo(int i){
            fitness_pop[i].second = false;
            return poblacion[i];
        }

        vector<double> getIndividuo(int i) const{
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

        void nuevas_soluciones(int tamPoblacion, int numCaracteristicas){

            if(!poblacion.empty())
                poblacion.clear();

            for(int i = 0; i < tamPoblacion; i++){ //Matriz aleatoria
                poblacion.push_back(Random::get<std::vector>(0.0, 1.0, numCaracteristicas));
                fitness_pop.emplace_back(-1, false);
            }
        }

        bool estaEvaluado(int i){
            return (i >= fitness_pop.size()) ? false : fitness_pop[i].second;
        }

        void calcularfitness_pop(Dataset train){
            int acierto_train;

            for(int i = 0; i < fitness_pop.size(); i++){
                if(estaEvaluado(i))
                    continue;

                clasificarTrain(train, poblacion[i], acierto_train);
                fitness_pop[i].first = calcularFitness(acierto_train, train.numEjemplos(), poblacion[i]);
                fitness_pop[i].second = true;
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
                worstFitness = distance(fitness_pop.begin(), minFitness);
                worstSecondFitness = distance(fitness_pop.begin(), secondMinFitness);
                bestFitness = distance(fitness_pop.begin(), maxFitness);
            }
        }

        const int getPosWorst(){
            return worstFitness;
        }

        const int getSecondPosWorst(){
            return worstSecondFitness;
        }

        const int getPosBest(){
            return bestFitness;
        }

        const double getFitness(int pos = -1){
            return (pos == -1) ? fitness_pop[worstFitness].first : fitness_pop[pos].first;
        }

        const vector<pair<double,bool>> getFitness_vector() const{
            return fitness_pop;
        }

        int torneo_binario() const{
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

        void etilismo(int betterFitness, vector<double> betterIndv){
            setIndividuo(worstFitness, betterIndv); //Cambia el peor de newpop por el mejor de pop
            worstFitness = betterFitness;
        }

        void imprimir() {
        // Imprimir la matriz
            cout << "Poblacion " << poblacion.size() << " " << poblacion[0].size() << endl;
            for (int i = 0; i < poblacion.size(); ++i) {
                for (int j = 0; j < poblacion[i].size(); ++j) {
                    std::cout << poblacion[i][j] << " ";
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

                for(auto i : otro.poblacion)
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
vector<double> AGG(Dataset train, int maxIters, double pcross, int cruce){
    double pmut = 0.1;
    int tamPoblacion = 50;
    int numCaracteristicas = train.numCaracteristicas();

    // Cual es el tamaño de la poblacion?
    Poblacion pop, newpop;

    // Inicializar el vector
    pop.nuevas_soluciones(tamPoblacion, numCaracteristicas); // Aleatorio

    // Calcular el fitness de la poblacion en train
    pop.calcularfitness_pop(train);

    int iter = tamPoblacion;

    vector<double> sol1, sol2;
    vector<vector<double>> hijos;
    while(iter < maxIters){
        // Selección por torneo
        aplicarTorneo(pop, newpop);

        int total_cruce = pop.numPoblacion()*pcross;

        for(int i = 0; i < total_cruce; i+=2){
            sol1 = newpop.getIndividuo(i);
            sol2 = newpop.getIndividuo(i+1);

            if(cruce == 0)
                hijos = cruceAritmetrico(sol1, sol2);
            else
                hijos = cruceBLX(sol1, sol2);


            newpop.setIndividuo(i,hijos[0]);
            newpop.setIndividuo(i+1, hijos[1]);
        }

        // Mutacion
        int total_mutar = pop.numPoblacion() * pmut;
        int posi;

        for(int i = 0; i < total_mutar; i++){
            posi = Random::get(1, newpop.numCaracteristicas()); // Posicion random

            Mov(newpop.getMIndividuo(i), posi ,0.8); //Mutacion
        }
        auto inicio = chrono::high_resolution_clock::now(); // Contamos el tiempo de los algoritmos

        // Evaluacion
        newpop.calcularfitness_pop(train);

//        auto fin = std::chrono::high_resolution_clock::now();
        // Calcular la duración en milisegundos
//        auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
        // Mostrar la duración en milisegundos
//        std::cout << "El tiempo transcurrido: " << duracion.count() << " milisegundos" << std::endl;

        // Etilismo, para no empeorar
        if (pop.getFitness(pop.getPosBest()) < newpop.getFitness(newpop.getPosBest())){
            int peor = newpop.getPosWorst();
            int mejor = pop.getPosBest();
            newpop.etilismo(mejor, pop.getIndividuo(mejor));
        }

//        cout << iter << endl;
        iter += newpop.numPoblacion();

        // Reemplazo
        pop.copy(newpop);

    }

    return pop.mejor();
}

void reemplaza_peores(vector<double> sol1, double fit1, vector<double> sol2, double fit2, Poblacion pop){
    double worst = pop.getPosWorst();
    double secondWorst = pop.getSecondPosWorst();
    vector<double> mini_pop = {fit1, fit2, pop.getFitness(worst), pop.getFitness(secondWorst)};

    std::sort(mini_pop.rbegin(), mini_pop.rend());

    if(mini_pop[0] == fit1)
        pop.setIndividuo(worst, sol1);
    else if(mini_pop[0] == fit2)
        pop.setIndividuo(worst, sol2);

    if(mini_pop[1] == fit1)
        pop.setIndividuo(worst, sol1);
    else if(mini_pop[1] == fit2)
        pop.setIndividuo(worst, sol2);
}

// cruce==0 ejecuta aritmétrico aleatorio, cruce>0 ejecuta BLX
vector<double> AGE(Dataset train, int maxIters, double pcross, int cruce){
    double pmut = 0.1;
    int tamPoblacion = 50;
    int numCaracteristicas = train.numCaracteristicas();

    // Cual es el tamaño de la poblacion?
    Poblacion pop;

    // Inicializar el vector
    pop.nuevas_soluciones(tamPoblacion, numCaracteristicas); // Aleatorio

    // Calcular el fitness de la poblacion en train
    pop.calcularfitness_pop(train);

    int iter = tamPoblacion;
    int posi1, posi2;
    vector<double> sol1, sol2;
    double fit1, fit2;
    vector<vector<double>> hijos;
    while(iter < maxIters){
        // Selección por torneo
        posi1 = pop.torneo_binario();
        posi2 = pop.torneo_binario();

        // cruzo
        if(cruce == 0)
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

        // Evaluacion
        int acierto_train;
        clasificarTrain(train, sol1, acierto_train);
        fit1 = calcularFitness(acierto_train, train.numEjemplos(), sol1);

        clasificarTrain(train, sol2, acierto_train);
        fit2 = calcularFitness(acierto_train, train.numEjemplos(), sol2);

//        auto fin = std::chrono::high_resolution_clock::now();
        // Calcular la duración en milisegundos
//        auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
        // Mostrar la duración en milisegundos
//        std::cout << "El tiempo transcurrido: " << duracion.count() << " milisegundos" << std::endl;

//        cout << iter << endl;
        iter += 2;

        // Reemplazo los 2 peores
        reemplaza_peores(sol1, fit1, sol2, fit2, pop);

    }

    return pop.mejor();
}