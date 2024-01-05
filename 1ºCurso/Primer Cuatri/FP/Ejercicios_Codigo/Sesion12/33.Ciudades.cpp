//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// Autor: Don Oreo
//
//////////////////////////////////////////////////////////////////////////

// Mapa de distancias entre ciudades

#include <iostream>
#include <cmath>
using namespace std;



// -----------------------------------------------------------------------
class MapaDistancias{
private:
    static const int NUM_MAX_CIUDADES = 50;
    static const int DISTANCIA_NULA = 0;
    double mat_dist[NUM_MAX_CIUDADES][NUM_MAX_CIUDADES];
    int  num_ciudades;

    bool EsCorrectaDistancia(double distancia){
       return distancia > DISTANCIA_NULA;
    }

    bool EsCorrectoIndice(int indice){
      return 0 <= indice && indice < num_ciudades;
    }

    bool EsCorrectaPosicion(int origen, int destino){
       return  EsCorrectoIndice(origen) && EsCorrectoIndice(destino);
    }

public:
   MapaDistancias (int numero_ciudades)
      : num_ciudades(numero_ciudades)
   {
         for(int i = 0; i < NUM_MAX_CIUDADES; i++){
            for( int j = 0; j < NUM_MAX_CIUDADES; j++)
               mat_dist[i][j] = DISTANCIA_NULA;
         }
   }

   int Capacidad(){
      return NUM_MAX_CIUDADES;
   }

   int NumCiudades(){
      return num_ciudades;
   }
   double DistanciaCiudad(int pos_i, int pos_j){
      return mat_dist[pos_i][pos_j];
   }

   void ModificaDistancia(int una, int otra, double distancia){
      if (EsCorrectaDistancia(distancia) && EsCorrectaPosicion(una, otra)){
         mat_dist[una][otra] = mat_dist[otra][una] = distancia;
      }
   }

   int CiudadMejorConectada(){
      int indice_mas_conectada = -1;
      int max_conex = -1, num_conex;

      for (int origen = 0; origen < num_ciudades; origen++){
         num_conex = 0;

         for (int destino = 0; destino < num_ciudades; destino++)
            if (mat_dist[origen][destino] != 0)
               num_conex++;

         if (num_conex > max_conex){
            max_conex = num_conex;
            indice_mas_conectada = origen;
         }
      }

      return indice_mas_conectada;
   }

   int MejorEscalaEntre (int origen, int destino){
      int escala_de_min_distancia = -1;
      double distancia_con_escala;
      double min_distancia = INFINITY;

      for (int escala = 0; escala < num_ciudades; escala++){
         distancia_con_escala = 0;

         if (mat_dist[origen][escala] != 0 && mat_dist[escala][destino] != 0)
            distancia_con_escala = mat_dist[origen][escala] +
                                   mat_dist[escala][destino];

         if (distancia_con_escala != 0){
            if (distancia_con_escala < min_distancia){
               escala_de_min_distancia = escala;
               min_distancia = distancia_con_escala;
            }
         }
      }

      return escala_de_min_distancia;
   }

   string ToString() {
      string cadena;

      for (int i = 0; i < num_ciudades; i++){
         for (int j = 0; j < num_ciudades; j++){
            cadena.append(to_string(mat_dist[i][j]));
            cadena.append("\t");
         }
         cadena.append("\n");
      }
      return cadena;
   }
};



// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
int main (){
   int ciudad_mas_conectada;
   int origen, destino, escala;
   int num_ciudades;
   const int TERMINADOR_CIUDADES = -1;

   cout << "Mapa de distancias"
        << "\n\nIntroduzca los datos en el siguiente orden:"
        << "\na) Número de ciudades"
        << "\nb) Distancias entre ellas en forma de matriz diagonal superior"
        << "\n   Lista de índices de ciudades para las que se quiere ver "
        << "\n   si están todas conectadas entre sí. Terminador: "
        << TERMINADOR_CIUDADES
        << "\n"
        << "\n   Ciudad de origen y ciudad de destino."
        << "\n\n";

   cin >> num_ciudades;

   MapaDistancias mapa(num_ciudades);

   for (int i = 0; i < num_ciudades - 1; i++){
      for (int j = i+1; j < num_ciudades; j++){
         double distancia;

         cin >> distancia;
         mapa.ModificaDistancia(i, j, distancia);
      }
   }

   /*for(int i = 0; i < num_ciudades; i++){
      cout << "\n";
      for( int j = 0; j < num_ciudades; j++)
         cout << mapa.DistanciaCiudad(i,j) << "\t";
   }*/

   cin >> origen >> destino;

   //-----------------------------------------------------------
   // Ciudad mejor conectada (con mayor número de conexiones directas)
   ciudad_mas_conectada = mapa.CiudadMejorConectada();

   cout << "La ciudad con más conexiones directas es la ciudad: "
        << ciudad_mas_conectada;


   //-----------------------------------------------------------
   // Mejor escala entre origen y destino
   escala = mapa.MejorEscalaEntre(origen,destino);

   if (escala == -1)
      cout << "No existe escala" << endl;
   else
      cout << "\nLa mejor escala entre " << origen << " y "
           << destino << " es " << escala << endl;
   return 0;
}

/*
Entrada:

   5
   50  100   0    150
       70    0    0
             60   80
                  90
   0  4

Salida:

   La ciudad con más conexiones directas es la ciudad: 2
   La mejor escala entre 0 y 4 es 2
*/
