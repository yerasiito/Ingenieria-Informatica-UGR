#include <iostream>
#include <ctime>

using namespace std;

long fib( int n)
{

  if (n<=1) 
    return 1;
  else 
    return fib(n-1) + fib(n-2);

}


int main(){

  int i;
  clock_t inicio, fin;
  float ciclos = CLOCKS_PER_SEC;

  for (i=20;i<=50;i++){
      inicio = clock();
 
      fib(i);

      fin = clock();
      cout << i << " " <<(fin-inicio) << endl;
    }
}
     

