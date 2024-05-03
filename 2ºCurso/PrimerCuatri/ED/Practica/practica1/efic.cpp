#include <iostream>
#include <ctime>

using namespace std;

#define MAXIMO 200000

void crear_matriz(int *M){
  int i;

  for (i=0; i<MAXIMO; i++) //recorremos la matriz
    M[i]=i;                //En cada posicion escribimos su índice
}

int busqueda_lineal( int *M, int n, int x){
  int i, encontrado;

  //Busqueda lineal con centinela
  for (i=0,encontrado=0; i<n && !encontrado; i++) 
    if (M[i]==x) 
      encontrado=1;

  if (encontrado)
    return i;
  else 
    return -1;
}


void orden_n2_puro(int *M, int n, int x ){
  int i;
 
  for (i=0; i<n; i++)
    busqueda_lineal(M,n,x);
}

int main(void){
  clock_t ti, tf;
  int n_datos;
  int M[MAXIMO];
 
  crear_matriz(M);

  for(n_datos=10000; n_datos<200000; n_datos+= 5000){
    ti = clock();
    //Buscamos un elemento inexistente para forzar un O(n^2) puro
    orden_n2_puro(M,n_datos,-1);
    tf = clock();
    cout << n_datos << "\t" << tf - ti << endl;
  }
}
