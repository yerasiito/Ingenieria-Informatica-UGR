//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

int main(){
   /*
   Esquema alumnos:

      Filtro para la distancia d (debe ser d >= 0):

      do{
         cin >> d;
      }while (d < 0);

      Filtro para el número de ptos n:

      do{
         cin >> n;
      }while (n < MIN  ||  MAX < n);
   */

   const int    LIM_KMS_RECARGO = 300;
   const double RECARGO_KM = 0.1;
   const double MIN_KMS_DSCTO = 700.0;
   const int    MIN_PTOS_DSCTO_BAJO = 100;
   const int    MIN_PTOS_DSCTO_ALTO = 200;
   const int    DSCTO_KMS = 2;
   const int    DSCTO_BAJO_PTOS = 3;
   const int    DSCTO_ALTO_PTOS = 4;
   const double TRF_BASE = 150.0;
   const int    MAX_NUM_PTOS = 400;
   const int    MIN_NUM_PTOS = 0;
   const char NUEVO_BILLETE='N';
   const char TERMINADOR='#';

   double dscto;
   double trf = 0;
   int dist;
   int ptos_fideliz;
   char billete;

   //Damos por hecho que minimo vas a comprar 1 billete

   cout << "Tarifa aerea."
        << "\nIntroduzca 'N' para un nuevo billete o '#' para finalizar la compra:" << endl;

   while(billete!=NUEVO_BILLETE && billete!=TERMINADOR)
      cin >> billete;

   while(billete!=TERMINADOR){

      cout << "\nIntroduzca la distancia del recorrido del viaje (> 0) y el "
           << "número de puntos de la tarjeta de fidelización (entre 0 y "
           << MAX_NUM_PTOS << ":\n";

      do{
         cin >> dist;
      }while (dist < 0);

      do{
         cin >> ptos_fideliz;
      }while (ptos_fideliz < MIN_NUM_PTOS
              ||
              MAX_NUM_PTOS < ptos_fideliz);


   /*
   Algoritmo:
      Inicializar la tarifa a la tarifa base

      Según sea la longitud del trayecto
         Actualizar la tarifa

      Según sea la longitud del trayecto
         Inicializar el dscto

      Según sea el número de puntos
         Actualizar el dscto

      Aplicar el dscto calculado anteriormente a la tarifa
   */


      trf = TRF_BASE;

      if (dist > LIM_KMS_RECARGO)
         trf = trf + RECARGO_KM*(dist - LIM_KMS_RECARGO) ;


      if (dist > MIN_KMS_DSCTO)
         dscto = DSCTO_KMS;
      else
         dscto = 0;

      if (ptos_fideliz > MIN_PTOS_DSCTO_ALTO)
         dscto = dscto + DSCTO_ALTO_PTOS;
      else if (ptos_fideliz > MIN_PTOS_DSCTO_BAJO)
         dscto = dscto + DSCTO_BAJO_PTOS;

      trf = trf * (1 - dscto / 100.0);

      cout << "\n\nTarifa final aplicando los dsctos: ";
      cout << trf;

      billete=0;
      cout <<"\n----------------------------------------------------" << endl;
      cout << "\nIntroduzca 'N' para un nuevo billete o '#' para finalizar la compra:" << endl;
      while(billete!=NUEVO_BILLETE && billete!=TERMINADOR){
         cin >> billete;
      }
   }
}
