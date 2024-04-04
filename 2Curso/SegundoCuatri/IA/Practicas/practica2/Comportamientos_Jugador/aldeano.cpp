#include "../Comportamientos_Jugador/aldeano.hpp"
#include "motorlib/util.h"

Action ComportamientoAldeano::think(Sensores sensores) {
  Action accion = actIDLE;

/*  // Aldeano basico
  switch (paso){
      case 0: accion = actFORWARD;
              break;
      case 1: accion = actTURN_R;
	      break;
  }
  paso = (paso+1)%2;*/

  // Aldeano comun
  int cual = aleatorio(20);
  switch (cual) {
	case 0: accion = actIDLE; break;
	case 1: accion = actTURN_L; break;
	case 2: accion = actTURN_R; break;
  case 3: accion = actSEMITURN_L; break;
  case 4: accion = actSEMITURN_R; break;
	default: 
		if (sensores.terreno[2] != 'P' and sensores.terreno[2] != 'M' and sensores.superficie[2] == '_') accion = actFORWARD;
    else accion = actSEMITURN_L;
		break;
  }

  return accion;
}

int ComportamientoAldeano::interact(Action accion, int valor) {
    return 0;
}
