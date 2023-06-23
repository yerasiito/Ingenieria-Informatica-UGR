//
// Created by yerasito on 23/06/23.
//

#ifndef PRACTICA2_POBLACION_H
#define PRACTICA2_POBLACION_H

#include <vector>
#include "dataset.h"

class Poblacion {
    // Una poblacion es un conjunto de pesos
private:
    int worstFitness, worstSecondFitness, bestFitness;
    double meanFitness;
    std::vector<std::pair<double, bool>> fitness_pop;
    std::vector<std::vector<double>> poblacion;
public:
    Poblacion();

    [[nodiscard]] int numPoblacion() const;
    [[nodiscard]] int numCaracteristicas() const;
    std::vector<double> & getMIndividuo(int i);
    [[nodiscard]] std::vector<double> getIndividuo(int i) const;
    void addIndividuo(const std::vector<double> & individuo);
    void setIndividuo(int i, const std::vector<double> & individuo);
    void setFitness(int i, double fitness);
    void setIndividuoyFitness(int i, const std::vector<double> & individuo, double fitness);
    void nuevas_soluciones(int tamPoblacion, int numCaracteristicas);
    bool estaEvaluado(int i);
    void calcularfitness_pop(const Dataset& train, int &iter);
    [[nodiscard]] double getMeanFitness() const;
    [[nodiscard]] int getPosWorst() const;
    [[nodiscard]] int getSecondPosWorst() const;
    [[nodiscard]] int getPosBest() const;
    double getFitness(int pos = -1);
    [[nodiscard]] std::vector<int> getOrderedFitness() const;
    [[nodiscard]] int torneo_binario() const;
    std::vector<double> mejor();
    void elitismo(int betterFitness, const std::vector<double>& betterIndv);
    void copy(Poblacion otro);
    void clear();

};


#endif //PRACTICA2_POBLACION_H
