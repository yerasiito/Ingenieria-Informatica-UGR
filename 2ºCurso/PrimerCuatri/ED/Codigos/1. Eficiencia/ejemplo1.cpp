#include <iostream>
#include <math.h>
using namespace std;

int main() {
  double a, b, c;
  double r1, r2;
  
  cout << "Coeficiente de 2º grado: ";
  cin >> a;
  cout << "Coeficiente de 1º grado: ";
  cin >> b;
  cout << "Término independiente: ";
  cin >> c;
  
  if (a!=0){
    r1 = (-b + sqrt(b*b-4*a*c))/2*a;
    r2 = (-b - sqrt(b*b-4*a*c))/2*a;
    cout << "Las raíces son: " << r1 << " y " << r2 << endl;
  }
  else{
    r1 = c/b;
    cout << "La única raíz es " << r1 << endl;
  }
  return 0;
}

