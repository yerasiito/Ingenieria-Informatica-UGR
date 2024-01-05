//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

//Cuadrado

#include <iostream>
using namespace std;

class Cuadrado{
private:
   double x,y;
   double lado;
public:
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
   Cuadrado una_parcela;
   Cuadrado otra_parcela;

   double esquina_x1, esquina_y1, lado1,
       esquina_x2, esquina_y2, lado2;

   cout << "Introduce las coordenadas de la esquina inferior izquierda del cuadrado 1 y su lado: " << endl;
   cin >> esquina_x1 >> esquina_y1 >> lado1;

   una_parcela.SetCoordenadasLado(esquina_x1, esquina_y1, lado1);

   cout << "Introduce las coordenadas de la esquina inferior izquierda del cuadrado 2 y su lado: " << endl;
   cin >> esquina_x2 >> esquina_y2 >> lado2;

   otra_parcela.SetCoordenadasLado(esquina_x2, esquina_y2, lado2);

   cout << "Coordenadas: " << una_parcela.Coord_x() << " , " << una_parcela.Coord_y() << endl;
   cout << "Longitud: " << una_parcela.Lado() << endl;
   cout << "Area: " << una_parcela.Area() << endl;
   cout << "Perimetro " << una_parcela.Perimetro() << endl;
   cout << "Coordenadas: " << otra_parcela.Coord_x() << " , " << una_parcela.Coord_y() << endl;
   cout << "Longitud: " << otra_parcela.Lado() << endl;
   cout << "Area: " << otra_parcela.Area() << endl;
   cout << "Perimetro: " << otra_parcela.Perimetro() << endl;



}
