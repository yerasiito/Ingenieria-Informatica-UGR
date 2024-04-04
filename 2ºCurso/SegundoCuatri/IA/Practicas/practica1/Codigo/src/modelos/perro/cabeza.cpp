#include "modelos/perro/cabeza.hpp"

CabezaPerro::CabezaPerro() : CuboObj3D(){

  //Ponemos una oreja...
  setHijo(new CuboObj3D());
  hijos[0] -> setColor(_vertex3<float>(88.0/256.0, 88.0/256.0, 88.0/256.0));
  hijos[0] -> setTranformacion(_vertex4<float>(Translacion_, -0.35, 0.7, -0.2));
  hijos[0] -> setTranformacion(_vertex4<float>(Escalado_, 0.3, 0.4, 0.1));

  //Ponemos la otra
  setHijo(new CuboObj3D());
  hijos[1] -> setColor(_vertex3<float>(88.0/256.0, 88.0/256.0, 88.0/256.0));
  hijos[1] -> setTranformacion(_vertex4<float>(Translacion_, 0.35, 0.7, -0.2));
  hijos[1] -> setTranformacion(_vertex4<float>(Escalado_, 0.3, 0.4, 0.1));

  //Ponemos el hocico
  setHijo(new CuboObj3D());
  hijos[2] -> setColor(_vertex3<float>(88.0/256.0, 88.0/256.0, 88.0/256.0));
  hijos[2] -> setTranformacion(_vertex4<float>(Translacion_, 0.0, -0.25, 0.6));
  hijos[2] -> setTranformacion(_vertex4<float>(Escalado_, 0.5, 0.5, 0.6));

  //Ponemos la nariz del hocico
  setHijo(new CuboObj3D());
  hijos[3] -> setColor(_vertex3<float>(0/256.0, 0/256.0, 0/256.0));
  hijos[3] -> setTranformacion(_vertex4<float>(Translacion_, 0.0, -0.2, 0.9));
  hijos[3] -> setTranformacion(_vertex4<float>(Escalado_, 0.3, 0.3, 0.3));

  //Ponemos un ojo
  setHijo(new CuboObj3D());
  hijos[4] -> setColor(_vertex3<float>(66.0/256.0, 134.0/256.0, 244.0/256.0));
  hijos[4] -> setTranformacion(_vertex4<float>(Translacion_, -0.30, 0.3, 0.45));
  hijos[4] -> setTranformacion(_vertex4<float>(Escalado_, 0.15, 0.15, 0.15));

  //Ponemos el otro
  setHijo(new CuboObj3D());
  hijos[5] -> setColor(_vertex3<float>(66.0/256.0, 134.0/256.0, 244.0/256.0));
  hijos[5] -> setTranformacion(_vertex4<float>(Translacion_, 0.30, 0.3, 0.45));
  hijos[5] -> setTranformacion(_vertex4<float>(Escalado_, 0.15, 0.15, 0.15));
}

CabezaPerro::~CabezaPerro(){
  delete hijos[0];
  delete hijos[1];
  delete hijos[2];
  delete hijos[3];
  delete hijos[4];
  delete hijos[5];
}
