#include <cmath>
#include <iostream>
#include <iomanip>
#include <filesystem>
#include "dataset.h"
#include "acp.h"
#include "funcionesAux.h"

using namespace std;

vector<string> nombreDatasets = {"diabetes", "ozone-320", "spectf-heart"}; //Datasets a utilizar

int main(int argc, char** argv) {
    int acierto_train, acierto_test;
    string algoritmo = "1-NN";
    vector<double> pesosMedios;
    vector<vector<double>> rendimiento, pesosParticiones;
    Dataset train,test;

    //Lee el algoritmo pasado por parametro (si se han pasado parametros)
    if (argc != 1)
        algoritmo = argv[1];
    //Devuelve error en caso de pasar un parametro desconocido
    if(algoritmo != "1-NN" && algoritmo != "greedy"){
        cerr << "Algoritmo " << argv[1] << " desconocido. Elige: 'sin parametro', greedy o bl.\n";
        return EXIT_FAILURE;
    }

    //Lee todos los dataset con sus respectivos ficheros
    while(!nombreDatasets.empty()){
        string fichero = nombreDatasets.front(); //Obtiene el primer elemento
        nombreDatasets.erase(nombreDatasets.begin()); //Lo saca del vector

        //Inicializar
        rendimiento = {}, pesosParticiones = {}, pesosMedios = {};

        for(int i = 0; i < 5; i++){
            //Lee los archivos del dataset seleccionado
            if(leerFicheros(fichero, train, test, i)){
                std::cout << "Ha surgido un error leyendo los datos\n";
                return EXIT_FAILURE;
            }

            //Inicializae variables
            if(i == 0) //en la primera iteracion
                pesosMedios.resize(train.numCaracteristicas(),0);
            vector<double> pesos(train.numCaracteristicas(),1);  //en todas las iteraciones

            //Normalizamos los datos
            normalizar(train, test);

            //Ejecutamos Greedy Relief
            auto momentoInicio = chrono::high_resolution_clock::now(); //Contamos el tiempo de los algoritmos
            if(algoritmo == "greedy"){
                Greedy gr;
                pesos = gr.greedy_relief(train);
            }

            //Ejecutamos el clasificador 1NN
            clasificar(train, test, pesos, acierto_train, acierto_test);

            //Guardamos los resultados en una matriz/tabla de rendimiento
            rendimiento.push_back(calcularRendimiento(acierto_train, acierto_test, train, test, pesos, momentoInicio));

            for(int j = 0; j < pesosMedios.size(); j++)
                pesosMedios[j] += pesos[j];

            pesosParticiones.push_back(pesos); //Para imprimirlos al final
        }
        /*Resultados del clasificador*/
        std::cout << "--------------------------------------Clasificador (" << algoritmo << "):" << fichero << "-------------------------------------";
        imprimeRendimiento(rendimiento); //Imprime la matriz/tabla de rendimiento

        // //Imprime todos los pesos por particion
        // imprimePesos(pesosParticiones);

        imprimePesoMedio(pesosMedios);
    }

    return 0;
}