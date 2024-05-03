#include <iostream>
using namespace std;


int main() {
  
  int n = 10, x = 0, y = 0;
  
  for(int i=1; i<n+1; i++)
    if(i%2==0){
      for(int j=i; j<n+1; j++)
        x++;
      for(int j=1; j<i+1; j++)
        y++;
    }
  
  cout << "x = " << x << endl;
  cout << "y = " << y << endl;
  
  return 0;
}
