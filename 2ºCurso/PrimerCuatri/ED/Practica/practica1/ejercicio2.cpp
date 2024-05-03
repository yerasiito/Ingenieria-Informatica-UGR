#include <iostream>
#include <ctime>

using namespace std;

#define MAXIMO 30000000
int M[MAXIMO];

void crear_matriz( int *M){
  int i;

  for (i=0;i<MAXIMO;i++) 
    M[i]=i;
}

int opera( int *M, int n, int x, int inf, int sup){
  int enc,med;

  enc=0;
  while ((inf<sup) && (!enc)){
    med = (inf+sup)/2; 
     if (M[med]==x) 
       return med;
     else if (M[med] < x) 
       inf = med+1;
     else sup = med-1;
  } 
  if (enc) 
    return med;
  else 
    return -1;
}


int alg2_1(int *M, int n, int x ){
  int i;
 
  for (i=0;i<n ;i++)
    opera(M,n,x,0,n-1);
}

main(){
  clock_t ti,tf;
  int n_datos;
 
  crear_matriz(M);

  for(n_datos=1000000; n_datos<MAXIMO; n_datos+= 500000){
    ti = clock();
    alg2_1(M,n_datos,-1);
    tf = clock();
    cout << n_datos << "\t" << tf - ti << endl;

  }

}
