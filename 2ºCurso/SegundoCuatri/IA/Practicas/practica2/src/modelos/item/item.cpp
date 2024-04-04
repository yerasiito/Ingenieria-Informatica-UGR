#include "modelos/item/item.hpp"


Item3D::Item3D() : Objeto3D(){
  glTranslatef(posicion.x, posicion.y, posicion.z);

  setTranformacion(_vertex4<float>(Translacion_, 0.0, 1.3, 0.0));
  //Ponemos el tronco
  setHijo(new IcosaedroObj3D());
  //hijos[0] -> setTranformacion(_vertex4<float>(Escalado_, 0.4, 0.3, 0.4));
  hijos[0] -> setTranformacion(_vertex4<float>(Translacion_, 0.0, 1.0, 0.0));
  hijos[0] -> setColor(_vertex3<float>(255.0/256.0, 30.0/256.0, 206.0/256.0));


  setHijo(new IcosaedroObj3D());
  hijos[1] -> setTranformacion(_vertex4<float>(Translacion_, 0.0, 1.0, 0.0));
  hijos[1] -> setTranformacion(_vertex4<float>(Rotacion_, 1.0, 90.0, 0.0));
  hijos[1] -> setColor(_vertex3<float>(0.0/256.0, 0.0/256.0, 0.0/256.0));



}

Item3D::~Item3D(){
  delete hijos[0];
  delete hijos[1];
}
