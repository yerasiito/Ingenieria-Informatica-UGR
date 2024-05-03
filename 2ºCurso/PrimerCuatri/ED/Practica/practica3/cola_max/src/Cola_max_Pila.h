/**
* @file Cola_max_Pila.h
* @brief Fichero cabecera del T.D.A Cola con máximo.
*
*  Gestiona una secuencia de elementos con facilidades para la inserción y
*  borrado de elementos en un extremo.
*/

#ifndef __COLA_MAX_PILA__
#define __COLA_MAX_PILA__

#include <cassert>
#include <stack>
#include <iostream>
#include "pila.h"


using namespace std;

/**
* 
* @brief T.D.A Cola con máximo.
* Una instancia @e A del tipo abstracto de dato @A cola con máximo es un objeto que representa una cola tipo FIFO que guarda el máximo de todos sus elementos en una cola paralela
* a la cola en la se guardan los datos, de forma que se pueda consultar el máximo directamente en una de las colas y en la otra se guardan los elementos de por sí. 
* Basado en el tipo de dato propio proporcionado por Prof. Joaquín Valdivia "pila.h" y parcialmente en std::stack de la STL.
*
*
* @author Yeray Lopéz Ramírez
* @author Jaime Castillo Uclés
* @date 27 NOV 2021
*/
/**
* @brief T.D.A. Elemento de la cola
* Una instancia del tipo abstracto Elemento de la cola que contiene dos elementos, un dato y un máximo de la cola hasta ese punto de la cola.
*
*/
struct Elemento{
	int elemento;
	int maximo;
		/**
		* @brief Operador <<
		* @param os stream de salida
		* @param elemento Elemento de salida
		* @return instancia del ostream
		*/
		friend ostream& operator<<(ostream &os, const  Elemento& elem){
		    	os << elem.elemento << " (" << elem.maximo << ")" << endl;
		    	return os;
	    	};
	};

class Cola_max{
private:
	
	Pila<Elemento> cola;
public:	
	
  /**
     * @brief Función frente
     * @pre Se necesita mínimo un valor en la cola previo
     * @return Devuelve el elemento en el frente de la cola
     */
   Elemento frente();

   /**
     * @brief Funcion elementos_size
     * @return Devuelve la cantidad de elementos que contiene la cola
     */
   int elementos_size();

   /**
     * @brief Función empty
     * @return Devuelve true si la cola está vacía (las dos colas están vacías)
     */
   bool empty();

   /**
     * @brief Función quitar, elimina el elemento que se encuentra en el frente de la cola y su máximo correpondiente.
     * @pre Se necesita mínimo un valor en la cola previo
     */
   void quitar();

   /**
     * @brief Función poner, añade un nuevo elemento a la cola y actualiza el máximo
     * @param Elemento a añadir
     */
   void poner(int elemento);

};

#endif




