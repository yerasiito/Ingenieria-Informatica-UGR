#include <iostream>
#include <vector_dinamico.h>
using namespace std;

void cargar_indices(Vector_Dinamico& v)
{
  for (int i=0;i<v.size();++i)
    v[i]= i;
}
float maximo(const Vector_Dinamico& v)
{
  float max;

  if (v.size()==0) {
    cerr << "Upsss máximo de???? asignamos cero" << endl;
    max= 0.0;
  }
  else {
    max=v[0];
    for (int i=1;i<v.size();++i)
      if (max<v[i])
	max=v[i];
  }
  return max;
}

int main()
{
  Vector_Dinamico vec;
  
  Vector_Dinamico vec2;
  
  cargar_indices(vec); 
  
  
  cout << "Máximo de "<< vec.size() << " elementos: " << maximo(vec) << endl;
  vec.resize(10);
  cargar_indices(vec);
  Vector_Dinamico vec1(vec);
  vec2=vec1;
   
  cout << "Máximo de "<< vec.size() << " elementos: " << maximo(vec) << endl;
  cout << "Máximo de "<< vec1.size() << " elementos: " << maximo(vec1) << endl;
  cout << "Máximo de "<< vec2.size() << " elementos: " << maximo(vec2) << endl;
  return 0; 
}
