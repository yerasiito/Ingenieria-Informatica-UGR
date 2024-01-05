#include <iostream>
#include <cmath>
using namespace std;

int main(){

    char letra;

    cout << "\nIntroduzca una letra a continuacion:";
    cin >> letra;

    if('A' <= letra && letra <= 'Z')
    {
    cout << "\nLa entrada es mayuscula";
    letra = letra + 32;
    }
    else
    {
    cout <<"\nLa entrada es minuscula";
    letra = letra - 32;
    }
    cout << "\nEl resultado es: " << letra;
}

