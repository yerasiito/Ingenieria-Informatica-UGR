#ifndef PRACTICA2_SHEEPFLOCKHEREDITYMODEL_H
#define PRACTICA2_SHEEPFLOCKHEREDITYMODEL_H

#include <vector>
#include "dataset.h"
#include "apc.h"

void cruceSPX(std::vector<double> &padre, int numOvejas, int sizeOvejas);

void cruceSPX(std::vector<double> &padre1, std::vector<double> &padre2);


std::vector<double> SFHMA(const Dataset &train, int maxIters, const std::string& operador);

std::vector<double> SFHMA_hibrido(const Dataset &train, int maxIters, const std::string& operador);

#endif //PRACTICA2_SHEEPFLOCKHEREDITYMODEL_H
