#include <iostream>
using namespace std;

double h1, m1,s1;
double h2,m2,s2;
int main()
{
    cout << "Este programa calcula los segundos entre dos horas.\n\n";

    cout << "Introduce una hora(formato _h _m _s): ";
    cin >> h1 >> m1 >> s1;

    cout << "Introduce una hora distinta(formato _h _m _s): ";
    cin >> h2 >> m2 >> s2;

    cout << "Los segundos entre ambas horas son: " << abs(3600*(h1 - h2) + 60*(m1 - m2) + (s1 - s2));
}
