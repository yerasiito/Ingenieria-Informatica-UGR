#include "../Comportamientos_Jugador/perro.hpp"


#include <iostream>
#include <stdlib.h>

int aleatorio4(int tope){
  double a = random(), c = RAND_MAX;
  a = a / (c+1);
  int b = a*(tope+1);
  return b;
}


Action ComportamientoPerro::think(Sensores sensores){

  switch (aleatorio4(3)) {
    case 0:
      return actIDLE;
    break;

    case 1:
      return actFORWARD;
    break;

    case 2:
      return actTURN_L;
    break;

    case 3:
      return actTURN_R;
    break;
  }


}

int ComportamientoPerro::interact(Action accion, int valor){
  return 0;
}
