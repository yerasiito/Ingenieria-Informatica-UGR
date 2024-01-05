//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// Departamento de Ciencias de la Computación e Inteligencia Artificial
// Autor: Don Oreo
//
//////////////////////////////////////////////////////////////////////////

// Elimina Ultimos

#include <iostream>
#include <string>

using namespace std;

string LeeString(char terminador){
   string cadena;
   char caracter;

   caracter = cin.get();

   while (caracter != terminador){
      cadena.push_back(caracter);
      caracter = cin.get();
   }

   return cadena;
}

string EliminaUltimo(string cadena, char a_borrar){
   int ultimo;

   ultimo = cadena.size() - 1;
   while(cadena[ultimo] == a_borrar){
      cadena.erase(ultimo);
      ultimo = cadena.size() - 1;
   }
   return cadena;
}

/* Metodo 2
string EliminaUltimo(string cadena,char a_borrar){
   while( cadena.back() == a_borrar)
      cadena.pop_back();
   return cadena;
}
*/
int main(){
   const char TERMINADOR = '#';
   char a_borrar;
   string cadena;

   // Lectura

   cout << "Lee string\n\n"
        << "Introduzca caracteres con terminador " << TERMINADOR
        << ". Y despues escribe el caracter ultimo a borrar." << endl;

   cadena = LeeString(TERMINADOR);

   a_borrar = cin.get();

   cadena = EliminaUltimo(cadena,a_borrar);

   cout << cadena;
}
