//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// Don Oreo
//
//////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
   char tipo_cota_inf, coma_sep, tipo_cota_sup;
   int cota_inf,cota_sup;

   cout <<"Introduce un intervalo: ";
   cin >> tipo_cota_inf >> cota_inf >> coma_sep >> cota_sup >> tipo_cota_sup;

   cout << "\n" << tipo_cota_inf << cota_inf << coma_sep << cota_sup << tipo_cota_sup;

}
