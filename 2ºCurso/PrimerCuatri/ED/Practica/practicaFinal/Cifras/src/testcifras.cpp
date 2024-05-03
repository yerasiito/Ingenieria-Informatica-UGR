/**
	@file testcifras.cpp
	@brief Test para probar el programa cifras
*/
	

#include <iostream>
#include <vector>
#include <random>
#include "cifras.h"

using namespace std;

int main( int argc, char *argv[]){
	int cantidad;
	cout<<"Introduce la cantidad de números en el conjunto"<<endl;
	cin>>cantidad;
	
	Cifras numeros;
	
	for(int a=0; a<numeros.getTam(); ++a){
		cout<<numeros.getAtPos(a)<<endl;
	}
	for(int i=0; i<cantidad; ++i){
		int num = 0;
		cout<<"Introduce el "<<i<<" número del conjunto"<<endl;
		cin>>num;
		numeros.in(num);
	}
	cout<<"	Comienza el juego	"<<endl;
	cout<<"	Se va a obtener un subconjunto...	"<<endl;
	int tam;
	int conseguir;
	cout<<"Dime la cantidad de números que tendrá"<<endl;
	cin>>tam;
	
	vector<int> los_elegidos;
	los_elegidos=numeros.out(tam);
	
	for(int i=0; i<tam; ++i){
		cout<<"El "<<i<<"º número elegido es: "<< los_elegidos[i]<<endl;
	}
	
	conseguir = 100 + rand() % 900; //Número entre 100 y 999.
	cout<<"El número que se quiere conseguir es "<<conseguir<<endl;
	
	cout<<"	Procesando...		"<<endl;
	numeros.search(conseguir,numeros);
	cout<<"	Fin del juego		"<<endl;
	
}
