/**
* @file diccionario.cpp
* @author Yeray López Ramírez
* @author Jaime Castillo Ucles
* @date Diciembre 2021
*/

#include "diccionario.h"

using namespace std;

//Funcion auxiliar
void intercalado(int c, int intercalar){
    if(c % intercalar == 0)
        cout << endl;
}

Diccionario::Diccionario(const Diccionario &diccionario) {
    *this = diccionario;
}

size_t Diccionario::size() const {
    return datos.size();
}

bool Diccionario::Esta(const string & palabra) const {
    return datos.find( palabra) != datos.end();
}

vector<string> Diccionario::PalabrasLongitud(const size_t longitud) const{
    vector<string> resultado;

    for(auto palabra: datos)
        if(palabra.size() == longitud)
            resultado.push_back(palabra);

    return resultado;
}

void Diccionario::aniade(const string &nueva) {
    datos.insert( nueva);
}

Diccionario & Diccionario::operator= (const Diccionario &d) {
    datos = d.datos;
    return *this;
}

ostream & operator<< (ostream &os, const Diccionario &diccionario) {
    int c = 1;
    for(auto palabra: diccionario){
        os << left << setw(25) <<  to_string(c) + "-" + palabra;
        intercalado(c++,4);
    }
    cout << endl;

    return os;
}

istream &operator>> (istream &is, Diccionario &d) { //flujo de entrada(ej. cin)
    string palabra;

    is >> palabra;
    d.aniade(palabra);

    return is;
}



ifstream & operator>> (ifstream &in, Diccionario &d ) { //Archivo de flujo de entrada
    string entrada;

    while(getline(in, entrada))
        d.aniade(entrada);

    return in;
}
