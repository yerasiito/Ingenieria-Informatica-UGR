#ifndef ALG_H
#define ALG_H

#include <vector>
#include "dataset.h"


/** POR IMPLEMENTAR */
std::vector<double> AGG(const Dataset &train, const int &maxIters, const double &pcross, const int &cruce);

std::vector<double> AGE(const Dataset &train, const int &maxIters, const int &cruce);
#endif