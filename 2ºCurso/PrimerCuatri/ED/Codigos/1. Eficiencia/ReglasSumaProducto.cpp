
#include <iostream>

using namespace std;

int main(int argc, const char * argv[]) {
  int n= 10;
  int A[n][n];
  
  for (int i=0; i<n; i++)
    for (int j=0; j<n; j++)
      A[i][j] = 0;
  for (int k=0; k<n; k++)
    A[k][k] = 1;
  
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++)
      cout << A[i][j];
    cout << endl;
  }
  
  k=0;
  while(k<n && k)
    
  
  return 0;
}
