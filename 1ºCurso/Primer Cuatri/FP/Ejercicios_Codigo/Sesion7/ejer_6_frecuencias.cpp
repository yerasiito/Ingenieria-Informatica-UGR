//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// Departamento de Ciencias de la Computación e Inteligencia Artificial
// Autor: Don Oreo
//
//////////////////////////////////////////////////////////////////////////

// Frecuencias
 /*
   Algoritmo:

      Recorrer -i- el vector texto
         actual = texto[i]

         Si actual no está en el vector procesados:
            - Añadir actual a procesados
            - Contar el número de ocurrencias de actual
              en el vector texto -a partir de la posición i+1-
   */
#include <iostream>
using namespace std;

int main(){
   const char TERMINADOR = '@';
   const int NUM_CARACT_ASCII = 256;
   const int MAX_NUM_CARACT = 1e4;  // diez mil

   char a_buscar[NUM_CARACT_ASCII];
   int frecuencias[NUM_CARACT_ASCII] {};
   char texto[MAX_NUM_CARACT];
   int contador;
   char car;
   int util_a_buscar, util_texto;

   cout << "Frecuencias\n"
        << "Introduzca los caracteres del vector a buscar, con terminador "
        << TERMINADOR << "\n"
        << "A continuación introduzca  los caracteres del texto,"
        << " usando el mismo terminador.\n\n";

   // Introduccion de Datos

   car = cin.get();
   util_a_buscar = 0;

   while (car != TERMINADOR && util_a_buscar < NUM_CARACT_ASCII){
      a_buscar[util_a_buscar] = car;
      car = cin.get();
      util_a_buscar++;
   }

   car = cin.get();
   util_texto = 0;

   while (car != TERMINADOR && util_texto < MAX_NUM_CARACT){
      texto[util_texto] = car;
      car = cin.get();
      util_texto++;
   }


   //Computo de Datos

   /*//Metodo 1:
   for(int i=0;i<NUM_CARACT_ASCII;i++){
         car=i;
         for(int j=0;j<util_texto;j++)
            if(car==texto[j])
               frecuencias[i]++;
   }

   //Salida de Datos

   for(int j=0;j<util_a_buscar;j++)
      for(int i=0;i<NUM_CARACT_ASCII;i++)
         if(a_buscar[j]==i)
            cout << i << " : " << frecuencias[i] << endl;

   */
   //Metodo 2:

   for(int j=0;j<util_a_buscar;j++)
         for(int i=0;i<util_texto;i++)
            if(a_buscar[j]==texto[i])
               frecuencias[j]++;

   //Salida de Datos

   for(int j=0;j<util_a_buscar;j++)
      cout << j << " : " << frecuencias[j] << endl;

   /*
   Ja@Juan Carlos Cubero@º

   J: 1
   a: 2
   */
}


