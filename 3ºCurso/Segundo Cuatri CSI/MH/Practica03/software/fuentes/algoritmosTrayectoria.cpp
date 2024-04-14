#include "algoritmosTrayectoria.h"
#include "busquedaLocal.h"
#include "apc.h"
#include "random.hpp"
#include "enfriamientoSimulado.h"

using namespace std;
using Random = effolkronium::random_static;

// GLOBALES
int MIN_MUTACION = 2;
int FACTOR_REINICIO = 0.10;

double BMB(const Dataset &train, std::vector<double> &Sact, int maxiterBMB, int maxiterBL){
    int i = 0;
    double objetivo, mejorObjetivo = -1;
    vector<double> S;

    // Algoritmo BMB, aplicar BL con pesos random hasta maxiterBMB
    while(i < maxiterBMB){
        // La busqueda local ya genera un vector aleatorio internamente si está vacio
        S.clear();
//         S = Random::get<std::vector>(0.0, 1.0, train.numCaracteristicas());

        // Evaluar BL
        objetivo = busquedaLocal(train, S, maxiterBL);

        // Guarda si es mejor
        if(objetivo > mejorObjetivo){
            Sact = S;
            mejorObjetivo = objetivo;
        }
        i++;
    }
    return mejorObjetivo;
}

double ILS(const Dataset &train, std::vector<double> &Sact, int maxiterILS, int maxiterBL){
    std::vector<double> S; // Vector de pesos
    double objetivo, mejorObjetivo; // Objetivos
    int i = 0, n = train.numCaracteristicas(); // Contador de bucle interno y BL
    vector<int> indices, tindices; // Indices de mutacion

    // Al menos mute 2
    int t = FACTOR_REINICIO * n;
    if(t < MIN_MUTACION)
        t = MIN_MUTACION;

    // Generar solucion inicial
    generaSolucionInicial(S, n);

    // Obtener primer mejor
    objetivo = busquedaLocal(train, S, maxiterBL);

    // Guardar mejor
    Sact = S;
    mejorObjetivo = objetivo;

    // Generar indices de mutacion
    int k = 1+(maxiterILS*t)/n;
    mezclarkIndices(indices, n, k);

    vector<int>::iterator it, fin;
    it = indices.begin();
    // Algoritmmo ILS
    while(i < maxiterILS) {

        // Obtiene t indices sin repeticion
        fin = (it + t > indices.end()) ? indices.end() : it + t;

        tindices = {it, fin}; // Obtiene el intervalo

        // Mutar mejor solucion (operador ILS)
        S = cMov(Sact, tindices, VARIANZA);

        objetivo = busquedaLocal(train, S, maxiterBL);

        // Guarda si mejora
        if (objetivo > mejorObjetivo) {
            mejorObjetivo = objetivo;
            Sact = S;
        }
        i++;
        it += t;
    }

    return mejorObjetivo;
}

double VNS(const Dataset &train, std::vector<double> &Sact, int maxiterVNS, int maxiterBL){
    int KMAX = 3; // Numero de atributos mutados simultaneos
    int n = train.numCaracteristicas(); // Numero de caracteristicas
    int i = 0; // i -> contador bucle interno, iter -> contador BL

    // Vectores de mutacion, para evitar repeticion
    vector<int> indices, tindices;

    std::vector<double> S; // Vector de pesos

    double objetivo, mejorObjetivo; // Valores de funcion objetivo

    // Al menos mute 2
    int t = FACTOR_REINICIO * n;
    if(t < MIN_MUTACION)
        t = MIN_MUTACION;

    // Generar solucion inicial
    generaSolucionInicial(S, n);

    // Obtener primer mejor
    objetivo = busquedaLocal(train, S, maxiterBL);

    // Guardar mejor
    Sact = S;
    mejorObjetivo = objetivo;

    // Generar indices de mutacion
    int kmut = (maxiterVNS*t)/n;
    mezclarkIndices(indices, n, kmut);

    // Intervalos de indice de mutacion en funcion de k (evita repeticion)
    int k = 1;
    vector<int>::iterator it, fin;
    it = indices.begin();
    // Algoritmmo VNS
    while(i < maxiterVNS) {
        // Obtiene t indices sin repeticion

        fin = (it + t > indices.end()) ? indices.end() : it + t;
        tindices = {it, fin}; // Obtiene el intervalo

        // Modificar mejor solucion
        S = cMov(Sact, tindices, VARIANZA);

        // Llamada a busqueda local. k indica cuantos atributos se mutan
        objetivo = busquedaLocal(train, S, maxiterBL, k);

        // Guarda si mejora
        if (objetivo > mejorObjetivo) {
            mejorObjetivo = objetivo;
            Sact = S;
            k = 1;
        }
        else
            if(k <= KMAX) // Mientras k no llega a max
                k++;
            else
                k = 1; // Sino Reinicia

        i++;
    }

    return mejorObjetivo;
}

double ILS_ES(const Dataset &train, std::vector<double> &Sact, int maxiterILS, int maxiterES){
    std::vector<double> S; // Vector de pesos
    double objetivo, mejorObjetivo; // Objetivos
    int i = 0, n = train.numCaracteristicas(); // Contador de bucle interno y BL
    vector<int> indices, tindices; // Indices de mutacion

    // Al menos mute 2
    int t = FACTOR_REINICIO * n;
    if(t < MIN_MUTACION)
        t = MIN_MUTACION;

    // Generar solucion inicial
    generaSolucionInicial(S, n);

    // Obtener primer mejor
    objetivo = ES(train, S, maxiterES);

    // Guardar mejor
    Sact = S;
    mejorObjetivo = objetivo;

    // Generar indices de mutacion
    int k = 1+(maxiterILS*t)/n;
    mezclarkIndices(indices, n, k);

    vector<int>::iterator it, fin;
    it = indices.begin();
    // Algoritmmo ILS
    while(i < maxiterILS) {

        // Obtiene t indices sin repeticion
        fin = (it + t > indices.end()) ? indices.end() : it + t;

        tindices = {it, fin}; // Obtiene el intervalo

        // Mutar mejor solucion (operador ILS)
        S = cMov(Sact, tindices, VARIANZA);

        objetivo = ES(train, S, 1000);

        // Guarda si mejora
        if (objetivo > mejorObjetivo) {
            mejorObjetivo = objetivo;
            Sact = S;
        }
        i++;
        it += t;
    }

    return mejorObjetivo;
}