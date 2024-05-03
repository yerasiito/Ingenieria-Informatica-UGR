/**
* @file ejercicio24.cpp
* @brief Ejercicio 20 de la relacion del reto 3
* @author López Ramírez, Yeray
* @date 23 de Noviembre de 2021
*/

#include <cstdlib>
#include <iostream>
#include <list>
#include <assert.h>

using namespace std;

/**
 * @brief El enunciado del problema a resolver, para tenerlo a la vista sin
 * tener que abrir el documento
 */
void enunciado(){
    cout << "\n********************************************************************************" << endl;
    cout << "Ejercicio 24:" << endl;
    cout << "Implementar una función " << endl
            << "    void postintercalar(list<int> & L1, list<int> & L2);" << endl
            << "que permita 'postintercalar' dos listas de enteros (intercalar alternativamente" << endl
            << "todos los elementos que las integran de final a principio), con los siguientes" << endl
            << "requisitos:" << endl
            << "(a) Hay que comprobar que las dos listas L1 y L2 no son vacías" << endl
            << "(b) Se empieza por el primer elemento de la primera lista L1" << endl
            << "(c) La segunda lista L2 contendrá el resultado final y la primera quedará vacía." << endl
            << "(d) Si una de ellas tiene un menor número de elementos que la otra, el exceso de" << endl
            << "nodos se incorporará a la lista resultante." << endl
            << "Ejemplo:" << endl
            << "Primera lista, L1 : (100,200); Segunda lista. L2: (1,2,3,4,5,6)" << endl
            << "Despues de aplicar la función:" << endl
            << "L2: (1,2,3,4,200,5,100,6); L1: vacia" << endl;
    cout << "********************************************************************************\n" << endl;
}

/**
 * @brief Pide los datos al usuario para crear las listas a su antojo
 * @param L1 : list
 * @param L2 : lsit
 */
void introduce(list<int> & L1, list<int> & L2){
    int dato;

    cout << "Introduce los valores de la primera lista:(0 para terminar) " << endl;
    cin >> dato;
    while(dato != 0){
        L1.push_front(dato);
        cin >> dato;
    }

    cout << "Introduce los valores de la segunda lista:(0 para terminar) " << endl;
    cin >> dato;
    while(dato != 0){
        L2.push_front(dato);
        cin >> dato;
    }
}

/**
 * @brief Intercala las listas segun el enunciado
 * @param L1 : list Lista a vaciar en el intercalado
 * @param L2 : lsit Lista a rellenar intercaladamente con L1
 */
void posintercalar(list<int> & L1, list<int> & L2){
    list<int>::iterator it;

    //Que no esten vacias
    assert(!L1.empty());
    assert(!L2.empty());

    //movemos el iterator una posicion despues del inicio de la lista
    it = L2.begin();
    it++;
    
    for(;!L1.empty() && L2.front() != *it; ++it){ //se sale si L1 vacia o L2 vuelve al frente
        L2.insert(it,L1.back());
        L1.pop_back();
    }

    if(*it == L2.front()){ //Si L2 ha llegado al final, mete el resto de L1 al principio(izquierda)
        it = L2.end();
        while(!L1.empty()){
            L2.insert(it,L1.back());
            L1.pop_back();
        }
    }
}

/**
 * @brief Imprime las listas sin destruir las originales
 * @param L1 : list
 * @param L2 : list
 */
void imprimir(const list<int> & L1, const list<int> & L2){
    list<int> aux1 = L1, aux2 = L2;
    cout << "\nL1 contiene:";
    while(!aux1.empty()){
        cout << " " << aux1.back();
        aux1.pop_back();
    }

    cout << "\nL2 contiene:";
    while(!aux2.empty()){
        cout << " " << aux2.back();
        aux2.pop_back();
    }
    cout << endl;
}

/**
 * @brief Programa principal donde realizar las pruebas y probar los métodos
 * @return 0 si todo funciona bien, otro numero en caso de error
 */
int main (){
    enunciado();
    list<int> L1, L2;

    introduce(L1,L2);
    cout << endl << "Antes de postintercalar";
    imprimir(L1, L2);
    posintercalar(L1,L2);
    cout << endl << "Despues de postintercalar";
    imprimir(L1, L2);


  return 0;
}
