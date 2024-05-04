// -----------------------------------------------------------------------------
// Sistemas concurrentes y Distribuidos.
// Seminario 2. Introducción a los monitores en C++11.
//
// Productor/Consumidor múltiples (prodcons_fifo_sc.cpp)
// Ejemplo de un monitor en C++11 con semántica SC, para el problema
// de fumadores, con múltiples estanqueros y fumadores.
// Precondición: estanquero y fumadores divisores de num_ingredientes
// Opcion FIFO (queue)
//
// Don Oreo
// -----------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <cassert>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <random>

using namespace std;

constexpr int
   num_ingredientes  = 40 ;     // número de ingredientes a producir/consumir

mutex mtx ;                 // mutex de escritura en pantalla
const int estanquero = 5, num_fumadores = 4; //Numero arbitrario de hebras
unsigned
   cont_prod[num_ingredientes], // contadores de verificación: producidos
   cont_cons[num_ingredientes], // contadores de verificación: consumidos
   cont_prod_hebra[estanquero];
// indica para cada hebra productora cuantos ingredientes ha producido
unsigned producidos[estanquero] = {0};
// indica para cada hebra consumidora cuantos ingredientes ha consumido
unsigned consumidos[num_fumadores] = {0};

//**********************************************************************
// plantilla de función para generar un entero aleatorio uniformemente
// distribuido entre dos valores enteros, ambos incluidos
// (ambos tienen que ser dos constantes, conocidas en tiempo de compilación)
//----------------------------------------------------------------------

template< int min, int max > int aleatorio(){
  static default_random_engine generador( (random_device())() );
  static uniform_int_distribution<int> distribucion_uniforme(min, max);
  return distribucion_uniforme(generador);
}

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

void ini_contadores(){
   for(unsigned i = 0 ; i < num_ingredientes ; i++){
      cont_prod[i] = 0 ;
      cont_cons[i] = 0 ;
   }
}

void test_contadores(){
   bool ok = true;
   cout << "comprobando contadores ...." << flush;

   for(unsigned i = 0 ; i < num_ingredientes ; i++){
      if (cont_prod[i] != 1){
         cout << "error: valor " << i << " producido " << cont_prod[i] 
              << " veces." << endl;
         ok = false;
      }
      if (cont_cons[i] != 1){
         cout << "error: valor " << i << " consumido " << cont_cons[i] 
         << " veces" << endl;
         ok = false;
      }
   }

   if (ok)
      cout << endl << flush << "solución (aparentemente) correcta." << endl << flush;
}

// *****************************************************************************
// clase para monitor buffer, version FIFO, semántica SC, un estanq. y un fum.

class ProdConsSC{
private:
   // constantes
 static const int           // constantes:
	num_celdas_total = 10;   //  núm. de entradas del buffer
 int                        // variables permanentes
	buffer[num_celdas_total],//  buffer de tamaño fijo, con los datos
	primera_libre,
    primera_ocupada,         // indice de celda de la próxima extracción
    num_celdas_ocupadas;          // indica el número de celdas ocupadas
   mutex cerrojo_monitor;        // cerrojo del monitor
   // colas condicion
   condition_variable ocupadas;  // cola donde espera el consumidor (n>0)
   condition_variable libres;    // cola donde espera el productor (n<num_celdas_total)

public:                    
   // constructor y métodos públicos
   ProdConsSC();             // constructor
   int leer();                // extraer un valor (sentencia L) (consumidor)
   void escribir(int valor);  // insertar un valor (sentencia E) (productor)
};

ProdConsSC::ProdConsSC(){
   primera_libre = 0;
   primera_ocupada = 0;
   num_celdas_ocupadas = 0;
}

// -----------------------------------------------------------------------------
// función llamada por el consumidor para extraer un dato

int ProdConsSC::leer(){
   // ganar la exclusión mutua del monitor con una guarda
   unique_lock<mutex> guarda(cerrojo_monitor);

   // esperar bloqueado hasta que 0 < num_celdas_ocupadas
   while (num_celdas_ocupadas == 0){
      ocupadas.wait(guarda);
   }

   // hacer la operación de lectura, actualizando estado del monitor
   assert(0 < num_celdas_ocupadas);
   if (primera_ocupada == num_celdas_total)
      primera_ocupada = 0;
   const int valor = buffer[primera_ocupada];
   primera_ocupada++;
   num_celdas_ocupadas--;

   // señalar al productor que hay un hueco libre, por si está esperando
   libres.notify_one();

   // devolver valor
   return valor;
}

void ProdConsSC::escribir(int valor){
   // ganar la exclusión mutua del monitor con una guarda
   unique_lock<mutex> guarda(cerrojo_monitor);

   // esperar bloqueado hasta que num_celdas_ocupadas < num_celdas_total
   while (num_celdas_ocupadas == num_celdas_total){
      libres.wait(guarda);
   }

   //cout << "escribir: ocup == " << num_celdas_ocupadas << ", total == " << num_celdas_total << endl ;
   assert(num_celdas_ocupadas < num_celdas_total);

   // hacer la operación de inserción, actualizando estado del monitor
   if (primera_libre == num_celdas_total)
      primera_libre = 0;
   buffer[primera_libre] = valor;
   primera_libre++;
   num_celdas_ocupadas++;

   // señalar al consumidor que ya hay una celda ocupada (por si esta esperando)
   ocupadas.notify_one();
}

// *****************************************************************************
// funciones de hebras

void funcion_hebra_estanquera(ProdConsSC * monitor, int num_hebra){
   for(unsigned i = 0 ; i < num_ingredientes/estanquero ; i++){
      int valor = producir_ingrediente(num_hebra);
      monitor->escribir(valor);
   }
}

void funcion_hebra_fumadora(ProdConsSC * monitor, int num_hebra){
   for(unsigned i = 0 ; i < num_ingredientes/num_fumadores ; i++){
      int valor = monitor->leer();
      fumar(valor);
   }
}

int main(){
   cout << "-------------------------------------------------------------------------------" << endl
        << "Problema fumadores (Múltiples estanq/fum, Monitor SC, buffer FIFO). " << endl
        << "-------------------------------------------------------------------------------" << endl
        << flush;

   ini_contadores();
   ProdConsSC monitor;

   thread estanquera[estanquero];
   thread fumadora[num_fumadores];
   for (int i = 0 ; i < estanquero ; i++)
      estanquera[i] = thread(funcion_hebra_estanquera, &monitor, i);
   for (int i = 0 ; i < num_fumadores ; i++)
      fumadora[i] = thread(funcion_hebra_fumadora, &monitor, i);

   for (int i = 0 ; i < estanquero ; i++)
      estanquera[i].join();
   for (int i = 0 ; i < num_fumadores ; i++)
      fumadora[i].join();

   // comprobar que cada item se ha producido y consumido exactamente una vez
   test_contadores() ;
}
