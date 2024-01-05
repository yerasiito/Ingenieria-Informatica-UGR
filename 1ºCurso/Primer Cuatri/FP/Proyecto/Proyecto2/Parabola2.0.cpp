//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main()
{
   const long double PI = 3.1415;
   const long double g = 9.806;

   int n, x0, y0, vel, elev, rot;                           //valores de entrada
   double tiempo_vuelo, h_max, alcance, xf, yf;             //valores de calculo y salida

   cout << "Este programa calcula el alcance de un proyectil: " << endl;

//Entrada de datos...
   cout << "Introduce las coordenadas del canion(x0,y0): ";
   cin >> x0 >> y0;
   cout << "Introduce la velocidad de lanzamiento: ";
   cin >> vel;                                              //Expresado en m/s
   if(vel<0){
      cout << "Error: La elevacion debe ser positiva";
      exit(-1);
   }
   cout << "Introduce la elevacion del canion: ";
   cin >> elev;                                             //Expresado en grados
   if(elev>=90){
      cout << "Error: La elevacion debe estar entre 0-90 grados";
      exit(-1);
   }
   cout << "Introduce la rotacion del canion: ";
   cin >> rot;                                              //Angulo 0 (en grados) es igual al Norte(Eje Y)
   if(rot>180 || rot<-180){
      n=rot/180;                                            //truncamiento de decimales por ser variable entera
      rot = rot - 360*n;
      cout << "El angulo de rotacion rectificado es: " << rot << endl;
   }

   const double elev_deg =elev*PI/180;                      //La funcion sin está en radianes, por lo que hay pasarla a grados.
   const double rot_deg = rot*PI/180;                       //***

//Cálculos...
   tiempo_vuelo = (2*vel*sin(elev_deg))/g;
   h_max = ((vel*sin(elev_deg))*(vel*sin(elev_deg)))/(2*g);
   alcance = (vel*vel*sin(2*elev_deg))/g;                   //Se repite vel a proposito para no tener que usar pow(más tiempo de calculo)
   xf = x0 + alcance*sin(rot_deg);
   yf = y0 + alcance*cos(rot_deg);

//Salida de datos...

   cout << "----------Resultado de Disparo----------"
        << "\nTiempo de vuelo:" << tiempo_vuelo  << " s" << endl
        << "Altura maxima:" << h_max << " metros" << endl
        << "Alcance:" << alcance << " metros" << endl
        << "Impacto:" << xf <<"," << yf << " metros" << endl;

//------------------------Exito de Disparo------------------------------------------------------------------

//Entrada de datos...

   cout << "----------Comprobacion de Objetivo----------";

   double x, y, d, d0, d1;

   cout << "\nIntroduzca la posicion del objetivo(x,y): ";
   cin >> x >> y;
   cout << "Introduzca distancias de impacto(dos valores): ";
   cin >> d0 >> d1;
   if(d0<0 || d1<0){
      cout << "Error: Las distancias de impacto no deben ser negativas";
      exit(-1);
   }

//calculo de datos...

   d = sqrt((x-xf)*(x-xf) + (y-yf)*(y-yf));             //Se repiten expresiones a proposito para no tener que usar pow(más tiempo de calculo)

//Salida de datos...

   cout << "La distancia al objetivo es: " << d;
   if(d<d0 && d<d1)
      cout << "---->Impacto Directo";
   else if(d>d0 && d>d1)
      cout << "---->No hay Impacto";
   else
      cout << "---->Impacto Parcial";
   return 0;
}
