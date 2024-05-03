#include <iostream>
#include <ctime>

using namespace std;
 
 
void hanoi (int M, int i, int j)
{
  if (M>0) {
    hanoi(M-1,i, 6-i-j);
    // cout << i << "->" << j << endl; 
    hanoi (M-1,6-i-j, j);
  }
}
 

int main()
{

  int i;
  clock_t inicio;
  clock_t fin;

  
  for (i=20;i<=35;i++)
    {
      inicio = clock();
 
      hanoi(i,1,2);

      fin = clock();
      
      cout << i << " " <<(fin-inicio) << endl;
      
    }
}
     

