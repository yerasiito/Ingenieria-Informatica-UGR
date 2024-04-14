#ifndef PRACTICA3_ALGORITMOSTRAYECTORIA_H
#define PRACTICA3_ALGORITMOSTRAYECTORIA_H

#include <vector>
#include "dataset.h"

double BMB(const Dataset &train, std::vector<double> &Sact, int maxiterBMB, int maxiterBL);

double ILS(const Dataset &train, std::vector<double> &Sact, int maxiterILS, int maxiterBL);

double VNS(const Dataset &train, std::vector<double> &Sact, int maxiterBMB, int maxiterBL);

double ILS_ES(const Dataset &train, std::vector<double> &Sact, int maxiterBMB, int maxiterBL);
#endif //PRACTICA3_ALGORITMOSTRAYECTORIA_H
