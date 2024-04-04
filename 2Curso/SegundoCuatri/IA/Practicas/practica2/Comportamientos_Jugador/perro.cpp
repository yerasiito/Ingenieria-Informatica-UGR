#include "../Comportamientos_Jugador/perro.hpp"
#include "motorlib/util.h"


#include <iostream>
#include <stdlib.h>

bool EstoyEnCasillaObjetivo(int fil, int col, const Sensores &sensores){
  bool esta_en_casilla_objetivo = false;
  for (int i = 0; i < sensores.destino.size() and !esta_en_casilla_objetivo; i = i + 2) {
    if (fil == sensores.destino[i] and col == sensores.destino[i+1] )
      esta_en_casilla_objetivo = true;
  }
  return esta_en_casilla_objetivo;
}

bool EsDelanteObjetivo(const Sensores &sensores){
  int fil = sensores.posF;
  int col = sensores.posC;
  switch (sensores.sentido)
  {
  case norte:
    fil--;
    break;
  case noreste:
    fil--;
    col++;
    break;
  case este:
    col++;
    break;
  case sureste:
    fil++;
    col++;
    break;
  case sur:
    fil++;
    break;
  case suroeste:
    fil++;
    col--;
    break;
  case oeste:
    col--;
    break;
  case noroeste:
    fil--;
    col--;
    break;
  }
  return EstoyEnCasillaObjetivo(fil,col,sensores);
}

bool EsDelanteCasilla(const char casilla, const Sensores &sensores, const vector<vector<unsigned char>> &mapa){
  int fil = sensores.posF;
  int col = sensores.posC;
  switch (sensores.sentido)
  {
  case norte:
    fil--;
    break;
  case noreste:
    fil--;
    col++;
    break;
  case este:
    col++;
    break;
  case sureste:
    fil++;
    col++;
    break;
  case sur:
    fil++;
    break;
  case suroeste:
    fil++;
    col--;
    break;
  case oeste:
    col--;
    break;
  case noroeste:
    fil--;
    col--;
    break;
  }
  return mapa[fil][col] == casilla;
}




Action ComportamientoPerro::think(Sensores sensores){

  Action accion;

  // Un lobo no puede estar en una casilla objetivo. Si está se tiene que salir.
  bool esta_en_casilla_objetivo = EstoyEnCasillaObjetivo(sensores.posF, sensores.posC, sensores);

  if (girando){
    accion = actSEMITURN_R;
    girando = false;
  }
  if (last_action == actWHEREIS){
          accion = actTURN_R;
          girando = true;
  }
  else if ( (esta_en_casilla_objetivo or sensores.terreno[0] == 'X') and 
    (sensores.terreno[2] != 'P' and sensores.terreno[2] != 'M') and
    (sensores.superficie[2] == '_') )  {
      accion = actFORWARD;
  }
  else if (esta_en_casilla_objetivo) {
      accion = actSEMITURN_R;
  }
  else {
    bool delanteEsCasillaObjetivo = EsDelanteObjetivo(sensores);

    if (sensores.superficie[2] == 'j' and sensores.terreno[2] != 'X'){
      accion = actWHEREIS;
    }
    else if (sensores.superficie[2] == 'j' and sensores.terreno[2] == 'X'){
      accion = actTURN_R;
    }
    else if (sensores.superficie[2] == 'l'){
      accion = actSEMITURN_L;
    }
    else if (!delanteEsCasillaObjetivo and sensores.terreno[2] != 'P' and sensores.terreno[2] != 'M' and sensores.superficie[2] != '_'){
            if (sensores.superficie[6] == 'j' or sensores.superficie[12] == 'j'){
              accion = actFORWARD;
            }
            else if (sensores.superficie[10] == 'j' or sensores.superficie[11] == 'j' or sensores.superficie[13] == 'j' or sensores.superficie[14] == 'j'){
              accion = actFORWARD;
            }
    }
    else if (sensores.superficie[1] == 'j' or sensores.superficie[4] == 'j' or sensores.superficie[9] == 'j'){
      accion = actSEMITURN_L;
    }
    else if (sensores.superficie[3] == 'j' or sensores.superficie[8] == 'j' or sensores.superficie[15] == 'j'){
      accion = actSEMITURN_R;
    }
    else {
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
    }
  }

  last_action = accion;
  return accion;
}

int ComportamientoPerro::interact(Action accion, int valor){
  return 0;
}
