/**
* @file Pila_max_Cola.h
* @brief Fichero cabecera del T.D.A Pila con máximo.
*
*  Gestiona una secuencia de elementos con facilidades para la inserción y
*  borrado de elementos en un extremo.
*/

#ifndef __PILA_MAX_COLA__
#define __PILA_MAX_COLA__

#include <cassert>
#include <queue>
#include <iostream>
#include "cola.h"


using namespace std;

/**
* 
* @brief T.D.A Pila con máximo.
* Una instancia @e A del tipo abstracto de dato @A pila con máximo es un objeto que representa una pila tipo que guarda el máximo de todos sus elementos en una pila paralela
* a la pila en la se guardan los datos, de forma que se pueda consultar el máximo directamente en una de las pilas y en la otra se guardan los elementos de por sí. 
* Basado en el tipo de dato propio proporcionado por Prof. Joaquín Valdivia "cola.h" y parcialmente en std::queue de la STL.
*
*
* @author Yeray Lopéz Ramírez
* @author Jaime Castillo Uclés
* @date 27 NOV 2021
*/

/**
* @brief T.D.A. Elemento de la pila
* Una instancia del tipo abstracto Elemento de la pila contiene dos elementos, un dato y un máximo de la pila hasta ese punto de la pila.
*
*/
struct Elemento{
	int elemento;
	int maximo;
		/**
		* @brief Operador <<
		* @param os stream de salida
		* @param elem Elemento de salida
		* @return instancia del ostream
		*/
		friend ostream& operator<<(ostream &os, const  Elemento& elem){
		    	os << elem.elemento << " (" << elem.maximo << ")" << endl;
		    	return os;
	    	};
	};

class Pila_max{
private:
	
	Cola<Elemento> pila;
public:	
	
  /**
     * @brief Función frente
     * @pre Se necesita mínimo un valor en la pila previo
     * @return Devuelve el elemento en el frente de la pila
     */
   Elemento frente();

   /**
     * @brief Funcion elementos_size
     * @return Devuelve la cantidad de elementos que contiene la pila
     */
   int elementos_size();

   /**
     * @brief Función empty
     * @return Devuelve true si la pila está vacía
     */
   bool empty();

   /**
     * @brief Función quitar, elimina el elemento que se encuentra en el frente de la pila y su máximo correpondiente.
     * @pre Se necesita mínimo un valor en la pila previo
     */
   void quitar();

   /**
     * @brief Función poner, añade un nuevo elemento a la pila y actualiza el máximo
     * @param Elemento a añadir
     */
   void poner(int elemento);

};

#endif




