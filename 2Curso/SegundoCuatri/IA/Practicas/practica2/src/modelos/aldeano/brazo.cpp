#include "modelos/aldeano/brazo.hpp"

BrazoAldeano3D::BrazoAldeano3D() : Objeto3D(){
  setHijo(new CuboObj3D());
  hijos[0] -> setTranformacion(_vertex4<float>(Translacion_, 0.0, 0.75, 0.0));
  hijos[0] -> setTranformacion(_vertex4<float>(Escalado_, 0.4, 0.4, 0.5));
  hijos[0] -> setColor(_vertex3<float>(32.0/255.0, 96.0/255.0, 32.0/255.0));
  hijos[0] -> setAmb(_vertex4<float>(32.0/255.0, 96.0/255.0, 32.0/255.0, 0.5));
  hijos[0] -> setDiff(_vertex4<float>(32.0/255.0, 96.0/255.0, 32.0/255.0, 0.5));
  hijos[0] -> setSpec(_vertex4<float>(32.0/255.0, 96.0/255.0, 32.0/255.0, 0.5));

  setHijo(new CuboObj3D());
  hijos[1] -> setTranformacion(_vertex4<float>(Translacion_, 0.0, 0.0, 0.0));
  hijos[1] -> setTranformacion(_vertex4<float>(Escalado_, 0.35, 1.1, 0.35));
  hijos[1] -> setColor(_vertex3<float>(255.0/255.0, 153.0/255.0, 102.0/255.0));
  hijos[1] -> setAmb(_vertex4<float>(255.0/255.0, 153.0/255.0, 102.0/255.0, 1.0));
  hijos[1] -> setDiff(_vertex4<float>(255.0/255.0, 153.0/255.0, 102.0/255.0, 1.0));
  hijos[1] -> setSpec(_vertex4<float>(255.0/255.0, 153.0/255.0, 102.0/255.0, 1.0));

}

BrazoAldeano3D::~BrazoAldeano3D(){
  delete hijos[0];
  delete hijos[1];
}
