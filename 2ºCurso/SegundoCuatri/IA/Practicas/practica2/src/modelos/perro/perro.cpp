#include "modelos/perro/perro.hpp"

Perro3D::Perro3D() : Objeto3D(){
  glTranslatef(posicion.x, posicion.y, posicion.z);

  setTranformacion(_vertex4<float>(Translacion_, 0.0, 1.3, 0.0));
  //Ponemos el cuerpo
  setHijo(new CuboObj3D());
  //hijos[0] -> setColor(_vertex3<float>(109.0/256.0, 106.0/256.0, 106.0/256.0));
  hijos[0] -> setColor(_vertex3<float>(88.0/256.0, 88.0/256.0, 88.0/256.0));

  //Ponemos la cabeza...
  setHijo(new CabezaPerro());
  hijos[1] -> setColor(_vertex3<float>(109.0/256.0, 106.0/256.0, 106.0/256.0));
  hijos[1] -> setTranformacion(_vertex4<float>(Escalado_, 0.8, 0.8, 0.8));
  hijos[1] -> setTranformacion(_vertex4<float>(Translacion_, 0.0, 0.0, 0.8));

  //Ponemos una pata
  setHijo(new CuboObj3D());
  hijos[2] -> setColor(_vertex3<float>(109.0/256.0, 106.0/256.0, 106.0/256.0));
  hijos[2] -> setTranformacion(_vertex4<float>(Translacion_, 0.4, -0.9, 0.4));
  hijos[2] -> setTranformacion(_vertex4<float>(Escalado_, 0.2, 0.8, 0.2));

  //Ponemos la otra
  setHijo(new CuboObj3D());
  hijos[3] -> setColor(_vertex3<float>(109.0/256.0, 106.0/256.0, 106.0/256.0));
  hijos[3] -> setTranformacion(_vertex4<float>(Translacion_, -0.4, -0.9, 0.4));
  hijos[3] -> setTranformacion(_vertex4<float>(Escalado_, 0.2, 0.8, 0.2));

  //Ponemos el lomo
  setHijo(new LomoPerro());
  hijos[4] -> setTranformacion(_vertex4<float>(Translacion_, -0.0, -0.1, -0.8));

}

Perro3D::~Perro3D(){
  delete hijos[0];
  delete hijos[1];
  delete hijos[2];
  delete hijos[3];
  delete hijos[4];
}
