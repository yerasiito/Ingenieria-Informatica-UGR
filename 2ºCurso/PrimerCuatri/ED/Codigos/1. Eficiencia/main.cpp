#include <iostream>
using namespace std;

int calculareficiencia (bool existe){
  int sum = 0; int n=1000;
  if (existe)
    for(int i=1; i<=n; i*=2)
      for(int j=1; j<=i; j++)
        sum++;
  else
    for(int i=1; i<=n; i*=2)
      for(int j=1; j<=n; j++)
        sum++;
  return sum;
}


int main(int argc, const char * argv[]) {
//  {
//    int sum = 0;
//    int n = 1000000;
//  
//    for(int i=1; i<=n; i*=2)
//      for(int j=1; j<=i; j++)
//        sum++;
//    cout << sum << endl;
//  
//    for(int i=1; i<n; i*=2)
//      for(int j=1; j<=n; j++)
//        sum++;
//    cout << sum << endl;
//  }
  
//  { //O(nlog_2 n)
//    int n=1000, j;
//    int i = 1;
//    int x = 0;
//    do{
//      j=1;
//      while(j<=n){
//        j = j * 2; //+?
//        x++;
//      }
//      i++;
//    }while(i<=n);
//    cout << x << endl;
//  }
  
//  {
//    int n=1000;
//    int i=2, j, x=0;
//    do{
//      j=1;
//      while(j<i){
//        j = j * 2;
//        x++;
//      }
//      i++;
//    }while(i<=n);
//    cout << x << endl;
//  }
  
//  {
//    int n = 1000;
//    int x = 0;
//    for(int i=1; i<=n; i+=4)
//      for(int j=1; j<=n; j+=n/4)
//        for(int k=1; k<=n; k*=2)
//          x++;
//    cout << x << endl;
//  }
  

  {
    cout << calculareficiencia(true) << endl;
  }
  
  
  
  return 0;
}

