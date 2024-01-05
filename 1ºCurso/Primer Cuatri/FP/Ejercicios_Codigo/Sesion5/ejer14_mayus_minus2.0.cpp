#include <iostream>
#include <cmath>
using namespace std;

int main() {

   enum class tipo
   {mayuscula, minuscula, otro};

   char letra_introducida;
   char letra_convertida;
   const int DISTANCIA_MAY_MIN = 'a'-'A';
   tipo caracter;

//Entrada de Datos...

   cout << "\nIntroduzca una letra --->";
   cin >> letra_introducida;

//Calculo de Datos...

   if ((letra_introducida >= 'A') && (letra_introducida <= 'Z')){
      letra_convertida = letra_introducida + DISTANCIA_MAY_MIN;
      caracter = tipo::mayuscula;
   }
   else if ((letra_introducida >= 'a') && (letra_introducida <= 'z')){
      letra_convertida = letra_introducida - DISTANCIA_MAY_MIN;
      caracter = tipo::minuscula;
   }
   else
      caracter = tipo::otro;

//Salida de Datos...

   if(caracter == tipo::mayuscula)
      cout << "La letra convertida es: " << letra_convertida;
   else if(caracter == tipo::minuscula)
      cout << "La letra convertida es: " << letra_convertida;
   else
            cout << "El caracter no era una letra";
   return 0;
}
