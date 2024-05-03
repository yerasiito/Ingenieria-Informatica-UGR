#include "diccionario.h"

using namespace std;

/**
* @file testDiccionario.cpp
* @brief Archivo de prueba para el diccionario
* @author Yeray López Ramírez
* @author Jaime Castillo Ucles
* @date Diciembre 2021
*/
int main ( int argc, char * argv[] ){
    int c = 1;
    if ( argc != 2 ){
        cerr  << "Los parámetros son:" << endl
              << "\t1.- Fichero con las palabras";

        return 0;
    }

    ///////////////////////////////////////////////////////////////////////////////////
    //EXTRAER EL DICCIONARIO
    ///////////////////////////////////////////////////////////////////////////////////

    ifstream f(argv[1]);

    if(!f){
        cerr << "No se ha podido abrir el fichero " << argv[1] << endl;

        return 0;
    }

    Diccionario D;
    cout << "Cargando diccionario..." << endl;

    f >> D;

    cout << "leido el diccionario..." << endl;

    cout << D << endl;

    ///////////////////////////////////////////////////////////////////////////////////
    //BUSCAR PALABRAS CON X LONGITUD
    ///////////////////////////////////////////////////////////////////////////////////

    int longitud;

    cout << "Dime la longitud de las palabras que quieres ver: ";

    //La longitud no puede ser menor o igual a 0, filtro de entrada
    do
        cin >> longitud;
    while (longitud <= 0);

    vector<string> v = D.PalabrasLongitud(longitud);

    cout << "Hay " << v.size() << " Palabras de Longitud " << longitud << endl;

    for(unsigned int i=0; i < v.size(); i++){
        cout << left << setw(20) << to_string(c) + "-" + v[i];
        intercalado(c++,5);
    }
    c=1;

    ///////////////////////////////////////////////////////////////////////////////////
    //COMPRUEBA PALABRAS
    ///////////////////////////////////////////////////////////////////////////////////

    string p;

    cout << "\nDime una palabra: ";
    cin >> p;

    if ( D.Esta(p) )
        cout << "Sí esa palabra existe\n" << endl;
    else
        cout << "Esa palabra no existe\n" << endl;

    ///////////////////////////////////////////////////////////////////////////////////
    //PROBAR CLASE ITERADORA
    ///////////////////////////////////////////////////////////////////////////////////

    cout << "Probando clase iteradora:" << endl;
    Diccionario::iterator it;
    for(it = D.begin(); it != D.end(); ++it){
        cout << left << setw(25) << to_string(c) + "-" + (*it);
        intercalado(c++,4);
    }
    cout << endl;

    return 0;
}
