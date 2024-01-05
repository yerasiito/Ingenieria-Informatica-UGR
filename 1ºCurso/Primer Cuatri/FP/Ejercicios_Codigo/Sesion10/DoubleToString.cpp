//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

//DoubleToString

#include <iostream>
#include <cmath>
using namespace std;

string EliminaUltimo(string cadena){
   int ultimo;
   ultimo = cadena.size() - 1;
   while(cadena[ultimo] == '0' || cadena[ultimo] == '.'){
      cadena.erase(ultimo);
      ultimo = cadena.size() - 1;
   }
   return cadena;
}

double Redondeado(double real, int decimales){
   real = round(real * pow(10,decimales));
   real = real / pow(10,decimales);

   return real;
}
string DoubleToString(double real, int decimales){
   string cadena;
   real = Redondeado(real,decimales);
   cadena = to_string(real);
   cadena = EliminaUltimo(cadena);
   return cadena;
}

int main(){
   const char TERMINADOR = '#';
   double real;
   int decimales;
   string cadena;

   cout << "Convertir a string\n\n"
        << "Introduzca el real a convertir con las decimaless a redondear" << TERMINADOR << endl;

   cin >> real >> decimales;

   cadena = DoubleToString(real,decimales);

   cout << cadena << endl;
}

