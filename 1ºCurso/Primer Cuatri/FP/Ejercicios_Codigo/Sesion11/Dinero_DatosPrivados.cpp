//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

//Dinero Datos miembro Privados

#include <iostream>
using namespace std;

class Dinero{
private:
   int euros;
   int centimos;

public:
   void SetEurCent(int eurs,int cents){
      while(cents>=100){
         eurs++;
         cents-=100;
      }
      euros = eurs;
      centimos = cents;
   }

   int Euros(){
      return euros;
   }
   int Centimos(){
      return centimos;
   }

} ;

int main(){
   Dinero un_dinero;
   Dinero otro_dinero;
   Dinero dinero_total;

   int euros1,centimos1,
       euros2,centimos2;
   int eursuma,centsuma;
   cout << "Introduce el primer dinero: " << endl;
   cin >> euros1 >> centimos1;
   cout << "Introduce el segundo dinero: " << endl;
   cin >> euros2 >> centimos2;

   un_dinero.SetEurCent(euros1,centimos1);
   otro_dinero.SetEurCent(euros2,centimos2);

   euros1 = un_dinero.Euros();
   centimos1 = un_dinero.Centimos();
   euros2 = otro_dinero.Euros();
   centimos2 = otro_dinero.Centimos();

   eursuma = euros1 + euros2;
   centsuma = centimos1 + centimos2;

   dinero_total.SetEurCent(eursuma,centsuma);

   cout << "En el primer dinero hay " << un_dinero.Euros() << "," << un_dinero.Centimos() << " euros" << endl;
   cout << "En el segundo dinero hay " << otro_dinero.Euros() << "," << otro_dinero.Centimos() << " euros" << endl;
   cout << "La suma del dinero es: " << dinero_total.Euros() << "," << dinero_total.Centimos() << " euros" << endl;

}
