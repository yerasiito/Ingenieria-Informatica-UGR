#include <iostream>
using namespace std;

double metros;                              //variable de entrada
double pulgada, pie, yarda,milla,m_marina;  //variables de salida

int main()
{
    cout <<"Este programa convierte metros en pulgadas, pies, yardas y millas.\n";

    cout <<"Introduce la distancia en metros: ";
    cin >> metros;

    pulgada = metros/0.0254;                //Conversión metros a pulgadas
    pie = metros/0.3048;                    //Conversión metros a pies
    yarda = metros/0.9144;                  //Conversión metros a yardas
    milla = metros/1609.344;                //Conversión metros a millas
    m_marina = metros/1852;                 //Conversión metros a millas náuticas


    cout << "\nLa distancia en pulgadas es: " << pulgada;
    cout << "\nLa distancia en pies es: " << pie;
    cout << "\nLa distancia en yardas es: " << yarda;
    cout << "\nLa distancia en millas es: " << milla;
    cout << "\nLa distancia en millas náuticas es: " << m_marina;
}

