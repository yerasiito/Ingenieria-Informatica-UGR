#include <cmath>
#include "greedy.h"
#include "funcionesAux.h"

using namespace std;

//Métodos de cálculo de distancia
double calcularTasaRed(std::vector<double> pesos){
    double tasa_red = 0;
    for(auto it : pesos)
        if(it < 0.1)
            tasa_red++;
    return tasa_red = 100*(tasa_red/pesos.size());
}

const string path = ""; //"./Instancias_APC/";
int car_descartada = 0;

int unoNN(Ejemplo test_ejemplo, Dataset training_set) {
    int min_index = 0;
    double min_distance = INFINITY;

    for (int i = 0; i < training_set.numEjemplos(); i++) {
        double distance = distancia(test_ejemplo, training_set.getEjemplo(i));
        if (distance < min_distance && distance != 0) {
            min_index = i;
            min_distance = distance;
        }
    }
    return training_set.getEjemplo(min_index).etiqueta;
}

int unoNNponderado(Ejemplo test_ejemplo, Dataset training_set, vector<double> w) {
    int min_index = 0;
    double min_distance = INFINITY;

    for (int i = 0; i < training_set.numEjemplos(); i++) {
        double distance = distanciaPonderada(test_ejemplo, training_set.getEjemplo(i), w);
        if (distance < min_distance && distance != 0) {
            min_index = i;
            min_distance = distance;
        }
    }
    return training_set.getEjemplo(min_index).etiqueta;
}

int main(int argc, char** argv) {
    Dataset ds;

    //Lee el archivo pasado por parámetro
    ifstream f(path + argv[1]);
   
    //Lee el fichero y lo integra en el objeto ds. Si falla entra en el if
    if(ds.read(f)){
        cerr << "No se pudo abrir - '"
            << argv[1] << "'" << endl;
        return EXIT_FAILURE;
    }

    //Imprime la matriz
    cout << "IMPRIME MATRIZ:";
    ds.dataPrint();
    ds.dimensionPrint();

    for(int i = 0; i < ds.numEtiquetas(); i++)
        cout << i << ":" << ds.getLabelName(i) << endl;
    
    //Normalizamos el ds
    Dataset ds_normalizado = ds.normalizar();

    //Calculamos el rendimiento del clasificador sin greedy
    Dataset trainset = ds_normalizado;
    int acierto = 0, error = 0;
    for(int i = 0; i < ds_normalizado.numEjemplos(); i++){
        int label = unoNN(ds_normalizado.getEjemplo(i), ds_normalizado);
        trainset.getEjemplo(i).etiqueta = label;
        if(label == ds_normalizado.getEjemplo(i).etiqueta){
            acierto++;
        }
        else
            error++;
    }
    double tasa_clas = 100*double(acierto)/double(ds.numEjemplos());
    cout << "-----1NN normal-----" << endl;
    cout << "Tasa_clas: " << tasa_clas << "%" << endl;

    //Calculamos el rendimiento del clasificador con greedy
    /**ALGORITMO GREEDY**/
    vector<double> pesos;
    Greedy gr;
    pesos = gr.greedy_relief(ds);

    Dataset trainset2 = ds_normalizado;
    acierto = 0, error = 0;
    for(int i = 0; i < ds_normalizado.numEjemplos(); i++){
        int label = unoNNponderado(ds_normalizado.getEjemplo(i), ds_normalizado, pesos);
        trainset2.getEjemplo(i).etiqueta = label;
        if(label == ds_normalizado.getEjemplo(i).etiqueta){
            acierto++;
        }
        else
            error++;
    }
    tasa_clas = 100*double(acierto)/double(ds.numEjemplos());
    double tasa_red = calcularTasaRed(pesos);
    cout << "----1NN mejorado----" << endl;
    cout << "Tasa_clas: " << tasa_clas << "%" << endl;
    cout << "Tasa_red: " << tasa_red << "%" << endl;
    //Habemus pesos w
    cout << "Pesos: ";
    for(int i = 0; i < pesos.size(); i++)
        cout << pesos[i] << " ";
    cout << endl;

    return 0;
}
