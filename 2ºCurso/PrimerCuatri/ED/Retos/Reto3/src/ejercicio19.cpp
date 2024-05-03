/**
* @file ejercicio19.cpp
* @brief Ejercicio 19 de la relacion del reto 3
* @author López Ramírez, Yeray
* @date 22 de Noviembre de 2021
*/

#include <cstdlib>
#include <iostream>
#include <stack>
using namespace std;

/**
 * @brief El enunciado del problema a resolver, para tenerlo a la vista sin
 * tener que abrir el documento
 */
void enunciado(){
    cout << "\n********************************************************************************" << endl;
    cout << "Ejercicio 19:" << endl;
    cout << "Dada una pila P de enteros implementar una función " << endl
    << "    void transformarpila(stack<int> & p);" << endl
    << "que transforme una pila p en otra en la que los elementos aparezcan en el mismo " << endl
    << "orden original y habiendo sido eliminados los elementos que siendo consecutivos" << endl
    << "aparezcan repetidos. Ejemplo: P =<1,1,2,3,3,4,5,5,1,1,9,8,7,7,3> pasaría a quedar" << endl
    << "como P = <1,2,3,4,5,1,9,8,7,3>" << endl;
    cout << "********************************************************************************\n" << endl;
}

/**
 * @brief Pide los datos al usuario para crear la lista a su antojo
 * @param p : stack La pila a crear/inicializar por el usuario
 */
void introduce(stack<int> & p){
    int a;
    cout << "Introduce los valores de C:(0 para terminar) " << endl;
    cin >> a;
    while(a != 0){
        p.push(a);
        cin >> a;
    }
}

/**
 * @brief Elimina los elementos repetidos de la pila pasada como parametro
 * @param p : stack Pila a limpiar de elementos repetidos
 */
void transformarpila(stack<int> & p){
    stack<int> aux;
    int elem_anterior;
    
    //Guarda el elemento anterior, y si coincide con el actual, no lo mete en la Pila aux
    while(!p.empty()){
        if(elem_anterior != p.top())
            aux.push(p.top());
        elem_anterior = p.top();
        p.pop();
    }
    //Devolvemos los elementos sin repetir a la pila original
    p = aux;
}

/**
 * @brief Imprime la pila sin destruir la original
 * @param p : stack La pila a imprimir
 */
void imprimir(const stack<int> & p){
    stack<int> aux = p;
    cout << "La cola contiene: ";
    while(!aux.empty()){
        cout << " " << aux.top();
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
    stack<int> p;

    introduce(p);
    transformarpila(p);
    imprimir(p);
}
