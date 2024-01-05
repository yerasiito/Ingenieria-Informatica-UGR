#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main()
{
    cout << "Este programa calcula el alcance de un proyectil: ";

    const long double PI = 3.1415;
    const long double g = 9.806;

    double vel_lanz, angulo;
    double tiempo_vuelo, h_max, alcance;

    cout << "\nIntroduzca velocidad de lanzamiento(m/s): ";
    cin >> vel_lanz;
    cout << "\nIntroduzca angulo de elevacion en grados (0-90): ";
    cin >> angulo;
    const double angulo_deg = angulo*PI/180;                //La funcion sin está en radianes, por lo que hay pasarla a grados.
    tiempo_vuelo = (2*vel_lanz*sin(angulo_deg))/g;

    h_max = ((vel_lanz*sin(angulo_deg))*(vel_lanz*sin(angulo_deg)))/(2*g);

    alcance = (vel_lanz*vel_lanz*sin(2*angulo_deg))/g;

     cout << "Tiempo de vuelo:" << tiempo_vuelo  << " s" << endl
          << "Altura maxima:" << h_max << " metros" << endl
          << "Alcance:" << alcance << " metros" << endl;

}


