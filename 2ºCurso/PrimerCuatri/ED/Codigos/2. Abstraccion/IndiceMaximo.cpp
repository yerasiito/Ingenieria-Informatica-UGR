#include <iostream>
#include <cassert>

using namespace std;

/**
 @brief Calcula el índice del elemento máximo de un vector
 @param vector array 1-D en el que hacer la búsqueda
 @param tam número de elementos del array \a vector
 
 @pre  \a vector es un array 1-D con al menos \a tam componentes
 @pre  \a tam > 0
 @return el elemento más pequeño en el array \a vector, es decir, 
 el valor i tal que v[i] <= v[j] para 0 <= j <  \a tam 
*/
int IndiceMaximo(int *vector, int tam);

int main() {
  const int TAM = 10;
  int v[TAM];
  
  for (int i=0; i<TAM; i++)
    v[i] = i+1;
  
  for (int i=0; i<TAM; i++)
    cout << v[i] << " ";
  cout << endl;
  
  cout << "Máximo en posición " << IndiceMaximo(v,TAM) << endl;

  return 0;
}

int IndiceMaximo(int *vector, int tam){
  assert(tam>0);
  int indice = 0;
  for (int i=1; i<tam; i++)
    if(vector[i] > vector[indice])
      indice = i;
  return indice;
}


