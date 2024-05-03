/**
* @file Colas_max_Pila.cpp
* @brief Implementación del T.D.A Colas con máximo
*/

#include <cassert>
#include "Cola_max_Pila.h"

/*-----------------------------------------------------------------------*/


Elemento Cola_max::frente(){
  return cola.tope();
}
/*-----------------------------------------------------------------------*/


int Cola_max::elementos_size(){
   return cola.num_elementos();
}


bool Cola_max::empty(){
   return cola.vacia();
}

void Cola_max::quitar(){
   cola.quitar();
}
/*-----------------------------------------------------------------------*/

void Cola_max::poner(int elemento){
	if(empty()){
		Elemento nuevo = {elemento, elemento};
		cola.poner(nuevo);
		return;
	}
	Pila<Elemento> aux;
	while(!empty()){
		aux.poner(frente());
		quitar();	
	}
	int maximo = aux.tope().maximo;
	Elemento nuevo;
	if(elemento>maximo){
	 nuevo = {elemento, elemento};
	}
	else{
	 nuevo = {elemento, maximo};
	}
	cola.poner(nuevo);
	
	while(!aux.vacia()) {
		cola.poner(aux.tope());
		aux.quitar();
	}
}

