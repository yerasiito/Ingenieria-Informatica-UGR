#include "enfriamientoSimulado.h"
#include "apc.h"
#include "busquedaLocal.h"
#include <vector>
#include <cmath>
#include "random.hpp"
#include <iomanip>

using namespace std;
using Random = effolkronium::random_static;

// CONSTANTES
double MU = 0.3;
double PHI = 0.2;

// PARAMETROS DE EJECUCION
int MAX_VECINOS = 0;
int MAX_EXITOS = 0;
int M = 0;
int MAX_ITER_ES = 0;
double Tf = std::pow(10, -4);

double CalculoBeta(double T0) {
    return (T0 - Tf) / (M * T0 * Tf);
}

// Cauchy Modificado
double MecanismoEnfriamientoG(double tK, double beta) {
    return tK / (1.0 + beta * tK);
}

double FijarTemperaturaZero(double fSolucion){
    double t0 = (MU * fSolucion) / (-log(PHI));

    // Debe ser menor que la inicial
    while(Tf > t0){
        Tf = Tf / 100;
    }
    return t0;
}

bool CondicionEnfriamiento(int nVecinos, int vecinosAceptados){
    return nVecinos >= MAX_VECINOS or vecinosAceptados >= MAX_EXITOS;
}

bool CondicionParadaES(int evaluaciones, int exitos) {
    // Si se cumple algo de esto, devuelve TRUE (y parará)
    return evaluaciones >= MAX_ITER_ES or exitos == 0;
}

double ES(const Dataset &train, std::vector<double> &Sact, int maxiter) {
    int n = train.numCaracteristicas(), indice, aceptados = 0;
    int vecinos;
    double incrementoF;
    bool enfriamiento;

    MAX_VECINOS = 10*n;
    MAX_EXITOS = 0.1*MAX_VECINOS;
    M = maxiter/MAX_VECINOS;
    MAX_ITER_ES = maxiter;

    // Generar vector inicial si Sact está vacío
    if(Sact.empty()) {
        generaSolucionInicial(Sact, n);
    }
    vector<double> S(Sact), Sprima;  // Guardará la solución actual

    // Guarda el mejor
    double fS = funObjetivo(train, S), fPrima;  // Guardará la función objetivo actual
    double fBest = fS;  // Guardará la mejor función objetivo de la mejor solución

    // Fijar temperatura inicial
    double t = FijarTemperaturaZero(fBest); // es el coste inicial
    double beta = CalculoBeta(t); // Calcula beta con la t0
    int eval = 0;
    bool parada = false;

    while (!parada) {  // CONDICION DE PARADA
        vecinos = 0;
        aceptados = 0;
        enfriamiento = false;

        // L(T) -> Bucle interno
        while (!enfriamiento) {
            // Generar vecino
            indice = Random::get(0, n);

            Sprima = cMov(S, {indice},VARIANZA); //Recibe un vector de un elemento

            vecinos++;  // Se ha generado un vecino

            // Calcular objetivo tras mutacion
            fPrima = funObjetivo(train, Sprima);
            eval++;  // Se evalua objetivo

            // Calcular diferencia
            incrementoF = fPrima - fS;

            double u = Random::get(0.0, 1.0); // Probabilidad de una mala
            // Maximizar
            if (incrementoF > 0.0 || (u <= exp(incrementoF / t))) {

                S = Sprima;  // La solución actual ahora es sPrima
                fS = fPrima;
                aceptados++;  // Se considera un éxito

                if (fS > fBest) {
                    Sact = S;
                    fBest = fS;
                }
            }
            enfriamiento = CondicionEnfriamiento(vecinos, aceptados);
        }

        t = MecanismoEnfriamientoG(t, beta);  // Cauchy Modificado
        eval++;  // Se evalua objetivo
        parada = CondicionParadaES(eval, aceptados);
    }

    return fBest;
}