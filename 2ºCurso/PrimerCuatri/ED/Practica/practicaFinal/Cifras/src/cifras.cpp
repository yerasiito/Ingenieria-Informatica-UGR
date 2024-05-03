
/**
 @file Cifras.cpp
 @brief Implementación de TDA Cifras
*/

#include <iostream>
#include <vector>
#include <random>
#include "cifras.h"
#include "Busqueda.h"

using namespace std;


	/**
	IMPLEMENTACIÓN
	*/
	
	void Cifras::resize(int tam){
		numeros.resize(tam);
	}	
	int Cifras::getTam(){
		return numeros.size();
	}
	int Cifras::getAtPos(int pos){
		return numeros[pos];
	}
	void Cifras::in(int numero){
		numeros.push_back(numero);
	}
	
	vector<int> Cifras::out(int cant){
		vector<int> los_elegidos;
		srand(time(NULL));
		
		for(int i=0; i<cant; ++i){
			int posicion_elegida = rand() % getTam();
			int elegido = numeros[posicion_elegida];
			numeros.erase(numeros.begin() + posicion_elegida);
			los_elegidos.push_back(elegido);
			
		}
		
		return los_elegidos;
	}
	
	void Cifras::search(int resultado, Cifras &conjunto){
	}
