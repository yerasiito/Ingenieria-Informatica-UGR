#include <algorithm>
#include <cmath>
#include "random.hpp"

#include "apc.h"


using namespace std;
using Random = effolkronium::random_static;

// Función para actualizar los pesos de las características
void actualizar_pesos(const Ejemplo& inst, const Dataset& dataset, vector<double>& weights, const int &leave_out) {
    double amigo_dist = INFINITY;
    double enemigo_dist = INFINITY;
    int amigo_idx, enemigo_idx;

    // Calcular las distancias de la instancia actual a todos los ejemplos del dataset
    // Se utiliza la función distancia() con pesos igual a 1
    for (int i = 0; i < dataset.numEjemplos(); i++) {
        if(i == leave_out)
            continue;

        double dist = distancia(inst, dataset.getEjemplo(i), vector<double>(dataset.numCaracteristicas(),1)); //distancia sin ponderar

        // Si la etiqueta del ejemplo es igual a la de la instancia actual, es un "amigo"
        if (inst.etiqueta == dataset.getEtiqueta(i)) { 
            // Se busca el "amigo" más cercano a la instancia actual
            if (dist < amigo_dist) { // Se omite si la distancia es 0, para evitar que la misma instancia sea considerada como "amigo"
                amigo_dist = dist;
                amigo_idx = i;
            }
        } 
        else { // Si la etiqueta del ejemplo es diferente, es un "enemigo"
            // Se busca el "enemigo" más cercano a la instancia actual
            if (dist < enemigo_dist) {
                enemigo_dist = dist;
                enemigo_idx = i;
            }
        }
    }

    // Actualizar los pesos de las características
    // Para cada característica, se resta el valor de la misma en la instancia actual al valor correspondiente en el "amigo" más cercano,
    // y se le resta el valor de la misma en la instancia actual al valor correspondiente en el "enemigo" más cercano
    for (int i = 0; i < weights.size(); i++) {
        weights[i] += fabs(inst.caracteristicas[i] - dataset.getCaracteristica(enemigo_idx, i)) - 
                      fabs(inst.caracteristicas[i] - dataset.getCaracteristica(amigo_idx, i));
    }
}

// Función principal para ejecutar el algoritmo Greedy Relief
vector<double> greedy_relief(const Dataset &dataset) {
    vector<double> weights(dataset.numCaracteristicas()); // Inicializamos vector de pesos a 0
    // Iteramos por cada ejemplo del dataset y actualizamos los pesos
    for (int i = 0; i < dataset.numEjemplos(); i++) {
        const Ejemplo& inst = dataset.getEjemplo(i);
        actualizar_pesos(inst, dataset, weights, i); // Actualizamos los pesos del ejemplo actual
    }
    // Normalizamos los pesos
    double w_max = *max_element(weights.begin(), weights.end()); // Obtenemos el peso máximo
    for(double & weight : weights){
        if(weight < 0){
            weight = 0;
        }
        else{
            weight /= w_max;
        }
    }
    return weights; // Devolvemos los pesos normalizados
}


// Funcion para clasificar un ejemplo dado un dataset
string clasificador1NN(const Dataset &train, const Ejemplo &test_ejemplo, const vector<double> &w, int leave_out) {
    const int numEjemplos = train.numEjemplos();
    double min_distance = INFINITY;
    const Ejemplo* min_ejemplo = nullptr;
    const Ejemplo* ejemplo;

    // Itera sobre todas las instancias del dataset de entrenamiento
    for (int i = 0; i < numEjemplos; i++) {
        // Ignora el mismo ejemplo
        if (i == leave_out)
            continue;

        ejemplo = &train.getEjemplo(i);
        double distance = distancia(test_ejemplo, *ejemplo, w); // Calcula la distancia entre el ejemplo de prueba y el ejemplo de entrenamiento i
        if (distance < min_distance) { // Actualiza el ejemplo con la distancia mínima
            min_distance = distance;
            min_ejemplo = ejemplo;
        }
    }

    return min_ejemplo->etiqueta; // Devuelve la etiqueta de la instancia con la distancia mínima
}



