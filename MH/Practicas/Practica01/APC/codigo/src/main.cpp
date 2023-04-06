#include <cmath>
#include "acp.h"
#include "funcionesAux.h"
#include <iostream>
#include <iomanip>
#include <filesystem>
#include <chrono>
using namespace std;
using namespace std::chrono;

string path = "../Instancias_APC/";

/**
 * @brief lee los ficheros
 * @param fichero el tipo de datos a leer, puede ser: diabetes, ozono, spearth
 * @param train el conjunto de datos de entrenamiento
 * @param el conjunto de datos de test
 * @param i el indice de particion (el numero indica el test)
*/
int leerFicheros(string fichero, Dataset &train, Dataset &test, int k){ 
    if(fichero != "diabetes" && fichero != "ozone-320" && fichero != "spectf-heart"){
        std::cout << "Los parametros admitidos son: diabetes, ozone-320 o spectf-heart\n";
        return EXIT_FAILURE;
    }
    train = {}, test = {};
    for(int i = 1; i <= 5; i++){
        string file = path + fichero + "_" + to_string(i) + ".arff";
        ifstream f(file);
        
        //Lee el fichero y lo integra en el objeto dataset. Si falla entra en el if
        if(i == k+1){
            if(test.read(f)){
                cerr << "No se pudo abrir - '"
                    << file << "'" << endl;
                return EXIT_FAILURE;
            }
        }
        else if(train.read(f)){
            cerr << "No se pudo abrir - '"
                << file << "'" << endl;
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

vector<double> calcularRendimiento(int i, int acierto_train, int acierto_test, Dataset train, Dataset test, high_resolution_clock::time_point momentoInicio){
    double tasa_clas_train = 100.0*acierto_train/train.numEjemplos();
    double tasa_clas_test = 100.0*acierto_test/test.numEjemplos();
    double tasa_red = 0;
    double fitness = 0.8*tasa_clas_test + 0.2*tasa_red;
    auto momentoFin = high_resolution_clock::now();
    milliseconds tiempo = duration_cast<std::chrono::milliseconds>(momentoFin - momentoInicio);
    double t = double(tiempo.count()/1000.0);

    vector<double> rendimiento = {double(i),tasa_clas_train, tasa_clas_test, tasa_red, fitness, t};
    return rendimiento;
}

void imprimeResultados(vector<vector<double>> resultados){
    std::cout << "Particion\t" << "Tasa_clas_train[%]\t" << "Tasa_clas_test[%]\t" << "Tasa_red[%]\t" << "Fitness\t\t" << "Tiempo[s]";
    cout << fixed << setprecision(2);
    for(int i = 0; i < resultados.size(); i++){
        cout << endl;
        for(int j = 0; j < resultados[0].size(); j++){
            cout << resultados[i][j] << "\t\t";
            if(j > 0 && j < 3)
                cout << "\t";
        }

    }
}

int main(int argc, char** argv) {
    Dataset train,test;
    vector<double> pesos;
    vector<double> pesosMedios = {};
    vector<vector<double>> pesosT;

    vector<vector<double>> uno, dos;

    /**Parte 0 y 1: 1NN, GREEDY y resultados**/
    for(int i = 0; i < 5; i++){
        auto momentoInicio = high_resolution_clock::now();

        //Lee el archivo pasado por parámetro
        if(leerFicheros(argv[1], train, test, i)){
            std::cout << "Ha surgido un error leyendo los datos\n";
            return EXIT_FAILURE;
        }
        
        //Normalizamos los datos
        normalizar(train, test);

        Clasificador clf;
        //Calculamos solo con 1NN
        int acierto_train = 0, acierto_test = 0;
        pesos = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
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

        uno.push_back(calcularRendimiento(i, acierto_train, acierto_test, train, test, momentoInicio));

        //Calculamos el rendimiento del clasificador con greedy
        momentoInicio = high_resolution_clock::now();
        Greedy gr;
        pesos = gr.greedy_relief(train);

        pesosT.push_back(pesos); //Para imprimirlos al final

        acierto_test = 0;
        //Calculamos el rendimiento del algoritmo con test
        for(int i = 0; i < test.numEjemplos(); i++){
            string label = clf.unoNN(test.getEjemplo(i), train, pesos);
            if(label == test.getEjemplo(i).etiqueta)
                acierto_test++;
        }
        dos.push_back(calcularRendimiento(i, acierto_train, acierto_test, train, test, momentoInicio));

        if(i == 0){
            pesosMedios = pesos;
        }
        else{
            for(int i = 0; i < pesosMedios.size(); i++)
                pesosMedios[i] += pesos[i];
        }
    }
    imprimeResultados(uno);

    // std::cout << fixed << setprecision(5);
    // std::cout << "Pesos por particion: " << endl;
    // for(int i = 0; i < pesosT.size(); i++){
    //     std::cout << "Particion " << i+1 << ": ";
    //     for(int j = 0; j < pesosT[0].size(); j++)
    //         std::cout << pesosT[i][j] << " ";
    //     std::cout << endl << endl;
    // }

    std::cout << "Pesos medios:\n";
    for(int i = 0; i < pesosMedios.size(); i++){
        pesosMedios[i] /= 5;
        std::cout << pesosMedios[i] << " ";
    }
    std::cout << endl;

    return 0;
}