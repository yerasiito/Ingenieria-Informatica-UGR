#ifndef FUNCIONESAUX_HPP
#define FUNCIONESAUX_HPP

#include <iostream>
#include <string>
#include <cmath>

#include "dataset.h"

const std::string path = "Instancias_APC/";

// Función para leer los ficheros de datos
int leerFicheros(std::string fichero, Dataset &train, Dataset &test, int k)
{
    // Se comprueba que el fichero sea válido
    if (fichero != "diabetes" && fichero != "ozone-320" && fichero != "spectf-heart")
    {
        std::cout << "Los parametros admitidos son: diabetes, ozone-320 o spectf-heart\n";
        return EXIT_FAILURE;
    }

    // Se limpian los datasets
    train = {}, test = {};

    // Se lee cada uno de los ficheros de datos y se integran en los datasets de train o test
    for (int i = 1; i <= 5; i++)
    {
        std::string file = path + fichero + "_" + std::to_string(i) + ".arff";
        std::ifstream f(file);

        // Si se trata del dataset de test, se añade al dataset test, en caso contrario, se añade al dataset train
        if (i == k + 1)
        {
            if (test.read(f))
            {
                std::cerr << "No se pudo abrir - '"
                          << file << "'" << std::endl;
                return EXIT_FAILURE;
            }
        }
        else if (train.read(f))
        {
            std::cerr << "No se pudo abrir - '"
                      << file << "'" << std::endl;
            return EXIT_FAILURE;
        }
    }

    // Si todo ha ido bien, se devuelve sucess
    return EXIT_SUCCESS;
}

// Función para calcular la distancia euclídea
double distancia(const Ejemplo &a, const Ejemplo &b, std::vector<double> w)
{
    double dist = 0;

    // Se calcula la distancia euclídea teniendo en cuenta los pesos w de cada característica
    for (int i = 0; i < a.caracteristicas.size(); i++)
    {
        // Si el peso es menor que 0.1, se ignora
        if (w[i] < 0.1)
        {
            continue;
        }

        // Se calcula la diferencia al cuadrado entre las dos características y se multiplica por el peso
        dist += w[i] * pow(a.caracteristicas[i] - b.caracteristicas[i], 2);
    }

    // Se devuelve la distancia euclídea final
    return sqrt(dist);
}

// Función para normalizar los datos
void normalizar(Dataset &train, Dataset &test)
{
    double car = 0;
    std::vector<double> min_atrib = {}, max_atrib = {};

    // Se busca el valor mínimo y máximo para cada atributo en los datasets de train y test
    for (int j = 0; j < train.numCaracteristicas(); j++)
    {
        double min_car = INFINITY, max_car = -INFINITY;

        // Se busca el valor mínimo y máximo en el dataset de train
        for (int i = 0; i < train.numEjemplos(); i++)
        {
            car = train.getCaracteristica(i, j);
            if (car > max_car)
                max_car = car;

            if (car < min_car)
                min_car = car;
        }

        // Se busca el valor mínimo y máximo en el dataset de test
        for (int i = 0; i < test.numEjemplos(); i++)
        {
            car = test.getCaracteristica(i, j);
            if (car > max_car)
                max_car = car;

            if (car < min_car)
                min_car = car;
        }

        // Se guardan los valores mínimo y máximo para el atributo actual
        min_atrib.push_back(min_car);
        max_atrib.push_back(max_car);
    }

    // Se normalizan los datos de train
    for (int i = 0; i < train.numEjemplos(); i++)
    {
        for (int j = 0; j < train.numCaracteristicas(); j++)
        {
            double valor_original = train.getCaracteristica(i, j);
            double valor_normalizado = (valor_original - min_atrib[j]) / (max_atrib[j] - min_atrib[j]);
            train.setCaracteristica(i, j, valor_normalizado);
        }
    }

    // Se normalizan los datos de test
    for (int i = 0; i < test.numEjemplos(); i++)
    {
        for (int j = 0; j < test.numCaracteristicas(); j++)
        {
            double valor_original = test.getCaracteristica(i, j);
            double valor_normalizado = (valor_original - min_atrib[j]) / (max_atrib[j] - min_atrib[j]);
            test.setCaracteristica(i, j, valor_normalizado);
        }
    }
}

#endif