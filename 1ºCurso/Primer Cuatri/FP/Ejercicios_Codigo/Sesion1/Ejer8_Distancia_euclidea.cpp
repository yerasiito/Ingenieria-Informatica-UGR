#include <iostream>

double x1,x2;           //Coordenadas de P1.
double y1,y2;           //Coordenadas de P2.

int main()
{
    cout << "Este programa calcula la distancia entre dos puntos dados.\n\n";

    cout << " Coordanada x del P1: ";
    cin >> x1;
    cout << " Coordanada y del P1: ";
    cin >> y1;

    cout << "\n Coordanada x del P2: ";
    cin >> x2;
    cout << " Coordanada y del P2: ";
    cin >> y2;

    cout << "\n    -La distancia euclidea entre ambos puntos es de " << sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1)) << "\n";
}
