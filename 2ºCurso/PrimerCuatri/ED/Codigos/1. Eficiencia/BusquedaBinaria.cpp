#include <iostream>
using namespace std;

int BusquedaBinaria(const int v[], const int n, const int elemento){
  int izquierda, derecha, centro;
  
  izquierda=0;
  derecha = n-1;
  centro = (izquierda + derecha)/2;
  while(izquierda<=derecha && v[centro]!=elemento){
    if (v[centro] > elemento)
      derecha = centro - 1;
    else
      izquierda = centro + 1;
    centro = (izquierda + derecha)/2;
  }
  if (izquierda > derecha)
    return -1;
  else
    return centro;
}

int main(int argc, const char * argv[]) {
  int datos[10] = {};
  int valor, posicion;
  
  for(int i=0; i<10; i++)
    datos[i] = i;

  for(int i=0; i<10; i++)
    cout << datos[i] << endl;

  cout << "Valor a buscar: ";
  cin >> valor;
  posicion = BusquedaBinaria(datos, 10, valor);

  if (posicion ==-1)
    cout << "No encontrado" << endl;
  else
    cout << "Encontrado en la posición " << posicion << endl;
  
  return 0;
}
