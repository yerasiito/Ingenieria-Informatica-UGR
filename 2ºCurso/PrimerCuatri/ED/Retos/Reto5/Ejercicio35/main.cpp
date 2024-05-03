
#include <iostream>
#include "ArbolBinario.hpp"
#include "ejercicio35.cpp"

using namespace std;

template <class Tbase>
void preorden(const ArbolBinario<Tbase>& a,
              const typename ArbolBinario<Tbase>::Nodo n){
  if (n!=0){
    cout << a.etiqueta(n) << ' ';
    preorden(a,a.izquierda(n));
    preorden(a,a.derecha(n));
  }
}

template <class Tbase>
void Esquema(const ArbolBinario<Tbase>& a,
             const typename ArbolBinario<Tbase>::Nodo n, string& pre){

  if (n==0)
    cout << pre << "-- x" << endl;
  else {
    cout << pre << "-- " << a.etiqueta(n) << endl;
    if (a.derecha(n)!=0 || a.izquierda(n)!=0) {// Si no es una hoja
      pre += "   |";
      Esquema(a, a.derecha(n), pre);
      pre.replace(pre.size()-4, 4, "    ");
      Esquema (a, a.izquierda(n), pre);
      pre.erase(pre.size()-4, 4);
    }
  }
}

int main(int argc, const char * argv[]) {
    string pre;
    ArbolBinario<int> a, b, c;


    cout << "Introduce el arbol en el formato:" << endl;
    cout << "n 1 n 2 n 4 x x n 5 x n 8 x x n 3 n 6 x x n 7 x x" << endl;

    //ejecucion del ejercicio 35

     cout << "Introduce un arbol:\n";
     cin >> a;

     cout << "Introduce otro arbol:\n";
     cin >> b;

     sumar_dos_arboles_en_otro(a,b,c);

    Esquema(a, a.raiz(), pre);
    Esquema(b, b.raiz(), pre);
    Esquema(c, c.raiz(), pre);

    
    
    
    
    return 0;
}

