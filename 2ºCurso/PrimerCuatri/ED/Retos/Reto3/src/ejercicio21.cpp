/**
* @file ejercicio21.cpp
* @brief Ejercicio 20 de la relacion del reto 3
* @author López Ramírez, Yeray
* @date 23 de Noviembre de 2021
*/

#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief El enunciado del problema a resolver, para tenerlo a la vista sin
 * tener que abrir el documento
 */
void enunciado(){
    cout << "\n********************************************************************************" << endl;
    cout << "Ejercicio 21:" << endl;
    cout << " Una matriz NxN de enteros se dice que está bi-ordenada si cada columna tiene " << endl
            << "los elementos ordenados de forma no decreciente de arriba abajo, y cada fila" << endl
            << "tiene los elementos también ordenados de forma no decreciente de izquierda a" << endl
            << "derecha. Ejemplo:" << endl
            << "    1   2   9" << endl
            << "    9   9   9" << endl
            << "    12  14  15" << endl
            << "(a) Implementar una función:" << endl
            << "    bool esmatrizbiordenada (vector<vector<int>> & M);" << endl
            << "que devuelva true si M es ua matriz bi-ordenada" << endl
            << "(b) Implementar de forma eficiente una función" << endl;
    cout << "********************************************************************************\n" << endl;
}

/**
 * @brief Pide los datos al usuario para crear la matriz a su antojo
 * @param M : queue La matriz a crear/inicializar por el usuario
 */
void introduce(vector<vector<int>> & M){
    cout << "Introduce los valores de la matriz: " << endl;
    int dato;
    for(int i = 0; i < M.size(); i++)
        for(int j=0; j < M.size(); j++)
            cin >>M[i][j];
}

/**
 * @brief Comprueba si la matriz pasada es bi-ordenada
 * Una matriz es bi-ordenada si sus elementos están ordenados crecientemente
 * por filas y columnas
 * @param M : vector<vector<int>> La matriz a comprobar
 * @return true si es bi-ordenada, false si no lo es
 */
bool esmatrizbiordenada(const vector<vector<int>> & M){
    bool isordenada = true;
    int anterior = M[0][0];
    
    //Recorre toda la matriz guardando el elemento anterior y comprobando que
    //siempre sea menor al actual(si es mayor, entonces devuelve false)
    for(int i = 0; i < M.size() && isordenada; i++)
        for(int j=0; j < M.size() && isordenada; j++){
            if(anterior > M[i][j])
                isordenada = false;
            anterior = M[i][j];
        }
            
    return isordenada;
}

/**
 * @brief Imprime la matriz
 * @param M : vector<vector<int>> La matriz a imprimir
 */
void imprimir(const vector<vector<int>> & M){
    cout << "La matriz contiene: " << endl;
    for(int i = 0; i < M.size(); i++){
        for(int j = 0; j < M.size(); j++)
            cout << M[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

/**
 * @brief Programa principal donde realizar las pruebas y probar los métodos
 * @return 0 si todo funciona bien, otro numero en caso de error
 */
int main (){
    enunciado();

    int dim;
    cout << "Introduce la dimension de la matriz(dim>0): ";
    cin >> dim;
    while(dim < 1) //La dimension no puede ser menor de 1
        cin >> dim;
    
    vector<vector<int>> M(dim,vector<int>(dim)); //crea una matriz con las dimensiones dadas

    introduce(M); //Pide datos al usuario
    
    if(esmatrizbiordenada(M))
        cout << "La matriz SI es biordenada" << endl;
    else
        cout << "La matriz NO es biordenada" << endl;
    //imprimir(M);
}
