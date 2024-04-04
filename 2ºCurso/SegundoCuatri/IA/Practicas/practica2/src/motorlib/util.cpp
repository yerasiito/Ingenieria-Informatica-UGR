#include "motorlib/util.h"

int aleatorio(int tope) {
  double a = rand(), c = RAND_MAX;
  a = a / (c+1);
  int b = a*(tope+1);

  return b;
}

