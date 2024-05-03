#include <iostream>
#include <conjunto_reales.h>
using namespace std;


void ListarConjunto(const Conjunto_Reales& c)
{
  cout << "Conjunto de " << c.size() << " elementos:" << endl;
  for (int i=0;i<c.size();++i)
    cout << "  Elemento: " << c.Elemento(i) << endl;
}

int main()
{
  Conjunto_Reales c, d, inter, dif;
  
  for (int i=0;i<10;++i) c.Insertar(i);
  for (int i=0;i<10;i+=2) c.Borrar(i);   

  ListarConjunto(c);

  for (int i=0;i<10;++i) d.Insertar(i);
  for (int i=0;i<10;i+=3) d.Borrar(i);   

  ListarConjunto(d);

  for (int i=0;i<c.size();++i)
      if (d.Pertenece(c.Elemento(i)))
          inter.Insertar(c.Elemento(i));
  
  ListarConjunto(inter);
  
  for (int i=0;i<c.size();++i)
      if (!d.Pertenece(c.Elemento(i)))
          dif.Insertar(c.Elemento(i));
      
   for (int i=0;i<d.size();++i)
      if (!c.Pertenece(d.Elemento(i)))
          dif.Insertar(d.Elemento(i));   
      
      
ListarConjunto(dif);
}


