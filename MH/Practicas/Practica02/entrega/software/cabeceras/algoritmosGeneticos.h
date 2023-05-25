#ifndef ALG_H
#define ALG_H

#include <vector>
#include "dataset.h"


/** POR IMPLEMENTAR */
std::vector<double> AGG(const Dataset &train, int maxIters, double pcross, const std::string& operador);

std::vector<double> AGE(const Dataset &train, int maxIters, const std::string& operador);

std::vector<double> AM_All(const Dataset &train, int maxIters, double pcross, const std::string& operador);

std::vector<double> AM_Rand(const Dataset &train, int maxIters, double pcross, const std::string& operador);

std::vector<double> AM_Best(const Dataset &train, int maxIters, double pcross, const std::string& operador);

#endif