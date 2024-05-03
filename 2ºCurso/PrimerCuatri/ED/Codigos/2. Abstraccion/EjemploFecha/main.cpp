#include <iostream>
#include "fecha.h"

using namespace std;

int main() {
  Fecha f, g;
  int dia, mes, anio;
  char c1[100], c2[100];
  
  std::cout << "Introduzca el día del mes que es hoy: ";
  cin >> dia;
  cout << "Introduzca el mes en el que estamos: ";
  cin >> mes;
  cout << "Introduzca el año en el que estamos: ";
  cin >> anio;
  
  constructor(f, dia, mes, anio);
  Siguiente(f, g);
  if (menor(f, g)){
    Escribe(f, c1);
    Escribe(g, c2);
    cout << "El día " << c1 << " es anterior a " << c2 << endl;
  }
  return 0;
}


int suma(int v[], int n){
  int s=0, i=0;
  while(i/=n){
    i = i+1;
    s += v[i];
  }
  return s;
}
