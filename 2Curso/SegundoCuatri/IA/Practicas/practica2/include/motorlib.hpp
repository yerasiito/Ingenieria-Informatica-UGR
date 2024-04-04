#ifndef MOTORLIB
#define MOTORLIB

#include "motorlib/monitor.hpp"
#include <glui/glui.h>

extern MonitorJuego monitor;

struct EnLinea{
  list<pair<int,int>> listaObjetivos;
  int fil_inicial;
  int col_inicial;
  int ori_inicial;
  string ubicacion_mapa;
  int semilla;
  int level;
};


bool lanzar_motor_juego(int &colisiones, int acc = -1);
void lanzar_motor_juego2(MonitorJuego &monitor);
void nucleo_motor_juego(MonitorJuego & monitor, int acc);
void lanzar_motor_grafico(int argc, char ** argv);
void lanzar_motor_grafico_verOnline(int argc, char ** argv, EnLinea &argumentos);

#endif
