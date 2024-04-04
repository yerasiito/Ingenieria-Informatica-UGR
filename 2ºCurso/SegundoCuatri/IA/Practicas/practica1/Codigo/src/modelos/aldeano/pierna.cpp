#include "modelos/aldeano/pierna.hpp"

PiernaAldeano3D::PiernaAldeano3D() : Objeto3D(){

  setHijo(new CuboObj3D());
  hijos[0] -> setTranformacion(_vertex4<float>(Escalado_, 0.45, 1.5, 0.5));
  hijos[0] -> setColor(_vertex3<float>(0.0/255.0, 0.0/255.0, 0.0/255.0));
  hijos[0] -> setAmb(_vertex4<float>(0.0/255.0, 0.0/255.0, 0.0/255.0, 0.5));
  hijos[0] -> setDiff(_vertex4<float>(0.0/255.0, 0.0/255.0, 0.0/255.0, 0.5));
  hijos[0] -> setSpec(_vertex4<float>(0.0/255.0, 0.0/255.0, 0.0/255.0, 0.5));


  setHijo(new CuboObj3D());
  hijos[1] -> setTranformacion(_vertex4<float>(Translacion_, 0.0, -0.85, 0.1));
  hijos[1] -> setTranformacion(_vertex4<float>(Escalado_, 0.45, 0.2, 0.7));
  hijos[1] -> setColor(_vertex3<float>(32.0/255.0, 96.0/255.0, 32.0/255.0));
  hijos[1] -> setAmb(_vertex4<float>(32.0/255.0, 96.0/255.0, 32.0/255.0, 0.5));
  hijos[1] -> setDiff(_vertex4<float>(32.0/255.0, 96.0/255.0, 32.0/255.0, 0.5));
  hijos[1] -> setSpec(_vertex4<float>(32.0/255.0, 96.0/255.0, 32.0/255.0, 0.5));


}

PiernaAldeano3D::~PiernaAldeano3D(){
  delete hijos[0];
  delete hijos[1];
}
