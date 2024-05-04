#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random>
#include "scd.h"

using namespace std ;
using namespace scd ;

//**********************************************************************
// Variables globales

const unsigned 
   num_items = 40 ,   // número de items
	tam_vec   = 10 ;   // tamaño del buffer
unsigned  
   cont_prod[num_items] = {0}, // contadores de verificación: para cada dato, número de veces que se ha producido.
   cont_cons[num_items] = {0}, // contadores de verificación: para cada dato, número de veces que se ha consumido.
   siguiente_dato       = 0 ;  // siguiente dato a producir en 'producir_dato' (solo se usa ahí)
   
int
   vec[tam_vec];
   
//variables de la implementación fifo
int 
    pos_lectura=0,
	pos_escritura=0;
    mutex SALIDA;   //mutex para los cout para que no se lanzen concurrentemente
    Semaphore puede_escribir=tam_vec, puede_leer=0;

//**********************************************************************
// funciones comunes a las dos soluciones
//----------------------------------------------------------------------

unsigned producir_dato()
{
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));
   const unsigned dato_producido = siguiente_dato ;
   siguiente_dato++ ;
   cont_prod[dato_producido] ++ ;
   cout << "producido: " << dato_producido << endl << flush ;
   return dato_producido ;
}
//----------------------------------------------------------------------

void consumir_dato( unsigned dato )
{
   assert( dato < num_items );
   cont_cons[dato] ++ ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));

   cout << "                  consumido: " << dato << endl ;

}

//Nota: no es necesario proteger la concurrencia con mutex(cerrojos) porque pos_lectura y pos_escritura son diferentes contadores y por tanto no hay fallo posible.
//Otro caso sería si hubiera varios productores y varios consumidores, ahí si sería necesario proteger con cerrojos ya que podrian darse interferencias entre el código de un contador lanzado en 
//concurrencia con sí mismo.

void  funcion_hebra_productora(  )
{
   for( unsigned i = 0 ; i < num_items ; i++ )
   {
   	//solución fifo
      int dato = producir_dato() ;
      sem_wait(puede_escribir);
      		vec[pos_escritura]=dato;
      		pos_escritura=(pos_escritura+1)%tam_vec;
      sem_signal(puede_leer);
     
   }
}

//----------------------------------------------------------------------

void funcion_hebra_consumidora(  )
{
   for( unsigned i = 0 ; i < num_items ; i++ )
   {	//solucion fifo
      int dato;
      sem_wait(puede_leer);
      		dato=vec[pos_lectura];
      		pos_lectura=(pos_lectura+1)%tam_vec;
      sem_signal(puede_escribir);
      consumir_dato( dato );
    }
}
//----------------------------------------------------------------------


void test_contadores()
{
   bool ok = true ;
   cout << "comprobando contadores ...." ;
   for( unsigned i = 0 ; i < num_items ; i++ )
   {  if ( cont_prod[i] != 1 )
      {  cout << "error: valor " << i << " producido " << cont_prod[i] << " veces." << endl ;
         ok = false ;
      }
      if ( cont_cons[i] != 1 )
      {  cout << "error: valor " << i << " consumido " << cont_cons[i] << " veces" << endl ;
         ok = false ;
      }
   }
   if (ok)
      cout << endl << flush << "solución (aparentemente) correcta." << endl << flush ;
}



int main()
{
SALIDA.lock();
   cout << "-----------------------------------------------------------------" << endl
        << "Problema de los productores-consumidores solución FIFO." << endl
        << "------------------------------------------------------------------" << endl
        << flush ;
SALIDA.unlock();

   thread hebra_productora ( funcion_hebra_productora ),
          hebra_consumidora( funcion_hebra_consumidora );

   hebra_productora.join() ;
   hebra_consumidora.join() ;

   test_contadores();
}
