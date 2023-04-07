#include <algorithm>
#include<iomanip>
#include "acp.h"
#include "funcionesAux.h"

using namespace std;

// Función para actualizar los pesos de las características
void Greedy::actualizar_pesos(const Ejemplo& inst, const Dataset& dataset, vector<double>& weights) {
    double amigo_dist = INFINITY;
    double enemigo_dist = INFINITY;
    int amigo_idx, enemigo_idx;
;
    for (int i = 0; i < dataset.numEjemplos(); i++) {
        double dist = distancia(inst, dataset.getEjemplo(i), vector<double>(dataset.numCaracteristicas(),1)); //Pesos a 1
        if (inst.etiqueta == dataset.getEtiqueta(i)) { //Amigo
            if (dist < amigo_dist && dist > 0.0) {
                amigo_dist = dist;
                amigo_idx = i;
            }
        } 
        else { //Enemigo
            if (dist < enemigo_dist) {
                enemigo_dist = dist;
                enemigo_idx = i;
            }
        }
    }

    for (int i = 0; i < weights.size(); i++) {
        weights[i] += fabs(inst.caracteristicas[i] - dataset.getCaracteristica(enemigo_idx, i)) - 
                      fabs(inst.caracteristicas[i] - dataset.getCaracteristica(amigo_idx, i));
    }
}

// Función principal para ejecutar el algoritmo Greedy Relief
vector<double> Greedy::greedy_relief(const Dataset &dataset) {
    vector<double> weights(dataset.numCaracteristicas());
    for (int i = 0; i < dataset.numEjemplos(); i++) {
        Ejemplo inst = dataset.getEjemplo(i);
        actualizar_pesos(inst, dataset, weights);
    }
    double w_max = *max_element(weights.begin(), weights.end());
    for(int i = 0; i < weights.size();i++){
        if(weights[i] < 0){
            weights[i] = 0;
        }
        else{
            weights[i] /= w_max;
        }
    }
    return weights;
}

// Funcion para clasificar un ejemplo dado un dataset
string Clasificador::unoNN(Ejemplo test_ejemplo, Dataset train, vector<double> w) {
    int min_index = 0;
    double min_distance = INFINITY;

    for (int i = 0; i < train.numEjemplos(); i++) {
        double distance = distancia(test_ejemplo, train.getEjemplo(i), w);
        if (distance < min_distance) {
            min_index = i;
            min_distance = distance;
        }
    }
    return train.getEjemplo(min_index).etiqueta;
}

// Función principal para clasificar los datasets de train y test
void clasificar(Dataset train, Dataset test, vector<double> pesos, int &acierto_train, int &acierto_test){
    Clasificador clf;
    acierto_train = 0, acierto_test = 0;
    for(int i = 0; i < train.numEjemplos(); i++){
        string label_train = clf.unoNN(train.getEjemplo(i), train.leave_one_out(i), pesos);
        if(label_train == train.getEjemplo(i).etiqueta)
            acierto_train++;
    }
    for(int i = 0; i < test.numEjemplos(); i++){
        string label_test = clf.unoNN(test.getEjemplo(i), train, pesos);
        if(label_test == test.getEjemplo(i).etiqueta)
            acierto_test++;
    }
}

// Funcion para calcular la tasa de reduccion de los pesos
double calcularTasaRed(vector<double> pesos){
    double tasa_red = 0;
    for(auto it : pesos)
        if(it < 0.1)
            tasa_red++;
    return tasa_red = 100*(tasa_red/pesos.size());
}

// Función para calcular el rendimiento de un algoritmo apartir de sus aciertos y pesos
vector<double> calcularRendimiento(int acierto_train, int acierto_test, Dataset train, Dataset test, vector<double> w,
    chrono::high_resolution_clock::time_point momentoInicio){
    
    double tasa_clas_train = 100.0*acierto_train/train.numEjemplos();
    double tasa_clas_test = 100.0*acierto_test/test.numEjemplos();
    double tasa_red = calcularTasaRed(w);
    double fitness = 0.8*tasa_clas_test + 0.2*tasa_red;
    auto momentoFin = chrono::high_resolution_clock::now();
    chrono::milliseconds tiempo = chrono::duration_cast<chrono::milliseconds>(momentoFin - momentoInicio);
    double t = double(tiempo.count());

    vector<double> rendimiento = {tasa_clas_train, tasa_clas_test, tasa_red, fitness, t};
    return rendimiento;
}

void imprimeRendimiento(vector<vector<double>> resultados){
    cout << "\nParticion\t" << "Tasa_clas_train[%]\t" << "Tasa_clas_test[%]\t" << "Tasa_red[%]\t" << "Fitness\t\t" << "Tiempo[ms]";
    cout << fixed << setprecision(2);
    vector<double> media(resultados[0].size(),0);
    for(int i = 0; i < resultados.size(); i++){
        cout << endl;
        cout << i+1 << "\t\t";
        for(int j = 0; j < resultados[0].size(); j++){
            media[j] += resultados[i][j];
            cout << resultados[i][j] << "\t\t";
            if(j < 2)
                cout << "\t";
        }
    }
    //MEDIA
    cout << "\nMEDIA\t\t";
    for(int i = 0; i < resultados[0].size(); i++){
        cout << media[i]/5.0 << "\t\t";
        if(i < 2)
            cout << "\t";
    }
    cout << endl;
}

void imprimePesos(vector<vector<double>> pesosP){
    std::cout << fixed << setprecision(5) << endl;
    std::cout << "----------------------------Pesos por particion:----------------------------" << endl;
    for(int i = 0; i < pesosP.size(); i++){
        std::cout << "Particion " << i+1 << ": ";
        for(int j = 0; j < pesosP[0].size(); j++)
            std::cout << pesosP[i][j] << " ";
        std::cout << endl << endl;
    }
}

void imprimePesoMedio(vector<double> pesosT){
    std::cout << "Pesos medios:\n";
    for(int i = 0; i < pesosT.size(); i++){
        pesosT[i] /= 5;
        std::cout << pesosT[i] << " ";
    }
    std::cout << endl;
}