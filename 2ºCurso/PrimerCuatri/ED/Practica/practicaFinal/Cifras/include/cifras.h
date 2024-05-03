/**
	@file Cifras.h
	@brief Cabecera del TDA Cifras
*/
#ifndef _CIFRAS_H
#define _CIFRAS_H

#include <iostream>
#include <vector>
#include "Busqueda.h"
using namespace std;


/**
  *  @brief T.D.A. Cifras
  *
  * Una instancia @e c del tipo de datos abstracto @c Cifras es un objeto
  * que almacena el conjunto de unos números y permite operar con ellos de una forma específica.
  *
  *
  * @author Yeray López Ramírez y Jaime Castillo Uclés
  * @date Diciembre 2021
  */


class Cifras{
private:
	vector<int> numeros;
public:
	/**
	 	@brief Constructor
	 */
	 Cifras(){
	 	numeros.clear();
	 }
	/**
	 	@brief Destructor
	 */
	 ~Cifras(){
		numeros.clear();
   	 }
   	 /**
   	 	@brief Redimensiona el vector de cifras
   	 */
	void resize(int tam);
	/**
		@brief Obtiene el tamaño del vector
		@return Tamaño del vector
	*/
	int getTam();
	/**
		@brief Obtiene un valor de una posición concreta del vector
		@param pos Posición
		@return El valor de la posición
	*/
	int getAtPos(int pos);
	/**
		@brief Introduce un número al vector
		@param numero Número a meter
	*/
	void  in(int numero);
	/**
		@brief Obtener sub-conjunto aleatoriamente. Crea un subvector donde introduce elementos del otro, utiliza la función rand, para obtener una posicion de todo el
		tamaño del vector asi una vez saca una posición aleatoria saca un número aleatorio, se actualizan las posiciones.
		@param cant Cantidad de números en el subconjunto
		@return Vector de números aleatorios
	*/
	vector<int> out(int cant);
	/**
		@brief Obtiene todas las operaciones con el subconjunto que dan el resultado pedido y las imprime por pantalla. En él, se utiliza una instancia del TDA Búsqueda (árbol n-ario) 			que será el soporte para realizar la búsqueda. Desde este método, se mostrarán directamente por pantalla estándar las soluciones.
		@param resultado Resultado pedido
		@param conjunto Subconjunto de números
	*/
	void search(int resultado, vector<int> &conjunto);
};
#endif
