#include <iostream>
#include <cassert>
#include <stdlib.h>
#include <thread>
#include <mutex>
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include "scd.h"

using namespace std ;
using namespace scd ;

// numero de fumadores 

vector<Semaphore> s;
Semaphore mostr_vacio=1;

//-------------------------------------------------------------------------
// Función que simula la acción de producir un ingrediente, como un retardo
// aleatorio de la hebra (devuelve número de ingrediente producido)

int producir_ingrediente( int num_fumadores )
{
   // calcular milisegundos aleatorios de duración de la acción de fumar)
   chrono::milliseconds duracion_produ( rand() % num_fumadores);

   // informa de que comienza a producir
   cout << "Estanquero : empieza a producir ingrediente (" << duracion_produ.count() << " milisegundos)" << endl;

   // espera bloqueada un tiempo igual a ''duracion_produ' milisegundos
   this_thread::sleep_for( duracion_produ );

    int num_ingrediente = rand()% num_fumadores ;

   // informa de que ha terminado de producir
   cout << "Estanquero : termina de producir ingrediente " << num_ingrediente << endl;

   return num_ingrediente ;
}

//----------------------------------------------------------------------
// función que ejecuta la hebra del estanquero

void funcion_hebra_estanquero( int num_fumadores )
{
	while(true){
		int j;
		j=producir_ingrediente(num_fumadores);
		sem_wait(mostr_vacio);
		//Poner producto en el mostrador
		cout << "Ponerlo en  mostrador" <<j<<endl;
		//Espera recogida de ingrediente
		sem_signal(s[j]);
	}

}

//-------------------------------------------------------------------------
// Función que simula la acción de fumar, como un retardo aleatoria de la hebra

void fumar( int num_fumador )
{

   // calcular milisegundos aleatorios de duración de la acción de fumar)
   chrono::milliseconds duracion_fumar( aleatorio<20,200>() );

   // informa de que comienza a fumar

    cout << "Fumador " << num_fumador << "  :"
          << " empieza a fumar (" << duracion_fumar.count() << " milisegundos)" << endl;

   // espera bloqueada un tiempo igual a ''duracion_fumar' milisegundos
   this_thread::sleep_for( duracion_fumar );

   // informa de que ha terminado de fumar

    cout << "Fumador " << num_fumador << "  : termina de fumar, comienza espera de ingrediente." << endl;

}

//----------------------------------------------------------------------
// función que ejecuta la hebra del fumador
void  funcion_hebra_fumador( int num_fumador )
{
   while( true )
   {
    //Esperar hasta que ingrediente i esté en mostrador
    sem_wait(s[num_fumador]);
    cout<<"Retirado ingrediente" <<num_fumador<<endl;
    //Recogerlo y avisar al estanquero
    sem_signal(mostr_vacio);
    fumar(num_fumador);

   }
}

//----------------------------------------------------------------------

int main()
{
   // declarar hebras y ponerlas en marcha
   // ......
   int num_fumadores;
   cout<<"¿Cuantos fumadores hay?"<<endl;
   cin>>num_fumadores;
   for(int i=0; i<num_fumadores; i++){
	s.push_back(Semaphore(0));
   }
   thread hebra_estanquero(funcion_hebra_estanquero, num_fumadores);
   thread hebra_fumador[num_fumadores];
   
   for (int i=0; i<num_fumadores; i++){
   	hebra_fumador[i]=thread (funcion_hebra_fumador, i);
   }
   hebra_estanquero.join();
   for(int i=0; i<num_fumadores; i++)
   	hebra_fumador[i].join();
}
