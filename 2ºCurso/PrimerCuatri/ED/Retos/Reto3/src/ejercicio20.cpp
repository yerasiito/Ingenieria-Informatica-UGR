/**
* @file ejercicio20.cpp
* @brief Ejercicio 20 de la relacion del reto 3
* @author López Ramírez, Yeray
* @date 23 de Noviembre de 2021
*/

#include <cstdlib>
#include <iostream>
#include <queue>
using namespace std;

/**
 * @brief El enunciado del problema a resolver, para tenerlo a la vista sin
 * tener que abrir el documento
 */
void enunciado(){
    cout << "\n********************************************************************************" << endl;
    cout << "Ejercicio 20:" << endl;
    cout << "Implementar una función" << endl
    << "void rotación(queue<int> & C);" << endl
    << "que saque una cierta cantidad de enteros del frente de la cola C y los vuelve a" << endl
    << "insertar al final de cola, de forma que quede en el frente el primer número par" << endl
    << "que haya en la cola. Por ejemplo, si" << endl
    << "C={1,3,5,2,4} ====>  C={2,4,1,3,5}" << endl;

    cout << "********************************************************************************\n" << endl;
}

/**
 * @brief Pide los datos al usuario para crear la cola a su antojo
 * @param C : queue La cola a crear/inicializar por el usuario
 */
void introduce(queue<int> & C){
    int a;
    cout << "Introduce los valores de C:(0 para terminar) " << endl;
    cin >> a;
    while(a != 0){
        C.push(a);
        cin >> a;
    }
}

/**
 * @brief Busca un elemento PAR en la cola y mueve todos los elementos a su izquierda
 * al final(a la derecha)
 * @param C : queue La cola a rotar
 */
void rotacion(queue<int> & C){
    queue<int> aux;
    
    //Mete todos los elementos en una cola auxiliar hasta encontrar uno PAR
    while(C.front() % 2 != 0 ){
        aux.push(C.front());
        C.pop();
    }

    //Mete los elementos de aux al final de la cola original, moviendo los elementos que queriamos
    while(!aux.empty()){
        C.push(aux.front());
        aux.pop();
    }
}

/**
 * @brief Imprime la cola sin destruir la original
 * @param C : queue La cola a imprimir
 */
void imprimir(const queue<int> & C){
    queue<int> aux = C;
    cout << "La cola contiene: ";
    while(!aux.empty()){
        cout << " " << aux.front();
        aux.pop();
    }
    cout << endl;
}

/**
 * @brief Programa principal donde realizar las pruebas y probar los métodos
 * @return 0 si todo funciona bien, otro numero en caso de error
 */
int main (){
    enunciado();
    queue<int> C;

    introduce(C);
    rotacion(C); //rotamos
    cout << "Tras rotar la cola..." << endl;
    imprimir(C);
}
