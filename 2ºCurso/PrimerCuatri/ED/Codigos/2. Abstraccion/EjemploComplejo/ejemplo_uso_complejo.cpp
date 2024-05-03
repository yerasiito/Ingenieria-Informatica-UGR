//
//  main.cpp
//  Ejemplo_Complejo
//
//  Created by Javier Abad on 16/8/17.
//  Copyright © 2017 Javier Abad. All rights reserved.
//

#include <iostream>
#include "Complejo.hpp"

int main() {

  Complejo c1, c2;
  cout << "Introduzca un complejo con el formato (r,i)" << endl;
  cin >> c1;
  cout << "Introduzca otro complejo con el formato (r,i)" << endl;
  cin >> c2;
  
  cout << "La suma de los dos complejos es " << c1+c2
  << "y su diferencia es " << c1-c2 << endl;
  
  cout << "Si sumamos 1 al primer complejo el resultado es " << c1+ 1 << endl;
  cout << "Si al segundo complejo le restamos 1 el resultado es "
  << c2-1 << endl;
  return 0;
}
