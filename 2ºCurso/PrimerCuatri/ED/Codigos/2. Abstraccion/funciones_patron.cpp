//
//  main.cpp
//  funciones_patron
//
//  Created by Javier Abad on 16/8/17.
//  Copyright © 2017 Javier Abad. All rights reserved.
//

#include <iostream>
#include "Complejo.hpp"
using namespace std;


template <class T>
T minimo (const T &a, const T &b){
  return(a < b ? a : b);
}


template <class T>
void intercambiar(T &a, T &b){
  T aux = a;
  a = b;
  b = aux;
}


template <class T>
void ordenar_seleccion(T * vector, int tam){
  int pos_minimo;
  for(int i=0; i<tam; i++){
    pos_minimo = i;
    for(int j=i+1; j<tam; j++)
      if(vector[j] < vector[pos_minimo])
        pos_minimo = j;
    intercambiar(vector[i], vector[pos_minimo]);
  }
}

int main() {
  int a = 3, b= 5;
  cout << "Antes del cambio: a = " << a << " y b = " << b << endl;
  intercambiar(a, b);
  cout << "Después del cambio: a = " << a << " y b = " << b << endl;
  
  cout << "El mínimo de " << a << " y " << b << " es " << minimo(a,b) << endl;
  
  Complejo c1(1,2), c2(3,4);
  
  cout << "Antes del cambio: c1 = " << c1 << " y c2 = " << c2 << endl;
  intercambiar(c1, c2);
  cout << "Después del cambio: c1 = " << c1 << " y c2 = " << c2 << endl;

//  cout << "El mínimo de " << c1 << " y " << c2 << " es " << minimo(c1,c2) << endl;

  int tam = 100;
  int v[tam];
  for (int i=0; i<tam; i++)
    v[i] = tam -i;
  
  for(int i=0; i<tam; i++)
    cout << v[i] << " ";
  cout << endl;

  ordenar_seleccion(v, tam);
  
  for(int i=0; i<tam; i++)
    cout << v[i] << " ";
  cout << endl;

  return 0;
}
