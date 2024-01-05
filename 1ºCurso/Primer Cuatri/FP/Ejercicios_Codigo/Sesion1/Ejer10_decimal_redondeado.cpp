#include <iostream>
#include <cmath>

using namespace std;

double numero ;
double cifra ;

int main()
{

    cout <<"\nEscribe el numero que quiere redondear y la cifra decimal:" ;
    cin >> numero >> cifra ;
    numero= round(numero * pow(10, cifra));
    numero = numero/ pow (10, cifra);
    cout << "\nEl numero aproximado es: " << numero ;
}
//Este codigo no compila en codeblocks pero si en dev c++, no entiendo muy bien por qué.
