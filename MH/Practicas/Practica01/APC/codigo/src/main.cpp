#include <cmath>
#include "acp.h"
#include "funcionesAux.h"
#include <iostream>
#include <iomanip>
#include <filesystem>
#include <chrono>
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

vector<double> calcularRendimiento(int i, int acierto_train, int acierto_test, Dataset train, Dataset test, vector<double> w,
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

void imprimeResultados(vector<vector<double>> resultados){
    std::cout << "\nParticion\t" << "Tasa_clas_train[%]\t" << "Tasa_clas_test[%]\t" << "Tasa_red[%]\t" << "Fitness\t\t" << "Tiempo[ms]";
    std::cout << fixed << setprecision(2);
    vector<double> media(resultados[0].size(),0);
    for(int i = 0; i < resultados.size(); i++){
        std::cout << endl;
        std::cout << i+1 << "\t\t";
        for(int j = 0; j < resultados[0].size(); j++){
            media[j] += resultados[i][j];
            std::cout << resultados[i][j] << "\t\t";
            if(j < 2)
                std::cout << "\t";
        }
    }
    //MEDIA
    std::cout << "\nMEDIA\t\t";
    for(int i = 0; i < resultados[0].size(); i++){
        std::cout << media[i]/5.0 << "\t\t";
        if(i < 2)
            std::cout << "\t";
    }
    std::cout << endl;
}

void imprimePesoMedio(vector<double> pesos){
    std::cout << "Pesos medios:\n";
    for(int i = 0; i < pesos.size(); i++){
        pesos[i] /= 5;
        std::cout << pesos[i] << " ";
    }
    std::cout << endl;
}

void imprimePesos(vector<vector<double>> pesosT){
    std::cout << fixed << setprecision(5) << endl;
    std::cout << "----------------------------Pesos por particion:----------------------------" << endl;
    for(int i = 0; i < pesosT.size(); i++){
        std::cout << "Particion " << i+1 << ": ";
        for(int j = 0; j < pesosT[0].size(); j++)
            std::cout << pesosT[i][j] << " ";
        std::cout << endl << endl;
    }
}

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

int main(int argc, char** argv) {
    int acierto_train, acierto_test;
    Dataset train,test;
    vector<double> pesosMedios;
    vector<vector<double>> pesosParticiones;
    vector<vector<double>> resultados;
    vector<string> ficheros = {"diabetes", "ozone-320", "spectf-heart"};
    string algoritmo = "1-NN";
    if (argc != 1)
        algoritmo = argv[1];
    
    if(algoritmo != "1-NN" && algoritmo != "greedy"){
        cerr << "Algoritmo " << argv[1] << " desconocido. Elige: 'sin parametro', greedy o bl.\n";
        return EXIT_FAILURE;
    }
    //Lee todos los dataset
    while(!ficheros.empty()){
        string fichero = ficheros.front(); //Obtiene el primer elemento
        ficheros.erase(ficheros.begin()); //Lo saca del vector

        //Inicializar
        pesosParticiones = {};
        pesosMedios = {};
        resultados = {};
        for(int i = 0; i < 5; i++){
            //Lee los archivos con el nombre pasado por parámetro
            if(leerFicheros(fichero, train, test, i)){
                std::cout << "Ha surgido un error leyendo los datos\n";
                return EXIT_FAILURE;
            }

            //Inicializa variables
            if(i == 0) //en la primera iteracion
                pesosMedios.resize(train.numCaracteristicas(),0);
            vector<double> pesos(train.numCaracteristicas(),1);  //en todas las iteraciones

            //Normalizamos los datos
            normalizar(train, test);


            //Ejecutamos Greedy Relief
            if(algoritmo == "greedy"){
                Greedy gr;
                pesos = gr.greedy_relief(train);
            }

            //Ejecutamos 1NN
            auto momentoInicio = chrono::high_resolution_clock::now();
            clasificar(train, test, pesos, acierto_train, acierto_test);
            resultados.push_back(calcularRendimiento(i, acierto_train, acierto_test, train, test, pesos, momentoInicio));

            for(int j = 0; j < pesosMedios.size(); j++){
                pesosMedios[j] += pesos[j];
            }

            pesosParticiones.push_back(pesos); //Para imprimirlos al final
        }
        //Clasificador 1NN sin pesos (todo a 1)
        std::cout << "--------------------------------------Clasificador (" << algoritmo << "):" << fichero << "-------------------------------------";
        imprimeResultados(resultados);

        // //Imprime todos los pesos por particion
        // imprimePesos(pesosParticiones);

        //Imprime el peso medio
        imprimePesoMedio(pesosMedios);
    }

    return 0;
}