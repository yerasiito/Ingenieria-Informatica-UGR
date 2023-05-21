#include <iomanip>
#include <map>
#include "random.hpp"
#include "busquedaLocal.cpp"
#include "algoritmosGeneticos.h"

using namespace std;
using Random = effolkronium::random_static;

vector<string> algoritmos { "oneNN", "Greedy", "BL"};
vector<string> algoritmosGeneticos {"AGG", "AGE", "AM1"};
vector<string> operadores {"Aritmetrico", "BLX"};
vector<string> nombreDatasets = {"diabetes", "ozone-320", "spectf-heart"}; // Datasets a utilizar

bool isInContainer(const std::vector<std::string>& container, std::string_view element) {
    return std::find(container.begin(), container.end(), element) != container.end();
}

void showErrorUnknownAlgorithm(std::string_view algorithm) {
    std::cerr << "Algoritmo '" << algorithm << "' desconocido. Elige: 'sin parametro', oneNN, Greedy, BL o AGG.\n";
}

void showErrorUnknownOperator(std::string_view op) {
    std::cerr << "Operador '" << op << "' desconocido. Elige: 'sin parametro', Aritmetrico o BLX.\n";
}

int main(int argc, char **argv)
{
    int ficheros = 5;
    long int seed;

    int acierto_train, acierto_test;
    string algoritmo = "oneNN", operador = "BLX";
    vector<double> pesosMedios, resultadosMedios;
    vector<double> resultado;
    Dataset train, test;

    // Lee el algoritmo pasado por parametro (si se han pasado parametros)
    if (argc != 1)
        algoritmo = argv[1];

    bool isAlgoritmoAPC = isInContainer(algoritmos, algoritmo);
    bool isAlgoritmoGenetico = isInContainer(algoritmosGeneticos, algoritmo);

    if (!isAlgoritmoAPC && !isAlgoritmoGenetico) {
        showErrorUnknownAlgorithm(algoritmo);
        return EXIT_FAILURE;
    }

    if (isAlgoritmoAPC) {
        if (argc <= 2)
            cout << "Semilla no especificada: aleatoria" << std::endl;
        else {
            seed = std::strtol(argv[2], nullptr, 10);
            Random::seed(seed);
            cout << "Usando semilla: " << seed << std::endl;
        }
    }

    if (isAlgoritmoGenetico) {
        if (argc <= 2) {
            std::cout << "Sin parámetros. Usando semilla aleatoria y operador BLX" << std::endl;
        } else {
            operador = argv[2];
            if (!isInContainer(operadores, operador)) {
                showErrorUnknownOperator(operador);
                return EXIT_FAILURE;
            }
            std::cout << "Usando operador: " << operador << std::endl;

            if (argc > 3) {
                seed = std::strtol(argv[3], nullptr, 10);
                Random::seed(seed);
                std::cout << "Usando semilla: " << seed << std::endl;
            } else {
                std::cout << "Semilla no especificada: aleatoria" << std::endl;
            }
        }
    }

    // Lee todos los dataset con sus respectivos ficheros
    while (!nombreDatasets.empty())
    {
        string fichero = nombreDatasets.front();      // Obtiene el primer elemento
        nombreDatasets.erase(nombreDatasets.begin()); // Lo saca del vector

        // Inicializar
        resultado = {}, pesosMedios = {}, resultadosMedios = {};

        // Imprimir cabecera tabla de resultados
        std::cout << "--------------------------------------Clasificador (" << algoritmo;
        if(isAlgoritmoGenetico)
            cout << "-" << operador;
        cout << "):" << fichero << "-------------------------------------" << endl;
        cout << "Particion\t" << "Tasa_clas_train[%]\t" << "Tasa_clas_test[%]\t" << "Tasa_red[%]\t" << "Fitness\t\t" << "Tiempo[s]" << endl;

        for (int i = 0; i < ficheros; i++)
        {
            // Lee los archivos del dataset seleccionado
            if (leerFicheros(fichero, train, test, i))
            {
                std::cout << "Ha surgido un error leyendo los datos\n";
                return EXIT_FAILURE;
            }

            // Inicializar variables
            if (i == 0) { // en la primera iteracion
                pesosMedios.resize(train.numCaracteristicas(), 0);
                resultadosMedios.resize(6);

            }
            vector<double> pesos(train.numCaracteristicas(), 1); // en todas las iteraciones

            // Normalizamos los datos
            normalizar(train, test);

            // Calculamos los pesos segun el algoritmo pasado por parametro
            auto momentoInicio = chrono::high_resolution_clock::now(); // Contamos el tiempo de los algoritmos
            if (algoritmo == "Greedy")
                pesos = greedy_relief(train);
            else if (algoritmo == "BL")
                pesos = busquedaLocal(train); // bl.busquedaLocal(train, test);
            else if(algoritmo == "AGG"){
                pesos = AGG(train, 15000, 0.1, operador); // Dataset, tamPoblacion, porcentajeCruce (genetico <<< memetico)
            }
            else if(algoritmo == "AGE"){
                pesos = AGE(train, 15000, operador); // Dataset, tamPoblacion, porcentajeCruce (genetico <<< memetico)
            }
            else if(algoritmo == "AM1")
                pesos = AM1(train, 15000, operador); // Dataset, tamPoblacion, porcentajeCruce (genetico <<< memetico)

            // Ejecutamos el clasificador 1NN
            clasificar(train, test, pesos, acierto_train, acierto_test, true);

            // Imprimimos los resultados de la ejecución
            resultado = calcularRendimiento(acierto_train, acierto_test, train, test, pesos, momentoInicio);
            imprimeRendimiento(i, resultado, resultadosMedios);

            // Guardamos los pesos medios para el final
            for (int j = 0; j < pesosMedios.size(); j++)
                pesosMedios[j] += pesos[j];

        }
        /*Resultados del clasificador*/

        imprimeResultadosMedios(resultadosMedios, pesosMedios, ficheros);
    }

    return 0;
}

void imprimeRendimiento(int i, const vector<double> &resultados, vector<double> &mediaResultados){
    int m = (int) resultados.size();

    cout << i+1 << "\t\t";
    // Imprime los resultados
    for(int j = 0; j < m-1; j++){
        // Imprime el valor actual con dos decimales
        cout << fixed << setprecision(2) << resultados[j] << "\t\t";
        if(j < 2)
            cout << "\t";
        mediaResultados[j] += resultados[j];
    }

    // Imprime el tiempo
    cout << fixed << defaultfloat<< resultados[m-1] << "\t\t";
    mediaResultados[m-1] += resultados[m-1];
    cout << endl;
}

void imprimeResultadosMedios(const vector<double> &resultadosMedios, vector<double> &pesosT, int n){
    int m = (int) resultadosMedios.size();

    cout << "MEDIA" << "\t\t";
    // Imprime los resultados medios
    for(int j = 0; j < m-2; j++){
        // Imprime el valor actual con dos decimales
        cout << fixed << setprecision(2) << resultadosMedios[j]/(double)n << "\t\t";
        if(j < 2)
            cout << "\t";
    }
    // Imprime el tiempo medio
    cout << fixed << defaultfloat<< resultadosMedios[m-2]/(double)n << "\t\t";

    std::cout << "\nPesos medios:\n";
    for(double & i : pesosT){
        i /= 5;
        std::cout << i << " ";
    }
    std::cout << endl << endl;
}
