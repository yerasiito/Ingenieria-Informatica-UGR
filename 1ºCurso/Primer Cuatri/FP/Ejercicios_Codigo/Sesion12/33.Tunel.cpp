//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// Autor: Don Oreo
//
//////////////////////////////////////////////////////////////////////////

// Túnel

#include <iostream>
#include <cmath>
#include "IV_FormateadorDoubles.cpp"
#include "IV_Instante.cpp"

using namespace std;


/*
Túnel en un momento dado:

matr:     ["4733MTI"  ,  "5232LTL"  , "3330PRB" ,   ?  , ... ,  ?  ]
seg_ent:  [    13     ,     79      ,    160    ,   ?  , ... ,  ?  ]
seg_sal:  [    96     ,    NULO     ,    NULO   , NULO , ... , NULO]

tot = 3
*/

class Tunel{
private:
   double distancia_km;

   static const int MAX_NUM_VEHICULOS = 100;
   string matriculas[MAX_NUM_VEHICULOS];
   int entradas[MAX_NUM_VEHICULOS];
   int salidas[MAX_NUM_VEHICULOS];
   int total_entradas = 0;

   static const int INSTANTE_NULO = -1;

public:
   Tunel(double long_tunel)
   :distancia_km(long_tunel)
   {
      for(int i = 0; i < MAX_NUM_VEHICULOS; i++)
         salidas[i] = -1;
   }

   string Matriculas(int posicion){
      return matriculas[posicion];
   }

   int Entradas(int posicion){
      return entradas[posicion];
   }

   int Salidas(int posicion){
      return salidas[posicion];
   }

   double Longitud(){
      return distancia_km;
   }

   int TotalEntradas(){
      return total_entradas;
   }

   void Entra(string matricula, int hora, int minuto, int segundo){
      int pos = -1;
      Instante inst_entrada(hora,minuto,segundo);
      int seg_totales = inst_entrada.SegundosTotales();

      for(int i = 0; i < total_entradas; i++)
         if(matricula == matriculas[i])
            pos = i;
      if(pos == -1){
         matriculas[total_entradas] = {matricula};
         entradas[total_entradas] = seg_totales;
         total_entradas++;
      }
      else{
         entradas[pos] = seg_totales;
         salidas[pos] = INSTANTE_NULO;
      }
   }

   void Sale(string matricula, int hora, int minuto, int segundo){
      int pos = -1;
      Instante inst_salida(hora,minuto,segundo);
      int seg_totales = inst_salida.SegundosTotales();

      for(int i = 0; i < total_entradas; i++)
         if(matricula == matriculas[i])
            pos = i;

      if(pos != -1)
         salidas[pos] = seg_totales;

   }

   bool HaSalido(int pos){
      bool ha_salido = true;

      if(Salidas(pos) == -1)
         ha_salido = false;

      return ha_salido;
   }

   double Velocidad(int pos){
      double velocidad;
      double diferencia_hora = (Salidas(pos) - Entradas(pos))/3600.0;

      velocidad = Redondea(distancia_km/diferencia_hora,1);

      return velocidad;
   }

};


int main(){
   const char FIN_ENTRADA = '#';
   const char ENTRADA = 'E';
   const char SALIDA  = 'S';
   char acceso;
   bool error_lectura;

   string matricula;
   string cadena;
   double long_tunel;
   int hora, min, seg;

   cin >> long_tunel;
   Tunel tunel(long_tunel);

   //Escribe E para entrada, S para salida y # para terminar la lectura
   cin >> acceso;
   error_lectura = false;

   while (acceso != FIN_ENTRADA && !error_lectura){
      cin >> matricula;
      cin >> hora >> min >> seg;

      if (acceso == ENTRADA)
         tunel.Entra(matricula,hora,min,seg);
      else if (acceso == SALIDA)
         tunel.Sale(matricula,hora,min,seg);
      else
         error_lectura = true;

      cin >> acceso;
   }

   //-------------------------------------------------------------

   FormateadorDoubles format_veloc(""," km/h", 1);
   if (error_lectura)
      cout << "\nSe produjo un error en la lectura. " << endl;
   else{
      int total_entradas = tunel.TotalEntradas();
      for (int i = 0; i < total_entradas; i++){
         cadena += "\n\nMatricula:\t" + tunel.Matriculas(i) +
         "\nVelocidad:\t";

         if(!tunel.HaSalido(i))
            cadena += "No ha salido";
         else
            cadena += format_veloc.GetCadena(tunel.Velocidad(i));
      }
   }

   cout << cadena << endl;
}

   // longitud_túnel  <entrada_o_salida  Matrícula# Instante> ... #

// Entrada:
/*
3.4
E 4733MTI 0 0 13
E 5232LTL 0 1 19
S 4733MTI 0 1 36
E 3330PRB 0 2 40
S 5232LTL 0 3 25
#
*/

// Salida:
/*
Matrícula:      4733MTI
Velocidad:      147.5 km/h

Matrícula:      5232LTL
Velocidad:      97.1 km/h

Matrícula:      3330PRB
Velocidad:      No ha salido
*/


//////////////////////////////////////////////////////////////////

// Entrada:
/*
   3.4
E 4733MTI 0 0 13
E 1976KEX 0 0 34
E 7717UQS 0 0 47
E 4744SEU 0 0 56
E 5232LTL 0 1 19
S 4733MTI 0 1 36
E 6188MOH 0 1 36
E 6603JHQ 0 2 4
E 6898DVW 0 2 17
E 3330PRB 0 2 40
S 1976KEX 0 2 53
E 1758HRV 0 2 56
E 8210YVI 0 3 9
S 5232LTL 0 3 25
S 6603JHQ 0 3 25
S 7717UQS 0 3 29
S 6188MOH 0 3 29
E 9265JJA 0 3 35
S 4744SEU 0 3 40
E 4864DUN 0 3 49
S 3330PRB 0 3 51
E 1071VVF 0 3 54
S 1758HRV 0 4 30
E 5917FBY 0 4 43
   */

   // Salida:
   /*
   Matrícula:	4733MTI
Velocidad:	147.5 km/h

Matrícula:	1976KEX
Velocidad:	88.1 km/h

Matrícula:	7717UQS
Velocidad:	75.6 km/h

Matrícula:	4744SEU
Velocidad:	74.6 km/h

Matrícula:	5232LTL
Velocidad:	97.1 km/h

Matrícula:	6188MOH
Velocidad:	108.3 km/h

Matrícula:	6603JHQ
Velocidad:	151.1 km/h

Matrícula:	6898DVW
Velocidad:	No ha salido

Matrícula:	3330PRB
Velocidad:	172.4 km/h

Matrícula:	1758HRV
Velocidad:	130.2 km/h

Matrícula:	8210YVI
Velocidad:	No ha salido

Matrícula:	9265JJA
Velocidad:	No ha salido

Matrícula:	4864DUN
Velocidad:	No ha salido

Matrícula:	1071VVF
Velocidad:	No ha salido

Matrícula:	5917FBY
Velocidad:	No ha salido
   */

