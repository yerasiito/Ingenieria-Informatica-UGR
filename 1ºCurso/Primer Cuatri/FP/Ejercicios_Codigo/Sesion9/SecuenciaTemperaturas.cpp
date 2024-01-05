//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
///////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

int main(){
   const int MIN_TEMP = -90,MAX_TEMP = 60;
   double anterior,actual;
   int secuencia = 1;            //Se va a repetir al menos 1 vez
   double mayor_secuencia = 0;
   double pos_secuencia = 1;
   int pos_mayor_secuencia = 1;
   int contador = 1;             //Empezamos desde 1 para que sea "lógico" y no empezar desde el 0 como los vectores
   bool final_entrada_datos=false;

   cin >> anterior;
   final_entrada_datos=anterior < MIN_TEMP
                       ||
                       anterior > MAX_TEMP;

   while(!final_entrada_datos){
      cin >> actual;
      if(actual > anterior){
         secuencia++;
      }
      else if(secuencia > mayor_secuencia){
         mayor_secuencia = secuencia;
         pos_mayor_secuencia = pos_secuencia;
         pos_secuencia = contador +1;      //Contador +1 ya que contamos apartir del siguiente
         secuencia = 1;
      }
      if(actual < MIN_TEMP || actual > MAX_TEMP){
         if(secuencia > mayor_secuencia){
            mayor_secuencia = secuencia -1;   // -1 ya que no contamos al "terminador"
            pos_mayor_secuencia = pos_secuencia;
         }
         final_entrada_datos=true;
      }
         anterior = actual;
         contador++;
   }


   cout << "Inicio: " << pos_mayor_secuencia << " Longitud: " << mayor_secuencia << endl;

   return 0;

}


