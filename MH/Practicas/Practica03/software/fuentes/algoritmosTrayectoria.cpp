#include "algoritmosTrayectoria.h"
#include "busquedaLocal.h"

double BMB(const Dataset &train, std::vector<double> &Sact, int &iter, int maxiter){
    // TODO implementar
    return busquedaLocal(train, Sact, iter, maxiter);
}