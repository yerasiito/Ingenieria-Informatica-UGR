#include <iostream>
using namespace std;

void intercambiar(int &a, int &b){
  int aux = a;
  a = b;
  b = aux;
}

void OrdenacionSeleccion (int v[], int n){
  int minimo, aux;
  
  for(int i=0; i<n; i++){
    minimo = i;
    
    for(int j=i+1; j<n; j++)
      if (v[j]<v[minimo])
        minimo = j;
    
    intercambiar(v[minimo],v[i]);
  }
}

int main() {
  
  int vector[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  
  OrdenacionSeleccion(vector, 10);
  
  for(int i=0; i<10; i++)
    cout << vector[i] << " ";
  cout << endl;
  return 0;
}
