#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int a,b;
    bool div;

    cout << "Este programa comprueba si cualquiera de los dos numeros son divisibles\n\n";
    cout << "Introduce dos numeros: ";
    cin >> a >> b;

    div = a%b==0 || b%a==0;

    if(div)
    {
     cout << "Los numeros son divisibles.";
    }
    else
        cout << "No son divisibles.";
}


