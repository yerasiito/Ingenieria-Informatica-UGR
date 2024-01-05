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

using namespace std;

int main()
{
    // a)

    char tipo_radar;
    cin >> tipo_radar;
    if (tipo_radar == 'F' && tipo_radar == 'f')
    .....

    /* No se puede hacer igualdades con char de esa manera, es con un = solo.*/

    // b)

    double velocidad;
    cin >> velocidad;
    if (velocidad > 100 && velocidad < 70)
    cout << "\nVelocidad fuera del rango";

    /* El problema de este programa es que no existe una velocidad mayor a 100 y a la vez sea menor que 70
    en todo caso debe ser o uno u otro, usando "||".*/

    // c)

    double velocidad;
    cin >> velocidad;
    if (velocidad > 100 || velocidad > 110)
    cout << "Velocidad excesiva";

    /*Se repite código innecesariamente, lo correcto es poner "velocidad > 100" y yasta.*/
}


