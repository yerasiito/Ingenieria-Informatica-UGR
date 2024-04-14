
#include "poblacion.h"
#include "random.hpp"
#include "apc.h"

using namespace std;
using Random = effolkronium::random_static;

bool compare(const std::pair<double, int>& a, const std::pair<double, int>& b) {
    return a.first < b.first;
}

Poblacion::Poblacion(){
    worstFitness = -1;
    worstSecondFitness = -1;
    bestFitness = -1;
    meanFitness = 0;
    if(!poblacion.empty())
        poblacion.clear();
    if(!fitness_pop.empty())
        fitness_pop.clear();
}

[[nodiscard]] int Poblacion::numPoblacion() const{
    return (int) poblacion.size();
}

[[nodiscard]] int Poblacion::numCaracteristicas() const{
    return (int) poblacion[0].size();
}

vector<double> & Poblacion::getMIndividuo(int i){
    fitness_pop[i].second = false;
    return poblacion[i];
}

[[nodiscard]] vector<double> Poblacion::getIndividuo(int i) const{
    return poblacion[i];
}

void Poblacion::addIndividuo(const vector<double> & individuo){
    poblacion.push_back(individuo);
    fitness_pop.emplace_back(-1, false);
}

void Poblacion::setIndividuo(int i, const vector<double> & individuo){
    if(poblacion[i] != individuo)
        fitness_pop[i].second = false;

    poblacion[i] = individuo;
}

void Poblacion::setFitness(int i, double fitness){
    fitness_pop[i].first = fitness;
    fitness_pop[i].second = true;
    meanFitness = (meanFitness + fitness) / 2.0;

    if(fitness > fitness_pop[bestFitness].first){
        bestFitness = i;
        fitness_pop[i].first = fitness;
    }

}

void Poblacion::setIndividuoyFitness(int i, const vector<double> & individuo, double fitness){
    poblacion[i] = individuo;
    setFitness(i, fitness);
}

void Poblacion::nuevas_soluciones(int tamPoblacion, int numCaracteristicas){
    vector<double> nueva;

    if(!poblacion.empty())
        poblacion.clear();

    for(int i = 0; i < tamPoblacion; i++){ //Matriz aleatoria
        nueva = Random::get<std::vector>(0.0, 1.0, numCaracteristicas);

        // Verificar restricciones
        checkPesos(nueva);

        // Añadir nueva solucion
        poblacion.push_back(nueva);
        fitness_pop.emplace_back(-1, false);
    }
}

bool Poblacion::estaEvaluado(int i){
    return i < fitness_pop.size() && fitness_pop[i].second;
}

void Poblacion::calcularfitness_pop(const Dataset& train, int &iter){
    for(int i = 0; i < fitness_pop.size(); i++){
        if(estaEvaluado(i))
            continue;

        fitness_pop[i].first = funObjetivo(train, poblacion[i]);
        fitness_pop[i].second = true;

        meanFitness += fitness_pop[i].first;
        iter++;
    }

    // Obtener el fitness medio
    meanFitness /= (double) numPoblacion();

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

[[nodiscard]] double Poblacion::getMeanFitness() const{
    return meanFitness;
}

[[nodiscard]] int Poblacion::getPosWorst() const{
    return worstFitness;
}

[[nodiscard]] int Poblacion::getSecondPosWorst() const{
    return worstSecondFitness;
}

[[nodiscard]] int Poblacion::getPosBest() const{
    return bestFitness;
}

double Poblacion::getFitness(int pos){
    return (pos == -1) ? fitness_pop[worstFitness].first : fitness_pop[pos].first;
}

[[nodiscard]] vector<int> Poblacion::getOrderedFitness() const{
    std::vector<std::pair<double, int>> indicesValores;
    for (int i = 0; i < fitness_pop.size(); ++i) {
        indicesValores.emplace_back(fitness_pop[i].first, i);
    }
    std::sort(indicesValores.begin(), indicesValores.end(), compare);

    std::vector<int> indicesOrdenados;
    for (const auto& elemento : indicesValores) {
        indicesOrdenados.push_back(elemento.second);
    }

    return indicesOrdenados;
}

[[nodiscard]] int Poblacion::torneo_binario() const{
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

vector<double> Poblacion::mejor(){
    return poblacion[bestFitness];
}

void Poblacion::elitismo(int betterFitness, const vector<double>& betterIndv){
    setIndividuo(worstFitness, betterIndv); //Cambia el peor de newpop por el mejor de pop
    worstFitness = betterFitness;
}

void Poblacion::copy(Poblacion otro){
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

void Poblacion::clear(){
    worstFitness = -1;
    bestFitness = -1;
    if(!poblacion.empty())
        poblacion.clear();
    if(!fitness_pop.empty())
        fitness_pop.clear();
}