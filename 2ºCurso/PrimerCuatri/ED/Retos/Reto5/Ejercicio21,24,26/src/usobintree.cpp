/**
 * @file usobintree.cpp
 * @brief archivo de pruebas de funciones de bintree
 * @author Yeray Lopez Ramirez
 * @date diciembre de 2021
 */

#include <iostream>
#include<queue>
#include <list>
#include <limits>
#include "bintree.h"


#include "ejercicios.cpp"

using namespace std;

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
    cout << *v; // acción sobre el nodo v.
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
      cout << *n;
      if (!n.left().null()) nodos.push(n.left());
      if (!n.right().null())
        nodos.push(n.right());
    }
  }
}

int numerocaminos(bintree<int> &ab,int k, bintree<int>::node n){
   if(n.left().null() && n.right().null()) //es una hoja?
      if(*n==k) return 1;
      else return 0;
   else{
      int contador = 0;
      if(!n.left().null())
         contador+=numerocaminos(ab, k - *n, n.left());
      if(!n.right().null())
         contador+=numerocaminos(ab, k - *n, n.right());
      return contador;
   }
}

pair<int,list<int>> caminomen_nodo(bintree<int>::node n){
   if(n.null())
      return pair<int,list<int>>(numeric_limits<int>::max(), list<int>());
   else
      if(n.left().null() && n.right().null()) //Paramos en la hoja
         return pair<int,list<int>>(*n,list<int>(1,*n));
      else{
         pair<int,list<int>> li=caminomen_nodo(n.left());
         pair<int,list<int>> ld=caminomen_nodo(n.right());
         if(li.first<ld.first){
            li.second.push_front(*n);
            li.first += *n;
            return li;
         }
         else{
            ld.second.push_front(*n);
            ld.first += *n;
            return ld;
         }
      }
}

list<int> caminodemenores(bintree<int> &ab){
   return caminomen_nodo(ab.root()).second;
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

void separador(){
   for(int i=0; i < 100; i++)
      cout << "=";
   cout << endl;
}

int main()
{
  /*list<int> camino = caminodemenores(Arb);
  cout << "El camino menores es: ";
  for (auto const &i: camino) {
        cout << i << " ";
  }
  cout << endl;*/

//////////////////////////////////////////////////////////////////////////////////////////////////////

  separador();
  cout << "Funcion 21: pesointerior:" << endl;
  //       30
  //     /    \
  //    21     9
  //  /  \    /
  // 7   14  9
  //        / \
  //       1  13
  bintree<int> pesoArb(30);
  pesoArb.insert_left(pesoArb.root(), 21);
  pesoArb.insert_right(pesoArb.root(), 9);

  pesoArb.insert_left(pesoArb.root().left(), 7);
  pesoArb.insert_right(pesoArb.root().left(), 14);

  pesoArb.insert_left(pesoArb.root().right(), 9);

  pesoArb.insert_left(pesoArb.root().right().left(), 1);
  pesoArb.insert_right(pesoArb.root().right().left(), 8);

  cout << "Preorden:";

  for (bintree<int>::preorder_iterator i = pesoArb.begin_preorder(); i!=pesoArb.end_preorder(); ++i)
    cout << *i << " ";

  cout << endl;


  cout << "Inorden:";

  for (bintree<int>::inorder_iterator i = pesoArb.begin_inorder(); i!=pesoArb.end_inorder(); ++i)
    cout << *i << " ";

  cout << endl;


  cout << "Postorden:";

  for (bintree<int>::postorder_iterator i = pesoArb.begin_postorder(); i!=pesoArb.end_postorder(); ++i)
    cout << *i << " ";

  cout << endl;

  cout << "Por Niveles:";

  for (bintree<int>::level_iterator i = pesoArb.begin_level(); i!=pesoArb.end_level(); ++i)
    cout << *i << " ";
  cout << endl;
  if(pesointerior(pesoArb))
     cout << "Es pesointerior" << endl;
  else
     cout << "No es pesointerior" << endl;

  separador();

//////////////////////////////////////////////////////////////////////////////////////////////////////

  cout << "Funcion 24: sumaparantec:" << endl;
  //       10
  //      /  \
  //     21   6
  //         / \
  //        8  11
  //          / \
  //         12 6
  bintree<int> sumaArb(10);
  sumaArb.insert_left(sumaArb.root(), 21);
  sumaArb.insert_right(sumaArb.root(), 6);

  sumaArb.insert_left(sumaArb.root().right(), 8);
  sumaArb.insert_right(sumaArb.root().right(), 11);

  sumaArb.insert_left(sumaArb.root().right().right(), 12);
  sumaArb.insert_right(sumaArb.root().right().right(),6);

  cout << "Preorden:";

  for (bintree<int>::preorder_iterator i = sumaArb.begin_preorder(); i!=sumaArb.end_preorder(); ++i)
    cout << *i << " ";

  cout << endl;


  cout << "Inorden:";

  for (bintree<int>::inorder_iterator i = sumaArb.begin_inorder(); i!=sumaArb.end_inorder(); ++i)
    cout << *i << " ";

  cout << endl;


  cout << "Postorden:";

  for (bintree<int>::postorder_iterator i = sumaArb.begin_postorder(); i!=sumaArb.end_postorder(); ++i)
    cout << *i << " ";

  cout << endl;

  cout << "Por Niveles:";

  for (bintree<int>::level_iterator i = sumaArb.begin_level(); i!=sumaArb.end_level(); ++i)
    cout << *i << " ";
  cout << endl;
  bintree<int>::node n = sumaArb.root();
  cout << "La suma de parantec es " << sumaparantec(sumaArb,n) << endl;

  separador();

//////////////////////////////////////////////////////////////////////////////////////////////////////

  cout << "Funcion 26: camino_ord:" << endl;
  //        3
  //      /   \
  //     6     7
  //    / \   / \
  //   1   3 9   5
  bintree<int> caminoOrdArb(3);
  caminoOrdArb.insert_left(caminoOrdArb.root(), 6);
  caminoOrdArb.insert_right(caminoOrdArb.root(), 7);

  caminoOrdArb.insert_left(caminoOrdArb.root().left(), 1);
  caminoOrdArb.insert_right(caminoOrdArb.root().left(), 3);

  caminoOrdArb.insert_left(caminoOrdArb.root().right(), 9);
  caminoOrdArb.insert_right(caminoOrdArb.root().right(), 5);

  cout << "Preorden:";

  for (bintree<int>::preorder_iterator i = caminoOrdArb.begin_preorder(); i!=caminoOrdArb.end_preorder(); ++i)
    cout << *i << " ";

  cout << endl;


  cout << "Inorden:";

  for (bintree<int>::inorder_iterator i = caminoOrdArb.begin_inorder(); i!=caminoOrdArb.end_inorder(); ++i)
    cout << *i << " ";

  cout << endl;


  cout << "Postorden:";

  for (bintree<int>::postorder_iterator i = caminoOrdArb.begin_postorder(); i != caminoOrdArb.end_postorder(); ++i)
    cout << *i << " ";

  cout << endl;

  cout << "Por Niveles:";

  for (bintree<int>::level_iterator i = caminoOrdArb.begin_level(); i!=caminoOrdArb.end_level(); ++i)
    cout << *i << " ";
  cout << endl;
  bintree<int>::node nOrdAbr = caminoOrdArb.root();
  if(camino_ord(caminoOrdArb, nOrdAbr))
     cout << "Existe un camino ordenado" << endl;
  else
     cout << "No existe camino ordenado" << endl;

  separador();
  return 0;
}

