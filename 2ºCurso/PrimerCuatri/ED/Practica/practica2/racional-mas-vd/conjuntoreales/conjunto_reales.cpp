/**
  * @file conjunto_reales.cpp
  * @brief Implementación del TDA Conjunto_Reales
  *
  */

#include <cassert>
#include <conjunto_reales.h>

/* _________________________________________________________________________ */

bool Conjunto_Reales::posicion_elemento(int& pos, float val) const
{
    int izq=0, der=nelementos-1,centro;
    
    while (der-izq>=0) {
        centro=(izq+der)/2;
        if (val<v[centro])
        der=centro-1;
        else if (val>v[centro])
            izq=centro+1;
            else {
            pos=centro;
            return true;
            }
    }
    pos= izq;

    return false;
}

/* _________________________________________________________________________ */

bool Conjunto_Reales::Insertar(float f) 
{
  int pos;
  if (posicion_elemento(pos,f))
    return false;
  else {
    if (v.size()==nelementos)
      if (v.size()==0)
	v.resize(1);
      else v.resize(2*v.size());
    for (int j=nelementos; j>pos; --j)
       v[j]=v[j-1];
       v[pos]=f;
    nelementos++;
    return true;
  }  
}
/* _________________________________________________________________________ */

bool Conjunto_Reales::Borrar(float f) 
{
  int pos;
  if (posicion_elemento(pos,f)) {
    nelementos--;
    for (int j=pos;j<nelementos;++j)
      v[j]=v[j+1];
    if (nelementos<v.size()/4)
      v.resize(v.size()/2);
    return true;
  }
  else return false;
}
