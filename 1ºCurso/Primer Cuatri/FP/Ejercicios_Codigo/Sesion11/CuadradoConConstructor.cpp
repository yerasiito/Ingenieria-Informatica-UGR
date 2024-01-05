//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

//Cuadrado con constructor

#include <iostream>
#include <cmath>
using namespace std;

class Cuadrado{
private:
   double x,y;
   double lado;
public:
   Cuadrado(double coord_x, double coord_y, double longitud){
      if(longitud > 0){
         x = coord_x;
         y = coord_y;
         lado = longitud;
      }
      else{
         x = NAN;
         y = NAN;
         lado = -1;
      }
   }

   void SetCoordenadasLado(double coord_x, double coord_y, double longitud){
      x = coord_x;
      y = coord_y;
      lado = longitud;
   }

   double Coord_x(){
      return x;

   }
   double Coord_y(){
      return y;
   }

   double Lado(){
      return lado;
   }

   double Area(){
      return lado*lado;
   }

   double Perimetro(){
      return 4*lado;
   }

};

int main(){

   const string MSJ_COORDENADAS = "\nCoordenadas: ";
   const string MSJ_LONGITUD = "\nLongitud: ";
   const string MSJ_AREA = "\nÁrea: ";
   const string MSJ_PERIMETRO = "\nPerímetro: ";
   const string MSJ_PARCELA = "\nParcela ";
   double esquina_x1, esquina_y1, lado1,
       esquina_x2, esquina_y2, lado2;

   cout << "Introduce las coordenadas de la esquina inferior izquierda del cuadrado 1 y su lado: " << endl;
   cin >> esquina_x1
       >> esquina_y1
       >> lado1;

   Cuadrado una_parcela(esquina_x1, esquina_y1, lado1);

   cout << "Introduce las coordenadas de la esquina inferior izquierda del cuadrado 2 y su lado: " << endl;
   cin >> esquina_x2
       >> esquina_y2
       >> lado2;

   Cuadrado otra_parcela(esquina_x2, esquina_y2, lado2);

   cout << MSJ_PARCELA << "1";
   cout << MSJ_COORDENADAS << una_parcela.Coord_x() << " , " << una_parcela.Coord_y();
   cout << MSJ_LONGITUD << una_parcela.Lado();
   cout << MSJ_AREA << una_parcela.Area();
   cout << MSJ_PERIMETRO << una_parcela.Perimetro() << endl;

   cout << MSJ_PARCELA << "2";
   cout << MSJ_COORDENADAS << otra_parcela.Coord_x() << " , " << otra_parcela.Coord_y();
   cout << MSJ_LONGITUD << otra_parcela.Lado();
   cout << MSJ_AREA << otra_parcela.Area();
   cout << MSJ_PERIMETRO << otra_parcela.Perimetro() << endl;


   return 0;
}
/*
3.4  5.7  2.9
-5.6 -4.1 1.8
*/
/*
Coordenadas: 3.4 , 5.7
Longitud: 2.9
Área: 8.41
Perímetro: 11.6

Coordenadas: -5.6 -4.1
Longitud: 1.8
Área: 3.24
Perímetro: 7.2
*/

