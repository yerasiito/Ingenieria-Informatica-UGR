#include "modelos/arbol/arbol.hpp"
#include <GL/glut.h>

Arbol3D::Arbol3D() : Objeto3D(){
  glTranslatef(posicion.x, posicion.y, posicion.z);

  setTranformacion(_vertex4<float>(Translacion_, 0.0, 1.3, 0.0));
  //Ponemos el tronco
  setHijo(new RevolucionObj3D("ply/cilindro.ply", 50));
  hijos[0] -> setTranformacion(_vertex4<float>(Escalado_, 0.4, 0.3, 0.4));
  hijos[0] -> setTranformacion(_vertex4<float>(Translacion_, 0.0, -4.5, 0.0));
  hijos[0] -> setColor(_vertex3<float>(51.0/256.0, 35.0/256.0, 6.0/256.0));


  setHijo(new ConoObj3D());
  hijos[1] -> setTranformacion(_vertex4<float>(Escalado_, 0.8, 1.5, 0.8));
  hijos[1] -> setTranformacion(_vertex4<float>(Translacion_, 0.0, -0.7, 0.0));
  hijos[1] -> setTranformacion(_vertex4<float>(Rotacion_, 0.0, 270.0, 0.0));
  hijos[1] -> setColor(_vertex3<float>(6.0/256.0, 35.0/256.0, 17.0/256.0));


  setHijo(new ConoObj3DWire());
  hijos[2] -> setTranformacion(_vertex4<float>(Escalado_, 0.8, 1.5, 0.8));
  hijos[2] -> setTranformacion(_vertex4<float>(Translacion_, 0.0, -0.7, 0.0));
  hijos[2] -> setTranformacion(_vertex4<float>(Rotacion_, 0.0, 270.0, 0.0));
  hijos[2] -> setColor(_vertex3<float>(0.0/256.0, 0.0/256.0, 0.0/256.0));

}

Arbol3D::~Arbol3D(){
  delete hijos[0];
  delete hijos[1];
  delete hijos[2];
}
