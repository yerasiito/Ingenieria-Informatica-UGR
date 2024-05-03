#include <iostream>

using namespace std;

void mi_funcion(const int n){
  int x, contador;
  contador = 0;
  x = 2;
  while (x<=n){
    x = 2 * x;
    contador++;
  }
  cout << contador << endl;
}

int main() {

  mi_funcion(100000000);
  
  return 0;
}
