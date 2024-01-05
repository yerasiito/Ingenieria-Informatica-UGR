//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

//Interfaz Simulador Depósito

#include<iostream>
#include<cmath>
using namespace std;

class SimuladorDeposito{
private:
   double capital;
   double interes;
public:
   SimuladorDeposito()
   :capital(0),interes(0)
   {
   }
   void SetCapital(double capital_inicial){
      if(esPositivo)
         ....
   }
   void SetInteres(double I){
      if(esPositivo)
         ....
   }
   double Capital(){
      return capital;
   }
   int Interes(){
      return interes;
   }
   void CapitalFinal(int tope_anio){
      ....
   }

   void DoblarCapital(){
      ....

   }

};

int main(){
   SimuladorDeposito sueldo1;

   double capital_inicial;
   int interes;
   int anios_a_invertir;

   cout << "Introduce el capital y el interes: ";
   cin >> capital_inicial >> interes;

   sueldo1.SetCapital(capital_inicial);
   sueldo1.SetInteres(interes);

   cout << "Introduce los años a invertir: ";
   cin >> anios_a_invertir;

   sueldo1.CapitalFinal(anios_a_invertir);
   sueldo1.DoblarCapital();
}
