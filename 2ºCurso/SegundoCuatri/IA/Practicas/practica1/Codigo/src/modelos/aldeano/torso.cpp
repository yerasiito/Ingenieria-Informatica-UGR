#include "modelos/aldeano/torso.hpp"

TorsoAldeano3D::TorsoAldeano3D(const std::string & filename) : Objeto3D(){

  //Colocamos el torso...
  setHijo(new CuboObj3D());
  hijos[0] -> setTranformacion(_vertex4<float>(Translacion_, 0.0, 0.75, 0.0));
  hijos[0] -> setTranformacion(_vertex4<float>(Escalado_, 1.0, 1.5, 0.5));
  hijos[0] -> setColor(_vertex3<float>(32.0/255.0, 96.0/255.0, 32.0/255.0));
  hijos[0] -> setAmb(_vertex4<float>(32.0/255.0, 96.0/255.0, 32.0/255.0, 0.5));
  hijos[0] -> setDiff(_vertex4<float>(32.0/255.0, 96.0/255.0, 32.0/255.0, 0.5));
  hijos[0] -> setSpec(_vertex4<float>(32.0/255.0, 96.0/255.0, 32.0/255.0, 0.5));


  //Colocamos la cabeza...
  setHijo(new CabezaAldeano3D(filename));
  hijos[1] -> setTranformacion(_vertex4<float>(Translacion_, 0.0, 1.5, 0.0));

  //Colocamos un brazo...
  setHijo(new BrazoAldeano3D());
  hijos[2] -> setTranformacion(_vertex4<float>(Translacion_, -0.7, 0.55, 0.0));

  //Colocamos el otro...
  setHijo(new BrazoAldeano3D());
  hijos[3] -> setTranformacion(_vertex4<float>(Translacion_, 0.7, 0.55, 0.0));

  //Colocamos la cintura y las piernas
  setHijo(new CinturaAldeano3D());
  hijos[4] -> setTranformacion(_vertex4<float>(Translacion_, 0.0, -0.2, 0.0));

}

TorsoAldeano3D::~TorsoAldeano3D(){
  delete hijos[0];
  delete hijos[1];
  delete hijos[2];
  delete hijos[3];
  delete hijos[4];
}
