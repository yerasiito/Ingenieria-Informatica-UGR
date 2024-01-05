//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cmath>

using namespace std;

int main(){

   int dorsal;
   int hora,minutos;
   char DOS_PUNTOS;
   const int TERMINADOR=0;
   int ganador,hora_ganador,minutos_ganador;
   int participantes=0;

   /*la variables ganador guarda el dorsal del ganador
     las variables hora_ganador y minutos_ganador guarda el tiempo(seria más facil con un vector...)
   */

   cout << "Introduce el dorsal del corredor(termine con el dorsal 0 o menor): ";
   cin >> dorsal;

   /*El programa terminará cuando el dorsal sea menor o igual al terminador */
   while(dorsal>TERMINADOR){
      participantes++;
      cout << "Introduce el tiempo del corredor: ";
      cin >> hora >> DOS_PUNTOS >> minutos;

   /*si la hora es menor a la ganadora, automaticamente se convierte en el nuevo ganador
     si la hora es igual, compara los minutos*/

      if(hora < hora_ganador || (hora==hora_ganador && minutos<minutos_ganador)){
         ganador = dorsal;
         hora_ganador = hora;
         minutos_ganador = minutos;
      }
      cout << "Introduce otro dorsal(termine con el dorsal 0 o menor): ";
      cin >> dorsal;
   }

   if(participantes>0){
      cout << "-----------------------------------------";
      cout << "\nEl ganador tiene el dorsal: " << ganador
           << " con un tiempo de: " << hora_ganador << DOS_PUNTOS << minutos_ganador
           << "\nEl numero de participantes es: " << participantes << endl;
   }
   else
      cout << "No hay ganador.";
}


