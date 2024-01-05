//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

//Dinero Datos miembro Publicos

#include <iostream>
using namespace std;

class Dinero{
public:
   int euros;
   int centimos;

   void SetEurCent(int eurs,int cents){
      while(cents>=100){
         eurs++;
         cents-=100;
      }
      euros = eurs;
      centimos = cents;
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

   eursuma = un_dinero.euros + otro_dinero.euros;
   centsuma = un_dinero.centimos + otro_dinero.centimos;

   dinero_total.SetEurCent(eursuma,centsuma);

   cout << "En el primer dinero hay " << un_dinero.euros << "," << un_dinero.centimos << " euros" << endl;
   cout << "En el segundo dinero hay " << otro_dinero.euros << "," << otro_dinero.centimos << " euros" << endl;
   cout << "La suma del dinero es: " << dinero_total.euros << "," << dinero_total.centimos << " euros" << endl;

}
