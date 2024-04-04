#include "modelos/aldeano/aldeano.hpp"


Aldeano3D::Aldeano3D(const std::string & filename) : Objeto3D(){
  glTranslatef(posicion.x, posicion.y, posicion.z);

  setHijo(new TorsoAldeano3D(filename));
  hijos[0] -> setTranformacion(_vertex4<float>(Escalado_, 0.8, 0.8, 0.8));
  hijos[0] -> setTranformacion(_vertex4<float>(Translacion_, 0.0, 2.05, 0.0));
}

Aldeano3D::~Aldeano3D(){
  delete hijos[0];
}
