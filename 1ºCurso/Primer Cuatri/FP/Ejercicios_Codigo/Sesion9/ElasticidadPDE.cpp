//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

// Elasticidad Precio-Demanda


#include <iostream>
#include <cmath>
using namespace std;

double Variacion_porcentual(double valor_ini,double valor_fin){
   double resultado;
   resultado = abs(100*((valor_ini - valor_fin)/valor_ini));
   return resultado;
}

double Elasticidad(double precio_ini,double precio_fin, double demanda_ini,double demanda_fin){
   double vp_demanda, vp_precio, elasticidad;
   vp_precio = Variacion_porcentual(precio_ini,precio_fin);
   vp_demanda = Variacion_porcentual(demanda_ini,demanda_fin);
   elasticidad = vp_demanda / vp_precio;
   return elasticidad;
}
//////////////////////////////////////////////////////////////


int main(){
   double precio_ini, precio_fin;
   double demanda_ini, demanda_fin;
   double elast_pd;

   cout << "Cálculo de la Elasticidad Precio-Demanda.\n\n"
        << "Introduzca cuaternas de valores:"
        << "El precio inicial, el precio final, la demanda inicial y la demanda final.\n"
        << "Introduzca cualquier negativo en el precio inicial para terminar\n\n";

   cin >> precio_ini;

   while (precio_ini >= 0){
      cin >> precio_fin;
      cin >> demanda_ini;
      cin >> demanda_fin;

      elast_pd = Elasticidad(precio_ini,precio_fin,demanda_ini,demanda_fin);

      cout << "Elasticidad Precio-Demanda: " << elast_pd << "\n";
      cin >> precio_ini;
   }
}
