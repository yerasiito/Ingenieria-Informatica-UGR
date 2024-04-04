#include "modelos/jugador/jugador3d.hpp"


Jugador3D::Jugador3D(const std::string & filename) : Objeto3D() {

  glTranslatef(posicion.x, posicion.y, posicion.z);

  setHijo(new Quesito3D());
  hijos[0] -> setColor(_vertex3<float>(111.0/256.0, 162.0/256.0, 179.0/256.0));
  hijos[0] -> setTranformacion(_vertex4<float>(Rotacion_, 1.0, 30.0, 0.0));

 // setHijo(new Retrato3D(filename));
 // hijos[1] -> setTranformacion(_vertex4<float>(Translacion_, -0.5, 1.0, 0.0));
}

Jugador3D::~Jugador3D() {
    delete hijos[0];
    delete hijos[1];  
}
