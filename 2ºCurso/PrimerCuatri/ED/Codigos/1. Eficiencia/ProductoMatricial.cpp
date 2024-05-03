#include <iostream>

using namespace std;

int main() {
  
  int TAM = 10;
  int A[TAM][TAM], B[TAM][TAM], C[TAM][TAM];
  int n = 3, x;
  
  x=0;
  for(int i=0; i<n; i++)
    for(int j=0; j<n; j++){
      A[i][j] = B[i][j] = ++x;
      
    }
  
  for(int i=0; i<n; i++)
    for(int j=0; j<n; j++){
      C[i][j] = 0;
      for( int k=0; k<n; k++)
        C[i][j] += A[i][k]*B[k][j];
    }
  
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++)
      cout << C[i][j] << " ";
    cout << endl;
  }

  return 0;
}
