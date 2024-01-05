#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int edad_persona;       //La edad de una persona no va a superar nunca un número como 2^32, así que un int o un short es suficiente

    long long pib_pais;     /*El PIB de un país si que puede superar el limite de 2^32,
                            por eso usamos el long long que llega hasta 2^64 sin perder precision como el double.*/

    bool primo;             //Para saber si es primo o no, usaremos un bool que nos dirá si lo es o no.

    string estado_civil;    //Para diferenciar y guardar correctamente variables de palabras, se usa string.

    bool sexo;              //Como son 2 opciones solo, se puede asignar un sexo a un estado. Ej. Hombre=1 y mujer=0.
}


