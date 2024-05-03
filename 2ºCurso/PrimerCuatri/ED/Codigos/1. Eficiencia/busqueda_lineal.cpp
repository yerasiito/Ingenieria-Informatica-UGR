
#include <iostream>
using namespace std;

int BusquedaLineal(const int v[], const int n, const int elemento){
  int i, posicion;
  bool encontrado;
  
  i=0;
  encontrado = false;
  while(i<n && !encontrado)
    if (v[i] == elemento){
      posicion = i;
      encontrado = true;
    }
    else
      i++;
  if (encontrado)
    return posicion;
  else
    return -1;
}

int main(int argc, const char * argv[]) {
  int datos[10];
  int valor, posicion;
  
  for(int i=0; i<10; i++)
    datos[i] = i+1;
  
  cout << "Valor a buscar: ";
  cin >> valor;
  posicion = BusquedaLineal(datos, 10, valor);
  if (posicion ==-1)
    cout << "No encontrado" << endl;
  else
    cout << "Encontrado en la posición " << posicion << endl;

  return 0;
}
