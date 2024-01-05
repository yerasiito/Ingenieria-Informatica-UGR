//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

//FormateadoDoubles

#include<iostream>
using namespace std;

double Redondea(double real, int num_decimales){
...
}

string EliminaUltimos(string cadena, char ultimo_car){
...
}

class FormateadorDoubles(){
private:
   string izda = "";
   string dcha = "";
   int decimales = 2;
   enum class SeparadorDecimal {PUNTO, COMA};
   SeparadorDecimal separador = SeparadorDecimal::COMA;
public:
   FormateadorDoubles()
   {
   }
   FormateadorDoubles(string delim_izda,delim_dcha)
   {
   }
   void Izda(){
      return izda;
   }

   void Dcha(){
      return dcha;
   }
   int SetDecimales(int num_decimales){
      decimales = num_decimales;
   }
   void SetSeparadorPunto(){
      separador = SeparadorDecimal::PUNTO;
   }
   string GetCadena(double real){
      ... Redondea, EliminaUltimos, etc
   }

};

int main(){
double num;

cout << "Introduce un numero: ";
cin >> num;
format_real(); //o format_real("<",">")

format_real.GetCadena();

}

