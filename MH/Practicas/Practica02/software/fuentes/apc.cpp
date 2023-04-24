#include <algorithm>
#include <iomanip>
#include <cmath>

#include "apc.h"


using namespace std;

// Función para actualizar los pesos de las características
void actualizar_pesos(const Ejemplo& inst, const Dataset& dataset, vector<double>& weights) {
    double amigo_dist = INFINITY;
    double enemigo_dist = INFINITY;
    int amigo_idx, enemigo_idx;

    // Calcular las distancias de la instancia actual a todos los ejemplos del dataset
    // Se utiliza la función distancia() con pesos igual a 1
    for (int i = 0; i < dataset.numEjemplos(); i++) {
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
        Ejemplo inst = dataset.getEjemplo(i);
        actualizar_pesos(inst, dataset.leave_one_out(i), weights); // Actualizamos los pesos del ejemplo actual
    }
    // Normalizamos los pesos
    double w_max = *max_element(weights.begin(), weights.end()); // Obtenemos el peso máximo
    for(int i = 0; i < weights.size();i++){
        if(weights[i] < 0){
            weights[i] = 0;
        }
        else{
            weights[i] /= w_max;
        }
    }
    return weights; // Devolvemos los pesos normalizados
}


// Funcion para clasificar un ejemplo dado un dataset
string clasificador1NN(Ejemplo test_ejemplo, Dataset train, vector<double> w) {
    int min_index = 0;  // Indice de la instancia con la distancia minima
    double min_distance = INFINITY;

    // Itera sobre todas las instancias del dataset de entrenamiento
    for (int i = 0; i < train.numEjemplos(); i++) {
        double distance = distancia(test_ejemplo, train.getEjemplo(i), w); // Calcula la distancia entre el ejemplo de prueba y el ejemplo de entrenamiento i
        if (distance < min_distance) { // Actualiza el indice y la distancia
            min_index = i; 
            min_distance = distance; 
        }
    }
    return train.getEjemplo(min_index).etiqueta; // Devuelve la etiqueta de la instancia con la distancia minima
}


// Función principal para clasificar los datasets de train y test
void clasificar(Dataset train, Dataset test, vector<double> pesos, int &acierto_train, int &acierto_test, bool tasa_train){
    acierto_train = 0, acierto_test = 0;
    
    // La tasa de train es opcional
    if(tasa_train)
        clasificarTrain(train, pesos, acierto_train);
    
    // Clasificar el dataset de test
    clasificarTest(train, test, pesos, acierto_test);
}

// Función auxiliar para clasificar el dataset de entrenamiento
void clasificarTrain(Dataset train, vector<double> pesos, int &acierto_train){
    acierto_train = 0;
    
    // Clasificar cada ejemplo del dataset de entrenamiento. Aplica leave one out
    for(int i = 0; i < train.numEjemplos(); i++){
        string label_train = clasificador1NN(train.getEjemplo(i), train.leave_one_out(i), pesos);
        if(label_train == train.getEjemplo(i).etiqueta)
            acierto_train++;
    }
}

// Función auxiliar para clasificar el dataset de test
void clasificarTest(Dataset train, Dataset test, vector<double> pesos,int &acierto_test){
    acierto_test = 0;
    
    // Clasificar cada ejemplo del dataset de test
    for(int i = 0; i < test.numEjemplos(); i++){
        string label_test = clasificador1NN(test.getEjemplo(i), train, pesos);
        if(label_test == test.getEjemplo(i).etiqueta)
            acierto_test++;
    }
}

// Funcion para calcular la tasa de reduccion de los pesos
double calcularTasaRed(vector<double> pesos){
    double tasa_red = 0;
    for(auto it : pesos)
        if(it < 0.1) // Si el peso es menor que 0.1, entonces cuenta como reducido
            tasa_red++;
    return tasa_red = 100*(tasa_red/pesos.size()); // Devolvemos la tasa de reduccion en porcentaje
}


double calcularFitness(int acierto, int numEjemplos, vector<double> pesos){
    // Calcula la tasa de clasificación y la tasa de reducción
    double tasa_clas = 100.0*(double(acierto)/double(numEjemplos));
    double tasa_red = calcularTasaRed(pesos);

    // Combina la tasa de clasificación y la tasa de reducción en una única medida de fitness
    return 0.8*tasa_clas + 0.2*tasa_red;
}

// Función para calcular el rendimiento de un algoritmo a partir de sus aciertos y pesos
vector<double> calcularRendimiento(int acierto_train, int acierto_test, Dataset train, Dataset test, vector<double> w,
    chrono::high_resolution_clock::time_point momentoInicio){
    
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
    double t = double(tiempo.count()/1000.0);

    // Creamos un vector con los valores de rendimiento y lo devolvemos
    vector<double> rendimiento = {tasa_clas_train, tasa_clas_test, tasa_red, fitness, t};
    return rendimiento;
}


void imprimeRendimiento(vector<vector<double>> resultados){
    int n = resultados.size(), m = resultados[0].size();
    // Imprime cabecera de la tabla con los nombres de las columnas
    cout << "\nParticion\t" << "Tasa_clas_train[%]\t" << "Tasa_clas_test[%]\t" << "Tasa_red[%]\t" << "Fitness\t\t" << "Tiempo[s]";
    vector<double> media(m,0);
    // Recorre todas las particiones
    for(int i = 0; i < n; i++){
        cout << endl;
        cout << i+1 << "\t\t";
        for(int j = 0; j < m-1; j++){
            // Suma el valor actual a la media correspondiente
            media[j] += resultados[i][j];
            // Imprime el valor actual con dos decimales
            cout << fixed << setprecision(2) << resultados[i][j] << "\t\t";
            if(j < 2)
                cout << "\t";
        }
        // Suma el tiempo de la partición actual a la media correspondiente y lo imprime
        media[m-1] += resultados[i][m-1];
        cout << defaultfloat << resultados[i][m-1] << "\t\t";
    }
    // Imprime la fila de las medias
    cout << "\nMEDIA\t\t";
    for(int i = 0; i < m-1; i++){
        // Imprime la media con dos decimales
        cout << fixed << setprecision(2) << media[i]/5.0 << "\t\t";
        if(i < 2)
            cout << "\t";
    }
    // Imprime la media del tiempo
    cout << defaultfloat << media[n-1]/5.0 << endl;
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
    std::cout << endl << endl;
}