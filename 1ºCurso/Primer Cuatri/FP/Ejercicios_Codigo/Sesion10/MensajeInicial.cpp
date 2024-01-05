//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

string LeeString(char terminador){
   string cadena;
   char car;

   car = cin.get();

   while (car != terminador){
      cadena.push_back(car);
      car = cin.get();
   }

   return cadena;
}

void ImprimeMarco (char car, int repeticiones){
   for(int i = 0; i < repeticiones; i++)
      cout << "*";

}

void Enmarca(string mensaje, char caracter){
   int util;
   string marco;

   util = mensaje.size();
   ImprimeMarco(caracter,util);
   cout << "\n" << mensaje << "\n";
   ImprimeMarco(caracter,util);

}
int main(){
   const char TERMINADOR = '@';
   char car;
   string msj;

   // Lectura

   cout << "Presentacion\n\n"
        << "Introduzca caracteres con terminador " << TERMINADOR << "\n";

   msj = LeeString(TERMINADOR);
   Enmarca(msj, car);

}