// Función principal para clasificar los datasets de train y test
void clasificar(const Dataset &train, const Dataset &test, const vector<double> &pesos, int &acierto_train, int &acierto_test, bool tasa_train){
    acierto_train = 0, acierto_test = 0;
    
    // La tasa de train es opcional
    if(tasa_train) {
        clasificarTrain(train, pesos, acierto_train);
    }
    
    // Clasificar el dataset de test
    clasificarTest(train, test, pesos, acierto_test);
}

// Función auxiliar para clasificar el dataset de entrenamiento
void clasificarTrain(const Dataset &train, const vector<double> &pesos, int &acierto_train){
    acierto_train = 0;
    for (int i = 0; i < train.numEjemplos(); i++) {
        int min_index = 0;  // Indice de la instancia con la distancia minima
        double min_distance = INFINITY;

        // Itera sobre todas las instancias del dataset
        for (int j = 0; j < train.numEjemplos(); j++) {
            // Leave one out
            if(i == j)
                continue;

            double distance = distancia(train.getEjemplo(i), train.getEjemplo(j), pesos); // Calcula la distancia entre el ejemplo de prueba y el ejemplo de entrenamiento i
            if (distance < min_distance) { // Actualiza el indice y la distancia
                min_index = j;
                min_distance = distance;
            }
        }
        if (train.getEjemplo(min_index).etiqueta == train.getEjemplo(i).etiqueta)
            acierto_train++;
    }
}

// Función auxiliar para clasificar el dataset de test
void clasificarTest(const Dataset &train, const Dataset &test, const vector<double> &pesos,int &acierto_test){
    acierto_test = 0;
    
    // Clasificar cada ejemplo del dataset de test
    for(int i = 0; i < test.numEjemplos(); i++){
        string label_test = clasificador1NN(train, test.getEjemplo(i), pesos);
        if(label_test == test.getEjemplo(i).etiqueta)
            acierto_test++;
    }
}

// Funcion para calcular la tasa de reduccion de los pesos
double calcularTasaRed(const vector<double> &pesos){
    double tasa_red = 0;
    for(auto it : pesos)
        if(it < 0.1) // Si el peso es menor que 0.1, entonces cuenta como reducido
            tasa_red++;
    return 100.0*(tasa_red/(double)pesos.size()); // Devolvemos la tasa de reduccion en porcentaje
}


double calcularFitness(const int &acierto, const int &numEjemplos, const vector<double> &pesos){
    // Calcula la tasa de clasificación y la tasa de reducción
    double tasa_clas = 100.0*(double(acierto)/double(numEjemplos));
    double tasa_red = calcularTasaRed(pesos);

    // Combina la tasa de clasificación y la tasa de reducción en una única medida de fitness
    return 0.8*tasa_clas + 0.2*tasa_red;
}

// Función para calcular el rendimiento de un algoritmo a partir de sus aciertos y pesos
vector<double> calcularRendimiento(int acierto_train, int acierto_test, const Dataset &train,
                                   const Dataset &test, const vector<double> &w, chrono::high_resolution_clock::time_point momentoInicio){
    
    // Calculamos la tasa de clasificación para el conjunto de entrenamiento y de prueba
    double tasa_clas_train = 100.0*acierto_train/train.numEjemplos();
    double tasa_clas_test = 100.0*acierto_test/test.numEjemplos();

    // Calculamos la tasa de reducción de los pesos
    double tasa_red = calcularTasaRed(w);

    // Calculamos el fitness, ponderando la tasa de clasificación del conjunto de prueba y la tasa de reducción de los pesos
    double fitness = 0.8*tasa_clas_test + 0.2*tasa_red;

    // Calculamos el tiempo transcurrido desde el inicio del algoritmo hasta el final
    auto momentoFin = chrono::high_resolution_clock::now();
    chrono::milliseconds tiempo = chrono::duration_cast<chrono::milliseconds>(momentoFin - momentoInicio);
    auto t = double(tiempo.count())/1000.0;

    // Creamos un vector con los valores de rendimiento y lo devolvemos
    vector<double> rendimiento = {tasa_clas_train, tasa_clas_test, tasa_red, fitness, t};
    return rendimiento;
}

void Mov(vector<double> &w, const int &i, const double &varianza){
    std::normal_distribution<double> distribution(0.0, sqrt(varianza));
    double z = Random::get(distribution);
    //Verificación de restricciones. Trunca w
    if(w[i]+z > 1)
        w[i] = 1;
    else if(w[i]+z < 0)
        w[i] = 0;
    else
        w[i] += z;
}