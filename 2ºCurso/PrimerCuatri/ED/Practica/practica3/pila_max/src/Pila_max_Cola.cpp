/**
* @file Pila_max_Cola.cpp
* @brief Implementación del T.D.A Pila con máximo
*/

#include <cassert>
#include "Pila_max_Cola.h"

/*-----------------------------------------------------------------------*/


Elemento Pila_max::frente(){
  return pila.frente();
}
/*-----------------------------------------------------------------------*/


int Pila_max::elementos_size(){
   return pila.num_elementos();
}


bool Pila_max::empty(){
   return pila.vacia();
}

void Pila_max::quitar(){
   pila.quitar();
}

/*-----------------------------------------------------------------------*/

void Pila_max::poner(int elemento){
	if(empty()){
		Elemento nuevo = {elemento, elemento};
		pila.poner(nuevo);
		return;
	}
	queue<Elemento> aux;
	while(!empty()){
		aux.push(frente());
		quitar();	
	}
	int maximo = aux.front().maximo;
	Elemento nuevo;
	if(elemento>maximo){
	 nuevo = {elemento, elemento};
	}
	else{
	 nuevo = {elemento, maximo};
	}
	pila.poner(nuevo);
	
	while(!aux.empty()) {
		pila.poner(aux.front());
		aux.pop();
	}
}

