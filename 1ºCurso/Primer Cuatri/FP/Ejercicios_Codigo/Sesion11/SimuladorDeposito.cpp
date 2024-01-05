//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

//Simulador Depósito

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
      if(capital_inicial >= 0)
         capital = capital_inicial;
   }
   void SetInteres(double I){
      if(I >= 0)
         interes = I;
   }
   double Capital(){
      return capital;
   }
   int Interes(){
      return interes;
   }
   void CapitalFinal(int tope_anio){
      double elev;
      double int_compuesto;
      for(int anios = 0; anios < tope_anio;anios++){
         elev = pow((1 + interes/100),anios+1);
         int_compuesto = capital*elev;
         cout << "Capital obtenido transcurrido el anio numero " << anios
              << " = " << int_compuesto << endl;
      }

   }

   void DoblarCapital(){
      double tope_cap = 2*capital;
      int anios;

      while(capital<=tope_cap){
         capital = capital + capital*(interes/100);
         anios++;
      }

   cout << "\nPara doblar la cantidad inicial han de pasar " << anios << " anios" << endl;
   cout << "Al finalizar, se obtendra un total de " << capital << " euros" << endl;

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
