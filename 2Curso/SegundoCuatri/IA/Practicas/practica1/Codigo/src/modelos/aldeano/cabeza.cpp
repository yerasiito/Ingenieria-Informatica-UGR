#include "modelos/aldeano/cabeza.hpp"

CabezaAldeano3D::CabezaAldeano3D(const std::string & filename) : Objeto3D(){

  //Colocamos la cara
  //setHijo(new Retrato3D(filename));
  //hijos[0] -> setTranformacion(_vertex4<float>(Translacion_, -0.5, 0.0, 0.501));

  //Colocamos la cabeza
  setHijo(new CuboObj3D());
  hijos[0] -> setTranformacion(_vertex4<float>(Translacion_, 0.0, 0.5, 0.0));
  hijos[0] -> setColor(_vertex3<float>(255.0/255.0, 153.0/255.0, 102.0/255.0));
  hijos[0] -> setAmb(_vertex4<float>(255.0/255.0, 153.0/255.0, 102.0/255.0, 1.0));
  hijos[0] -> setDiff(_vertex4<float>(255.0/255.0, 153.0/255.0, 102.0/255.0, 1.0));
  hijos[0] -> setSpec(_vertex4<float>(255.0/255.0, 153.0/255.0, 102.0/255.0, 1.0));

  //Colocamos el pelo
  setHijo(new CuboObj3D());
  hijos[1] -> setTranformacion(_vertex4<float>(Escalado_, 1.1, 0.8, 1.1));
  hijos[1] -> setTranformacion(_vertex4<float>(Translacion_, 0.0, 0.8, -0.05));
  hijos[1] -> setColor(_vertex3<float>(82.0/255.0, 41.0/255.0, 0.0/255.0));
  hijos[1] -> setAmb(_vertex4<float>(82.0/255.0, 41.0/255.0, 0.0/255.0, 1.0));
  hijos[1] -> setDiff(_vertex4<float>(82.0/255.0, 41.0/255.0, 0.0/255.0, 1.0));
  hijos[1] -> setSpec(_vertex4<float>(82.0/255.0, 41.0/255.0, 0.0/255.0, 1.0));
}

CabezaAldeano3D::~CabezaAldeano3D(){
  delete hijos[0];
  delete hijos[1];
}
