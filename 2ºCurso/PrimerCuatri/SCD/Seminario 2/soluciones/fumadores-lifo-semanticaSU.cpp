// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Seminario 2. Introducción a los monitores en C++11.
//
// archivo: fumadores-lifo-semanticaSU.cpp
// Ejemplo de un monitor en C++11 con semántica SU, para el problema
// de fumadores, con múltiples estanqueros y fumadores.
// Opcion LIFO (stack)
//
// -----------------------------------------------------------------------------


#include <iostream>
#include <iomanip>
#include <cassert>
#include <thread>
#include <mutex>
#include <random>
#include "scd.h"

using namespace std ;
using namespace scd ;

constexpr int
   num_ingredientes  = 40 ;     // número de ingredientes a producir/consumir

mutex
   mtx ;                 // mutex de escritura en pantalla
const int estanquero = 5, num_fumadores = 4; //Numero arbitrario de hebras
unsigned
   cont_prod[num_ingredientes], // contadores de verificación: producidos
   cont_cons[num_ingredientes], // contadores de verificación: consumidos
   cont_prod_hebra[estanquero];

//**********************************************************************
// funciones comunes a las dos soluciones (fifo y lifo)
//----------------------------------------------------------------------

int producir_ingrediente(int i)
{
   static int contador [estanquero] = {};

   if ( contador[i] == 0 && i != 0)
       contador[i] = num_ingredientes/estanquero * i;

   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));
   mtx.lock();
   cout << "Ingrediente: " << contador[i] << endl << flush ;
   mtx.unlock();
   cont_prod[contador[i]] ++ ;
   cont_prod_hebra[i]++;
   return contador[i]++ ;
}
//----------------------------------------------------------------------

void fumar( unsigned num_fumador )
{
   if ( num_ingredientes <= num_fumador )
   {
      cout << " Fumador " << num_fumador << " fuma " << num_ingredientes << endl ;
      assert( num_fumador < num_ingredientes );
   }
   cont_cons[num_fumador] ++ ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));
   mtx.lock();
   cout << "                  fuma: " << num_fumador << endl ;
   mtx.unlock();
}
//----------------------------------------------------------------------

void ini_contadores()
{
   for( unsigned i = 0 ; i < num_ingredientes ; i++ )
   {  cont_prod[i] = 0 ;
      cont_cons[i] = 0 ;
   }
}

//----------------------------------------------------------------------

void test_contadores()
{
   bool ok = true ;
   cout << "comprobando contadores ...." << flush ;

   for( unsigned i = 0 ; i < num_ingredientes ; i++ )
   {
      if ( cont_prod[i] != 1 )
      {
         cout << "error: valor " << i << " producido " << cont_prod[i] << " veces." << endl ;
         ok = false ;
      }
      if ( cont_cons[i] != 1 )
      {
         cout << "error: valor " << i << " consumido " << cont_cons[i] << " veces" << endl ;
         ok = false ;
      }
   }
   if (ok)
      cout << endl << flush << "solución (aparentemente) correcta." << endl << flush ;
}

// *****************************************************************************
// clase para monitor buffer, version LIFO, semántica SC, un prod. y un cons.

class ProdConsSU : public HoareMonitor
{
 private:
 static const int           // constantes:
	num_celdas_total = 10;   //  núm. de entradas del buffer
 int                        // variables permanentes
	buffer[num_celdas_total],//  buffer de tamaño fijo, con los datos
	primera_libre ;          //  indice de celda de la próxima inserción
 CondVar         // colas condicion:
   ocupadas,                //  cola donde espera el consumidor (n>0)
   libres ;                 //  cola donde espera el productor  (n<num_celdas_total)

 public:                    // constructor y métodos públicos
   ProdConsSU(  ) ;           // constructor
   int  leer();                // extraer un valor (sentencia L) (consumidor)
   void escribir( int valor ); // insertar un valor (sentencia E) (productor)
} ;
// -----------------------------------------------------------------------------

ProdConsSU::ProdConsSU(  )
{
	ocupadas = newCondVar();
	libres = newCondVar();
	primera_libre = 0 ;
}
// -----------------------------------------------------------------------------
// función llamada por el fumador para consumir un ingrediente

int ProdConsSU::leer(  )
{
   // esperar bloqueado hasta que 0 < num_celdas_ocupadas
   if (primera_libre == 0 )
      ocupadas.wait();

   // hacer la operación de lectura, actualizando estado del monitor
   assert( 0 < primera_libre  );
   primera_libre-- ;
   const int valor = buffer[primera_libre] ;


   // señalar al estanquero que la mesa esta vacia
   libres.signal();

   // devolver valor
   return valor ;
}
// -----------------------------------------------------------------------------

void ProdConsSU::escribir( int valor )
{
   // esperar bloqueado hasta que num_celdas_ocupadas < num_celdas_total
   if ( primera_libre == num_celdas_total )
      libres.wait();

   //cout << "escribir: ocup == " << num_celdas_ocupadas << ", total == " << num_celdas_total << endl ;
   assert( primera_libre < num_celdas_total );

   // hacer la operación de inserción, actualizando estado del monitor
   buffer[primera_libre] = valor ;
   primera_libre++ ;

   // señalar al fumador que el ingrediente esta en la mesa
   ocupadas.signal();
}
// *****************************************************************************
// funciones de hebras

void funcion_hebra_estanquero( MRef<ProdConsSU> monitor, int num_hebra )
{
    int aProducir = num_ingredientes/estanquero;
   for( unsigned i = num_hebra*aProducir; i < num_hebra*aProducir + aProducir ; i++ )
   {
      int valor = producir_ingrediente( num_hebra );
      monitor->escribir( valor );
   }
}
// -----------------------------------------------------------------------------

void funcion_hebra_fumador( MRef<ProdConsSU> monitor )
{
   for( unsigned i = 0 ; i < num_ingredientes/num_fumadores ; i++ )
   {
      int valor = monitor->leer();
      fumar( valor ) ;
   }
}
// -----------------------------------------------------------------------------

int main()
{
   cout << "-------------------------------------------------------------------------------------" << endl
        << "Problema fumadores (Varios estanq/fum, Monitor SU, buffer LIFO)." << endl
        << "-------------------------------------------------------------------------------------" << endl
        << flush ;

   MRef<ProdConsSU> monitor = Create<ProdConsSU>();

   thread hebra_productora[estanquero],
          hebra_consumidora[num_fumadores];

    for (int i=0; i<estanquero; i++)
        hebra_productora[i] = thread (funcion_hebra_estanquero, monitor, i);
    for (int i=0; i<num_fumadores; i++)
        hebra_consumidora[i] = thread (funcion_hebra_fumador, monitor);

    for (int i=0; i<estanquero; i++)
        hebra_productora[i].join() ;
    for (int i=0; i<num_fumadores; i++)
        hebra_consumidora[i].join() ;

   // comprobar que cada item se ha producido y consumido exactamente una vez
   test_contadores() ;
}
