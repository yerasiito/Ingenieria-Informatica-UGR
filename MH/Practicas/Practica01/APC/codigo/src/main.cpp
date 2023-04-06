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

    for(int i = 1; i <= 5; i++){
        string file = path + fichero + "_" + to_string(i) + ".arff";
        ifstream f(file);
        
        //Lee el fichero y lo integra en el objeto dataset. Si falla entra en el if
        if(i == (5-k)){
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


int main(int argc, char** argv) {
    Dataset train,test;
    vector<double> pesosMedios = {};
    vector<vector<double>> pesosT;

    std::cout << "Particion\t" << "Tasa_clas[%]\t" << "Tasa_red[%]\t" << "Fitness\t\t" << "Tiempo[s]\n";
    for(int i = 0; i < 5; i++){
        auto momentoInicio = high_resolution_clock::now();
        train = {}, test = {};
        //Lee el archivo pasado por parámetro
        if(leerFicheros(argv[1], train, test, i)){
            std::cout << "Ha surgido un error leyendo los datos\n";
            return EXIT_FAILURE;
        }
        
        //Normalizamos los datos
        normalizar(train, test);

        //Calculamos el rendimiento del clasificador con greedy
        vector<double> pesos;
        Greedy gr;
        pesos = gr.greedy_relief(train);

        pesosT.push_back(pesos); //Para imprimirlos al final

        Clasificador clf;
        int acierto = 0, error = 0;
        //Test
        for(int i = 0; i < test.numEjemplos(); i++){
            int label = clf.unoNNponderado(test.getEjemplo(i), train, pesos);
            if(label == test.getEjemplo(i).etiqueta){
                acierto++;
            }
            else
                error++;
        }
        double tasa_clas = 100*double(acierto)/double(test.numEjemplos());
        double tasa_red = calcularTasaRed(pesos);
        double fitness = 0.8*tasa_clas + 0.2*tasa_red;
        auto momentoFin = high_resolution_clock::now();
        milliseconds tiempo = duration_cast<std::chrono::milliseconds>(momentoFin - momentoInicio);
        std::cout << fixed << setprecision(2) << i+1 << "\t\t" << tasa_clas << "\t\t" 
                  << tasa_red << "\t\t" << fitness << "\t\t" << double(tiempo.count()/1000.0) << endl;

        if(i == 0){
            pesosMedios = pesos;
        }
        else{
            for(int i = 0; i < pesosMedios.size(); i++)
                pesosMedios[i] += pesos[i];
        }
    }
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