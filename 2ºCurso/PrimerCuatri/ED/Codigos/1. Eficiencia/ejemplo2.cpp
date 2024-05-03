#include <iostream>
using namespace std;

int main() {
  int n=10, contador=0;
  
  for(int i=1; i<n; i++)
    for(int j=i+1; j<n+1; j++)
      for(int k=1; k<j+1; k++){
        // Sentencia O(1)
        cout << i << " " << j << " " << k << endl;
        contador++;
      }
  cout << contador << endl;
  return 0;
}
