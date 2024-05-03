//María Mingjie Párraga Ramos

#include <iostream>
#include<queue>
#include "bintree.h"
using namespace std;


#include "ejercicios36,41,44.cpp"

template <class T>
bool esHoja(const bintree<T> & A, const typename bintree<T>::node &v)
{
  return ( v.left().null()  && v.right().null() );
}

template <class T>
bool esInterno(const bintree<T> & A, const typename bintree<T>::node &v)
{
  return ( !v.left().null() || !v.right().null() );
}

template <class T>
void PreordenBinario(const bintree<T> & A,
                     typename bintree<T>::node v) {
  if (!v.null()) {
    cout << *v << " "; // acción sobre el nodo v.
    PreordenBinario(A, v.left());
    PreordenBinario(A, v.right());
  }
}

template <class T>
void InordenBinario(const bintree<T> & A,
                    typename bintree<T>::node v)
{
  if (!v.null()) {
    InordenBinario(A, v.left());
    cout << *v; //acción sobre el nodo v.
    InordenBinario(A, v.right());
  }
}

template <class T>
void PostordenBinario(const bintree<T> & A,
                      typename bintree<T>::node v)
{
  if (!v.null()) {
    PostordenBinario(A, v.left());
    PostordenBinario(A, v.right());
    cout << *v; // acción sobre el nodo v.
  }
}

template <class T>
void ListarPostNiveles(const bintree<T> &A, typename bintree<T>::node n) {
  queue<typename bintree<T>::node> nodos;
  if (!n.null()) {
    nodos.push(n);
    while (!nodos.empty()) {
      n = nodos.front(); nodos.pop();
      cout << *n << " ";
      if (!n.left().null()) nodos.push(n.left());
      if (!n.right().null())
        nodos.push(n.right());
    }
  }
}


template <class T>
ostream & operator << (ostream & os, bintree<T> &arb)
{

  cout << "Preorden:";

  for (typename bintree<T>::preorder_iterator i = arb.begin_preorder(); i!=arb.end_preorder(); ++i)
    cout << *i << " ";

  cout << endl;
  return os;
}

bintree<int>::node AMC(const bintree<int> &A, bintree<int>::node v, bintree<int>::node w) {
    bintree<int>::node ancestro;
    
    // Primero hacemos que ambos estén en el mismo nivel, entonces
    // encontrar el ancestro común más cercano será ir subiendo en los
    // padres de cada uno hasta que coincidan
    int prof_v = getProfundidad(A, v), prof_w = getProfundidad(A, w);
    if ( prof_v < prof_w )
        for ( int i = 0; i < prof_w-prof_v; ++i )
            w = w.parent();
    else if ( prof_v > prof_w )
        for ( int i = 0; i < prof_v-prof_w; ++i )
            v = v.parent();
    
    // caso límite
    if ( v == w )
        return v;
    
    bool continuar = true;
    while ( continuar ) {
        v = v.parent();
        w = w.parent();
        
        if ( v == w ) {
            ancestro = v;
            continuar = false;
        }
    }
    
    return ancestro;
}

bool tienenigualvolumen(bintree<int> A, bintree<int> B){ //Devuelve true si el num de hojas * la altura de ambos árboles es igual y false en caso contrario
    int profA = altura(A.root()), profB = altura(B.root()), hojasA = A.size(), hojasB = B.size();
    return ( (hojasA * profA) == (hojasB * profB) );
} 

int main()
{  // Creamos el árbol:
  //        7
  //     /    \
  //    1      9
  //  /  \    /
  // 6    8  5
  //       \
  //       4
//  typedef bintree<int> bti;
  bintree<int> Arb(7);
  Arb.insert_left(Arb.root(), 1);
  Arb.insert_right(Arb.root(), 9);
  Arb.insert_left(Arb.root().left(), 6);
  Arb.insert_right(Arb.root().left(), 8);
  Arb.insert_left(Arb.root().right(), 5);
  Arb.insert_right(Arb.root().left().right(), 4);
  
  cout << endl << "---------EJERCICIO 36-----------------" << endl;
  
  bintree<int>::node w = Arb.laraiz.left().left();
  bintree<int>::node v = Arb.laraiz.right().left();
  bintree<int>::node ancestro = AMC(Arb,v,w);
  cout << "El ancestro es " << *ancestro << endl;

  cout << "El arbol probado es:(escrito por niveles): ";
  ListarPostNiveles(Arb,ancestro);
  cout << endl;
  
  cout << endl << "---------EJERCICIO 41-----------------" << endl;
  
  bintree<int>::node u = Arb.laraiz.left().left();
  cout << "El arbol probado es:(escrito por niveles): ";
  ListarPostNiveles(Arb,ancestro);
  cout << endl;

  int nivel = enquenivel(u, Arb);
    
  cout << "El nodo " << *u << " está a nivel " << nivel << endl;
  
  cout << endl << "---------EJERCICIO 44-----------------" << endl;
  
  bintree<int> A(7);
  A.insert_left(A.root(), 1);
  A.insert_right(A.root(), 9);
  A.insert_left(A.root().left(), 6);
  A.insert_right(A.root().left(), 8);
  A.insert_left(A.root().right(), 5);
  A.insert_right(A.root().left().right(), 4);
  
  bintree<int> B(1);
  B.insert_left(B.root(), 2);
  B.insert_right(B.root(), 3);
  B.insert_left(B.root().left(), 4);
  B.insert_right(B.root().left(), 5);
  B.insert_left(B.root().right(), 6);
  B.insert_right(B.root().left().right(), 4);
  
  cout << "El arbol A es:(escrito por niveles): ";
  ListarPostNiveles(A,A.root());
  cout << "\nEl arbol B es:(escrito por niveles): ";
  ListarPostNiveles(B,B.root());

  cout << "\n¿Tienen igual volumen?" << endl;
  if(tienenigualvolumen(A,B)){
      cout << "True" << endl;
  }
  else
      cout << "False" << endl;
}
