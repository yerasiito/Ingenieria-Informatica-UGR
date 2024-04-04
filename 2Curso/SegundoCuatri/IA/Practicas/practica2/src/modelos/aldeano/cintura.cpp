#include "modelos/aldeano/cintura.hpp"

CinturaAldeano3D::CinturaAldeano3D() : Objeto3D(){

  //Ponemos el paquete
  setHijo(new CuboObj3D());
  hijos[0] -> setTranformacion(_vertex4<float>(Escalado_, 1.0, 0.4, 0.5));
  hijos[0] -> setColor(_vertex3<float>(0.0/255.0, 0.0/255.0, 0.0/255.0));
  hijos[0] -> setAmb(_vertex4<float>(0.0/255.0, 0.0/255.0, 0.0/255.0, 0.5));
  hijos[0] -> setDiff(_vertex4<float>(0.0/255.0, 0.0/255.0, 0.0/255.0, 0.5));
  hijos[0] -> setSpec(_vertex4<float>(0.0/255.0, 0.0/255.0, 0.0/255.0, 0.5));

  //Ponemos una pierna
  setHijo(new PiernaAldeano3D());
  hijos[1] -> setTranformacion(_vertex4<float>(Translacion_, -0.275, -0.9, 0.0));

  //Ponemos la otra pierna
  setHijo(new PiernaAldeano3D());
  hijos[2] -> setTranformacion(_vertex4<float>(Translacion_, 0.275, -0.9, 0.0));

}

CinturaAldeano3D::~CinturaAldeano3D(){
  delete hijos[0];
  delete hijos[1];
  delete hijos[2];
}
