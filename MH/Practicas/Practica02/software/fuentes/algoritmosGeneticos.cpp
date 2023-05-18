#include "algoritmosGeneticos.h"
#include "apc.h"
#include "random.hpp"
#include <algorithm>

using namespace std;
using Random = effolkronium::random_static;

class Poblacion{
    // Una poblacion es un conjunto de pesos
    private:
        int worstFitness, bestFitness;
        vector<double> fitness_pop;
        vector<vector<double>> poblacion;
    public:
        Poblacion(int tamPoblacion, int tamPeso){
            zeros(tamPoblacion, tamPeso);
        }

        void zeros(int tamPoblacion, int tamPeso){
            poblacion.resize(tamPoblacion, vector<double>(tamPeso, 0));

        }

        int numPoblacion(){
            return poblacion.size();
        }

        int numCaracteristicas(){
            return poblacion[0].size();
        }

        vector<double> getIndividuo(int i) const{
            return poblacion[i];
        }

        vector<double> &getIndividuoModificable(int i){
            return poblacion[i];
        }

        void setIndividuo(int i, const vector<double> & individuo){
            poblacion[i] = individuo;
        }

        void nuevas_soluciones(){
            //Segun la guia desordena un vector de indices??

            for(int i = 0; i < poblacion.size(); i++){ //Matriz aleatoria
                poblacion[i] = Random::get<std::vector>(0.0, 1.0, numCaracteristicas());
            }
        }

        void calcularfitness_pop(Dataset train){
            int acierto_train, acierto_test;
            fitness_pop = vector<double>();

            for(auto w : poblacion){
                clasificarTrain(train, w, acierto_train);
                fitness_pop.push_back(calcularFitness(acierto_train, train.numEjemplos(), w));
            }

            // Obtener el peor fitness del vector
            auto minFitness = min_element(fitness_pop.begin(), fitness_pop.end());
            
            // Obtener el mejor fitness del vector
            auto maxFitness = max_element(fitness_pop.begin(), fitness_pop.end());

            // Si no está el vector vacio, guarda el peor y mejor fitness
            if (!fitness_pop.empty()) {
                worstFitness = distance(fitness_pop.begin(), minFitness);
                bestFitness = distance(fitness_pop.begin(), maxFitness);
            }
        }

        const int getPosWorst(){
            return worstFitness;
        }

        const int getPosBest(){
            return bestFitness;
        }

        const double getFitness(int pos = -1){
            return (pos == -1) ? fitness_pop[worstFitness] : fitness_pop[pos];
        }

        const vector<double> getFitness_vector() const{
            return fitness_pop;
        }

        int torneo_binario(){
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

        int worstFitnessPos(){
            return worstFitness;
        }

        int bestFitnessPos(){
            return bestFitness;
        }

        void etilismo(int betterFitness, vector<double> betterIndv){
            setIndividuo(worstFitness, betterIndv); //Cambia el peor de newpop por el mejor de pop
            worstFitness = betterFitness;
        }

        void imprimir() {
        // Imprimir la matriz
            for (int i = 0; i < poblacion.size(); ++i) {
                for (int j = 0; j < poblacion[i].size(); ++j) {
                    std::cout << poblacion[i][j] << " ";
                }
                cout << endl;
            }
        }

        void setValor(int i, int j, int valor){
            poblacion[i][j] = valor;
        }

        void copy(Poblacion otro){
            if(&otro != this){

                worstFitness = otro.worstFitness;
                bestFitness = otro.bestFitness;
                fitness_pop = otro.fitness_pop;
                
                cout << "\nSTOP1\n";
                imprimir();
                poblacion = otro.poblacion;
                cout << "\nSTOP2\n";
            }
        }

};

void aplicarTorneo(Poblacion pop, Poblacion &newpop){
    int posi;
    vector<double> fitness_pop = pop.getFitness_vector();
    for(int i = 0; i < newpop.numPoblacion(); i++){
        posi = pop.torneo_binario();
        // cout << "Mejor candidato: " << posi << " " << fitness_pop[posi] << endl;
        newpop.setIndividuo(i, pop.getIndividuo(posi));
    }
    
}

// Devuelve 2 hijos
vector<vector<double>> cruceAritmetrico(vector<double> padre1, vector<double> padre2){
    vector<vector<double>> hijo;
    hijo.resize(2); //Se generan 2 hijos

    padre1 = {0.1,0.1,0.2,0.2,0.3,0.3,0.4,0.4,0.5,0.5};
    padre2 = {0.2,0.3,0.2,0.2,0.3,0.2,0.3,0.2,0.3,0.2};
    double alpha = Random::get(0.0, 1.0);

    // cout << "Hijo: ";
    for (size_t i = 0; i < padre1.size(); ++i) {
        double gen1 = alpha * padre1[i] + (1 - alpha) * padre2[i];
        double gen2 = alpha * padre2[i] + (1 - alpha) * padre1[i];

        hijo[0].push_back(gen1);
        hijo[1].push_back(gen2);
        // cout << gen1 << " ";
    }
    // cout << endl;
    return hijo;
}

vector<double> AGG(Dataset train, int maxIters, double pcross){
    double pmut = 0.1;
    int tamPoblacion = 10;

    cout << "\n\n##############Ejecucion de AGG##############\n";

    // Cual es el tamaño de la poblacion?
    Poblacion pop(tamPoblacion, train.numCaracteristicas());

    // Nueva poblacion
    Poblacion newpop = pop;

    // Inicializar el vector
    pop.nuevas_soluciones(); // Si todo es 0 no?

    // Calcular el fitness de la poblacion en train
    pop.calcularfitness_pop(train);

    int iter = tamPoblacion;

    vector<double> sol1, sol2;
    while(iter < maxIters){
        // Selección por torneo
        aplicarTorneo(pop, newpop);

        int total_cruce = pop.numPoblacion()*pcross;

        for(int i = 0; i < total_cruce; i+=2){
            sol1 = newpop.getIndividuo(i);
            sol2 = newpop.getIndividuo(i+1);

            cruceAritmetrico(sol1, sol2);

            newpop.setIndividuo(i, sol1);
            newpop.setIndividuo(i+1, sol2);
        }

        // Mutacion
        int total_mutar = pop.numPoblacion()* pmut;
        int posi;
        for(int i = 0; i < total_mutar; i++){
            posi = Random::get(1, pop.numPoblacion()); // Posicion random
            Mov(newpop.getIndividuoModificable(i),posi,0.8); //Mutacion
        }

        // Evaluacion
        newpop.calcularfitness_pop(train);

        cout << iter << endl;
        iter += newpop.numPoblacion();
        
        // Etilismo, para no empeorar
        if (pop.getFitness(pop.getPosBest()) < newpop.getFitness(newpop.getPosBest())){
            int peor = newpop.getPosWorst();
            int mejor = pop.getPosBest();
            newpop.etilismo(mejor, pop.getIndividuo(mejor));
        }
        // Reemplazo
        pop.copy(newpop);
    }

    // pop.imprimir();

    return pop.mejor();
}
