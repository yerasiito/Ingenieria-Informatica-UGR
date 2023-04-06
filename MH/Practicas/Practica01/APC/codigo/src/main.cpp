#include <cmath>
#include "acp.h"
#include "funcionesAux.h"
#include <iostream>
#include <iomanip>
#include <filesystem>

using namespace std;

string path = "../Instancias_APC/";

/**
 * @brief lee los ficheros
 * @param fichero el tipo de datos a leer, puede ser: diabetes, ozono, spearth
 * @param train el conjunto de datos de entrenamiento
 * @param el conjunto de datos de test
 * @param i el indice de particion (el numero indica el test)
*/
int leerFicheros(string fichero, Dataset &train, Dataset &test, int k){ 
    if(fichero == "diabetes"){
        for(int i = 0; i < 5; i++){
            string file = path + fichero + "_" + to_string(i+1) + ".arff";
            ifstream f(file);
            
            //Lee el fichero y lo integra en el objeto dataset. Si falla entra en el if
            if(i == k){
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
    }
    else{
        cout << "Los parametros admitidos son: diabetes, \n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


int main(int argc, char** argv) {
    Dataset train,test;
    vector<double> pesosMedios = {};

    cout << "Particion\t" << "Train[%]\t" << "Test[%]\t\t" << "Reduccion[%]\t" << "Fitness\n";
    for(int i = 0; i < 5; i++){
        train = {}, test = {};
        //Lee el archivo pasado por parámetro
        if(leerFicheros(argv[1], train, test, i)){
            cout << "Ha surgido un error leyendo los datos\n";
            return EXIT_FAILURE;
        }
        
        //Normalizamos los datos
        Dataset trainN = train.normalizar();
        Dataset testN = test.normalizar();

        //Calculamos el rendimiento del clasificador con greedy
        vector<double> pesos;
        Greedy gr;
        pesos = gr.greedy_relief(trainN);

        Clasificador clf;
        double acierto = 0, error = 0;
        Dataset trainset = trainN;
        //Calcula para train
        for(int i = 0; i < trainN.numEjemplos(); i++){
            int label = clf.unoNNponderado(trainN.getEjemplo(i), trainN, pesos);
            trainset.getEjemplo(i).etiqueta = label;
            if(label == trainN.getEjemplo(i).etiqueta){
                acierto++;
            }
            else
                error++;
        }
        double tasa_clas_train = 100*double(acierto)/double(trainN.numEjemplos());
        acierto = 0, error = 0;
        //Calcula para test
        Dataset testset = testN;
        for(int i = 0; i < testN.numEjemplos(); i++){
            int label = clf.unoNNponderado(testN.getEjemplo(i), trainN, pesos);
            testset.getEjemplo(i).etiqueta = label;
            if(label == testset.getEjemplo(i).etiqueta){
                acierto++;
            }
            else
                error++;
        }

        double tasa_clas_test = 100*double(acierto)/double(testN.numEjemplos());
        double tasa_red = calcularTasaRed(pesos);
        double fitness = 0.8*tasa_clas_train + 0.2*tasa_red;
        cout << i+1 << "\t\t" << tasa_clas_train << "\t\t" << tasa_clas_test << "\t\t" << tasa_red << "\t\t" << fitness << endl;

        if(i == 0){
            pesosMedios = pesos;
        }
        else{
            for(int i = 0; i < pesosMedios.size(); i++)
                pesosMedios[i] += pesos[i];
        }
    }

    cout << "Pesos medios:\n";
    for(int i = 0; i < pesosMedios.size(); i++){
        pesosMedios[i] /= 5;
        cout << pesosMedios[i] << " ";
    }
    cout << endl;

    return 0;
}