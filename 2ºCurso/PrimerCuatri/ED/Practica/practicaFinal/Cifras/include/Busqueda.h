/**
	@file Busqueda.h
	@brief Cabecera del TDA Busqueda
*/
#ifndef _BUSQUEDA_H
#define _BUSQUEDA_H

#include <iostream>
#include <cifras.h>
#include <vector>

using namespace std;


/**
	@file TDA Búsqueda
	@brief Una instancia del TDA Búsqueda es un árbol n-ario que almacena todos los posibles valores de las todas las posibles operaciones que lleven al número determinado.
	De esta forma, el árbol n-ario quedaría teniendo N nodos del conjunto un nodo para cada número del conjunto. Y luego cada nodo tendría 4 nodos con cada operación (+,-,*,/) para cada uno de 		los otros nodos que restantes que no se han usado.
	@author Jaime Castillo Uclés & Yeray López Ramírez
*/

class Busqueda{
private:
	/**
		@brief Struct Celda sirve para almacenar el nodo del árbol
	*/
	
	struct Celda{
		int etiqueta;
		Celda *padre, *hijoizq, *hermdrcha;	
	};
	
	
public:
	/**
		@brief Constructor del árbol n-ario, construye un árbol vacío.
	*/
	Busqueda();
	/**
		@brief Destructor del árbol n-ario
	*/
	~Busqueda();
	/**
		 @brief Construye el árbol con la estructura necesaria a las operaciones y al conjunto. A partir del pasarle el conjunto.
		 @param conjunto Conjunto de números
	 */
	void construir(vector<int> conjunto);
	
	// Funciones de uso //
	/**
		@brief Insertar un hijo a la izquierda. Necesario en método construir.
	*/
	void insertarhijoizqda(Celda *T1, Celda *n, Celda *T2){
		if(T2 != 0)
		{
			T2->hermdrcha=n->hijoizq;
			T2->padre=n;
			T2=0;
		}
	}
	/**
		@brief Podar hijo a la izq. Necesario para descartar las no-soluciones, de forma que cuando se encuentre la solución solo haya que listarlo en preorden.
		@return Hijo podado
	*/
	Celda *PodarHijoIzq(Celda *T, Celda *n){
		Celda *Res=0;
		if(n->hijoizq !=0){
			Res=n->hijoizq;
			n->hijoizq=Res->hermdrcha;
			Res->padre=Res->hermdrcha=0;
			}
		return Res;
		
	}
	/**
		@brief Insertar hermano a la derecha
	*/
		
	void insertarhermdrcha();
	/**
		@brief Lista el árbol por preorden.
	*/
	void ListarPreorden(Celda *T);
	/**
		@brief Busca el número en el árbol y devuelve todas las operaciones asociadas, siguiendo los caminos del árbol desde la raíz hasta el nodo localizado ( al haber quitado con otros 			métodos las no-soluciones anteriores al encontrar la solución llegar a la solución es tan simple como recorrer en preorden hasta llegar al número deseado, esas operaciones serán la 			solución a almacenar).
		@param num El número solución
		@return Vector de vectores de char con las operaciones que se han empleado. Ordenadas desde la primera hasta la última.
		
	*/
	vector<vector<char>> busca(int num);
};
#endif
