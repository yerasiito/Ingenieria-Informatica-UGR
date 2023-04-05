#ifndef DATASET_H
#define DATASET_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>


struct Ejemplo {
    std::vector<double> caracteristicas = {};
    int etiqueta = 0;

    void imprimir(){
        std::cout << std::endl;
        for(auto it : caracteristicas){
            std::cout << it << " ";
        }
        std::cout << etiqueta;
        std::cout << std::endl;
    }
};

class Dataset {
    private:
        std::vector<Ejemplo> ejemplos = {};
        std::vector<std::string> labelNames = {};
    public:
        /**
         * @brief Lee un fichero arf y lo guarda en el conjunto de datos
         * @param f El fichero a leer
         * @return 1 si falla, 0 si todo va bien
        */
        int read(std::ifstream &f);

        /**
         * @brief Etiqueta un string como numero
         * @param nombre La etiqueta string a etiquetar
         * @return la posicion/etiqueta del string si está en labelNames, 
         * sino devuelve la posicion/etiqueta nueva asignada
        */
        int etiquetar(std::string nombre);

        //Métodos get

        Ejemplo &getEjemplo(int i);

        /**
         * @brief Devuelve un ejemplo dado un indice
         * @param i la posicion
         * @return el ejemplo en la posicion dada
        */
        const Ejemplo &getEjemplo(int i) const;

        /**
         * @brief devuelve el número de ejemplos del conjunto de datos
         * @return el numero de ejemplos
        */
        const int numEjemplos();

        /**
         * @brief devuelve el número de característica de los ejemplos
         * @return el numero de características
        */
        const int numCaracteristicas();

        /**
         * @brief devuelve el número de etiquetas del conjunto de datos
         * @return el numero de etiquetas
        */
        const int numEtiquetas();

        /**
         * @brief devuelve la caracteristica j del ejemplo i
         * @param i la posición del ejemplo
         * @param j la posición de característica
         * @return la caracteristica en ds[i][j]
        */
        const double getCaracteristica(int i, int j);

        /**
         * @brief devuelve la etiqueta del ejemplo i
         * @param i el numero de ejemplo
         * @return la etiqueta int del ejemplo dado
        */
        const int &getEtiqueta(int i);

        /**
         * @brief devuelve el nombre de la etiqueta dada con un entero
         * @param i el num de etiqueta a obtener
         * @return el nombre de la etiqueta
        */
        const std::string &getLabelName(int i);

        //Métodos set
        /**
         * @brief Inserta un struct ejemplo en el conjunto de datos
         * @param e El ejemplo a insertar
        */
        void insertEjemplo(Ejemplo e);

        /**
         * @brief Normaliza el dataset en un rango [0,1]
         * @return el dataset normalizado
        */
        Dataset normalizar();

        /**
         * @brief Imprime la matriz de datos
        */
        void dataPrint();

        /**
         * @brief Imprime la dimension de la matriz
        */
        void dimensionPrint();



};

#endif  // DATASET_H