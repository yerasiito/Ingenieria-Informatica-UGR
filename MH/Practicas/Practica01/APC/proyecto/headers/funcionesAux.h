#ifndef FUNCIONES_AUX_H
#define FUNCIONES_AUX_H

#include "dataset.h"
#include <vector>

double distancia(const Ejemplo& a, const Ejemplo& b);

double distanciaPonderada(const Ejemplo& a, const Ejemplo& b, std::vector<double> w);

#endif