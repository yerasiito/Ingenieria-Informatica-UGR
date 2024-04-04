#include "modelos/perro/lomo.hpp"

LomoPerro::LomoPerro() : Objeto3D(){


  //Ponemos el cuerpo...
  setHijo(new CuboObj3D());
  hijos[0] -> setColor(_vertex3<float>(109.0/256.0, 106.0/256.0, 106.0/256.0));
  hijos[0] -> setTranformacion(_vertex4<float>(Escalado_, 0.8, 0.8, 1.3));

  //Ponemos una pata
  setHijo(new CuboObj3D());
  hijos[1] -> setColor(_vertex3<float>(109.0/256.0, 106.0/256.0, 106.0/256.0));
  hijos[1] -> setTranformacion(_vertex4<float>(Translacion_, 0.3, -0.8, -0.55));
  hijos[1] -> setTranformacion(_vertex4<float>(Escalado_, 0.2, 0.8, 0.2));
  //Ponemos la otra
  setHijo(new CuboObj3D());
  hijos[2] -> setColor(_vertex3<float>(109.0/256.0, 106.0/256.0, 106.0/256.0));
  hijos[2] -> setTranformacion(_vertex4<float>(Translacion_, -0.3, -0.8, -0.55));
  hijos[2] -> setTranformacion(_vertex4<float>(Escalado_, 0.2, 0.8, 0.2));

  //Ponemos la cola
  setHijo(new CuboObj3D());
  hijos[3] -> setColor(_vertex3<float>(118.0/256.0, 118.0/256.0, 118.0/256.0));
  hijos[3] -> setTranformacion(_vertex4<float>(Translacion_, 0.0, 0.3, -1.0));
  hijos[3] -> setTranformacion(_vertex4<float>(Escalado_, 0.2, 0.2, 0.8));
}

LomoPerro::~LomoPerro(){
  delete hijos[0];
  delete hijos[1];
  delete hijos[2];
  delete hijos[3];
}
