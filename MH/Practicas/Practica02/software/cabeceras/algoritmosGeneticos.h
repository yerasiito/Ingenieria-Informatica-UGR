#ifndef ALG_H
#define ALG_H

#include <vector>
#include "dataset.h"


/** POR IMPLEMENTAR */
std::vector<double> AGG(Dataset train, int maxIters, double pcross, int cruce);

std::vector<double> AGE(Dataset train, int maxIters, double pcross, int cruce);
#endif