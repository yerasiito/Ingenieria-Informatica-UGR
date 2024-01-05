//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

/* Aprovechando el ejercicio 13 que ya hicimos, simplemente comprobamos si la diferencia es negativa
o no para saber cual va primero.

    cout << "Este programa calcula los segundos entre dos horas.\n\n";

    cout << "Introduce una hora(formato _h _m _s): ";
    cin >> h1 >> m1 >> s1;

    cout << "Introduce una hora distinta(formato _h _m _s): ";
    cin >> h2 >> m2 >> s2;

    diferencia=3600*(h1 - h2) + 60*(m1 - m2) + (s1 - s2);

    if(diferencia<0)
        cout << "\nEl primero SI es anterior." << endl;
    else
        cout << "\nEl primero NO es anterior." << endl;
*/

#include <iostream>
using namespace std;

int main()
{
    double h1, m1,s1;
    double h2,m2,s2;
    bool COMPARADOR;

    cout << "Este programa calcula los segundos entre dos horas.\n\n";

    cout << "Introduce una hora(formato _h _m _s): ";
    cin >> h1 >> m1 >> s1;
    cout << "Introduce una hora distinta(formato _h _m _s): ";
    cin >> h2 >> m2 >> s2;

    //Proceso...

    if(h1!=h2)
    {
        if(h1<h2)
            COMPARADOR=true;
        if(h1>h2)
            COMPARADOR=false;
    }
    else
        {
            if(m1!=m2)
            {
                if(m1<m2)
                    COMPARADOR=true;
                if(m1>m2)
                    COMPARADOR=false;
            }
            else
                {
                    if(s1!=s2)
                    {
                        if(s1<s2)
                            COMPARADOR=true;
                        if(s1>s2)
                            COMPARADOR=false;
                    }
                    else
                        COMPARADOR=false;
                }
        }


    //Salida de datos...

    if(COMPARADOR==true)
        cout << "\nEl primero SI es anterior." << endl;
    else
        cout << "\nEl primero NO es anterior." << endl;
}

