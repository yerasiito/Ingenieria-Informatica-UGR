//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////


// Sustituir carácter por vector
#include <iostream>
using namespace std;


int main(){
   const char TERMINADOR = '#';
   const int MAX_NUM_CARACT = 3e6;  // Compile con la opción -Wl,--stack,21000000
   char v[MAX_NUM_CARACT],
        nuevo[MAX_NUM_CARACT];
   char a_borrar;
   char car;
   int i, util_v, util_nuevo;

   // Lectura

   car = cin.get();
   i = 0;

   while (car != TERMINADOR){
      v[i] = car;
      car = cin.get();
      i++;
   }

   util_v = i;

   car = cin.get();
   i = 0;

   while (car != TERMINADOR){
      nuevo[i] = car;
      car = cin.get();
      i++;
   }

   util_nuevo = i-1;

   a_borrar = cin.get();


   //////////////////////////////////////////////////////////
   int contador=0;

   /*Contamos el numero de ocurrencias a borrar*/
   for(int i=0; i<util_v;i++){
      if(v[i]==a_borrar){
         contador++;
      }
   }

   int util_resultado=util_v;
   util_resultado+=contador*util_nuevo;      //Obtenemos el util final

   /*Inicializamos las variables de lectura/escritura*/
   int lec=util_v;
   int esc=util_resultado;

   /** Comprueba si los caracteres de v coinciden con a_borrar
   *si coinciden, imprime el vector nuevo de derecha a izquierda
   *si no coincide, imprime el caracter de v a la izquierda del caracter de más a la derecha
   */
   //Nota:Los vectores leen de derecha a izquierda

   while(lec>=0){
      if(v[lec]==a_borrar){
         for(int j=util_nuevo; j>=0; j--){
            v[esc]=nuevo[j];
            esc--;
         }
      }
      else{
         v[esc]=v[lec];
         esc--;
      }
      lec--;
   }
   //////////////////////////////////////////////////////////

   cout << "<";

   for (int i = 0; i < util_resultado; i++)
      cout << v[i] ;

   cout << ">";

// Ejemplo de entrada:
// unoadosaa#TTU#a

// Salida:
// unoTTUdosTTUTTU
}
