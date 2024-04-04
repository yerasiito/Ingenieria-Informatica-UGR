#include "comportamientos/comportamiento.hpp"

Comportamiento::Comportamiento(unsigned int size)
{
  vector<unsigned char> aux(size, '?');
  vector<unsigned char> aux2(size, 0);

  for (unsigned int i = 0; i < size; i++)
  {
    mapaResultado.push_back(aux);
    mapaEntidades.push_back(aux);
    mapaConPlan.push_back(aux2);
  }
}

Action Comportamiento::think(Sensores sensores)
{
  return actIDLE;
}

int Comportamiento::interact(Action accion, int valor)
{
  return 0;
}
