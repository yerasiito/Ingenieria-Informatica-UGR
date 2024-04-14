#include "random.hpp"
#include "busquedaLocal.hpp"

using namespace std;
using Random = effolkronium::random_static;

vector<string> nombreDatasets = {"diabetes", "ozone-320", "spectf-heart"}; // Datasets a utilizar

int main(int argc, char **argv)
{
    long int seed;

    if (argc <= 2)
        cout << "Sin semilla fija" << endl;
    else
    {
        seed = atoi(argv[2]);
        Random::seed(seed);
        cout << "Usando semilla: " << seed << endl;
    }

    int acierto_train, acierto_test;
    string algoritmo = "1-NN";
    vector<double> pesosMedios;
    vector<vector<double>> rendimiento, pesosParticiones;
    Dataset train, test;

    // Lee el algoritmo pasado por parametro (si se han pasado parametros)
    if (argc != 1)
        algoritmo = argv[1];
    // Devuelve error en caso de pasar un parametro desconocido
    if (algoritmo != "1-NN" && algoritmo != "greedy" && algoritmo != "bl")
    {
        cerr << "Algoritmo " << argv[1] << " desconocido. Elige: 'sin parametro', greedy o bl.\n";
        return EXIT_FAILURE;
    }

    // Lee todos los dataset con sus respectivos ficheros
    while (!nombreDatasets.empty())
    {
        string fichero = nombreDatasets.front();      // Obtiene el primer elemento
        nombreDatasets.erase(nombreDatasets.begin()); // Lo saca del vector

        // Inicializar
        rendimiento = {}, pesosParticiones = {}, pesosMedios = {};

        for (int i = 0; i < 5; i++)
        {
            // Lee los archivos del dataset seleccionado
            if (leerFicheros(fichero, train, test, i))
            {
                std::cout << "Ha surgido un error leyendo los datos\n";
                return EXIT_FAILURE;
            }

            // Inicializar variables
            if (i == 0) // en la primera iteracion
                pesosMedios.resize(train.numCaracteristicas(), 0);
            vector<double> pesos(train.numCaracteristicas(), 1); // en todas las iteraciones

            // Normalizamos los datos
            normalizar(train, test);

            // Calculamos los pesos segun el algoritmo pasado por parametro
            auto momentoInicio = chrono::high_resolution_clock::now(); // Contamos el tiempo de los algoritmos
            if (algoritmo == "greedy")
                pesos = greedy_relief(train);
            else if (algoritmo == "bl")
                pesos = busquedaLocal(train); // bl.busquedaLocal(train, test);
            // Ejecutamos el clasificador 1NN
            clasificar(train, test, pesos, acierto_train, acierto_test, true);

            // Guardamos los resultados en una matriz/tabla de rendimiento
            rendimiento.push_back(calcularRendimiento(acierto_train, acierto_test, train, test, pesos, momentoInicio));

            // Guardamos los pesos medios para el final
            for (int j = 0; j < pesosMedios.size(); j++)
                pesosMedios[j] += pesos[j];

            pesosParticiones.push_back(pesos); // Para imprimirlos al final
        }
        /*Resultados del clasificador*/
        std::cout << "--------------------------------------Clasificador (" << algoritmo << "):" << fichero << "-------------------------------------";
        imprimeRendimiento(rendimiento); // Imprime la matriz/tabla de rendimiento

        // //Imprime todos los pesos por particion
        // imprimePesos(pesosParticiones);

        imprimePesoMedio(pesosMedios);
    }

    return 0;
}
