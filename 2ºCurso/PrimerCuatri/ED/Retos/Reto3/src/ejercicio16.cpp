/**
  * @file ejercicio16.cpp
  * @brief Ejercicio 16 de la relacion del reto 3
  * @author López Ramírez, Yeray
  * @date 21 de Noviembre de 2021
  */

#include <iostream>
#include <stack>

using namespace std;

/**
 * @brief El enunciado del problema a resolver, para tenerlo a la vista sin
 * tener que abrir el documento
 */
void enunciado(){
    cout << "\n**************************************************************************" << endl;
    cout << "Ejercicio 16:" << endl;
    cout << "Implementa las funciones de insertar y borrar elementos del TDA list<int> " << endl
    << "a partir de las funciones del TDA stack <int>" << endl;
    cout << "**************************************************************************\n" << endl;
}

/**
 * @brief MyPilaLista
 * Una clase con metodos de tipo lista implementada con pilas
 */
class MyListaPila{
private:
    stack<int> lista;
public:
    
    /**
     * @brief Pide los datos al usuario para crear la lista a su antojo
     */
    void introduce(){
        int a;
        cout << "Introduce los valores de la 'listaPila':(0 para terminar) " << endl;
        cin >> a;
        while(a != 0){
            lista.push(a);
            cin >> a;
        }
    }
    
    /**
     * @brief Inserta al estilo de las listas pero usando stacks
     * No podemos pasar un objeto iterator ya que las pilas no pueden usarlo
     * @param posicion : int Posicion a insertar
     * @param a_insertar : int Dato entero a insertar
     */
    void insertar(const int posicion, int a_insertar){
        int contador = lista.size();
        stack<int> aux;
        
        //Quitamos elementos y los metemos en una pila auxiliar hasta la posicion deseada
        while(contador != posicion){ 
            aux.push(lista.top());
            lista.pop();
            contador--;
        }
        
        aux.push(a_insertar); //insertamos el elemento en la posicion
        
        //Metemos los elementos quitados de antes
        while(!aux.empty()){
            lista.push(aux.top());
            aux.pop();
        }
    }
    /**
     * @brief Borra al estilo de las listas pero usando stacks
     * @param posicion : int Posicion del elemento a borrar
     */
    void borrar(const int posicion){
        int contador = lista.size()-1;
        stack<int> aux;
        
        //Quitamos elementos y los metemos en una pila auxiliar hasta la posicion deseada
        while(contador != posicion){ 
            aux.push(lista.top());
            lista.pop();
            contador--;
        }
        
        lista.pop(); //eliminamos el elemento en la posicion
        
        //Metemos los elementos quitados de antes
        while(!aux.empty()){
            lista.push(aux.top());
            aux.pop();
        }  
    }
    
    /**
     * @brief Imprime la lista a partir de stacks sin destruirla en el proceso
     */
    void imprimir(){
        cout << "Mi lista hecha con pila contiene: ";
        stack<int> aux = lista;
        stack<int> invertida;
        while(!aux.empty()){
            invertida.push(aux.top());
            aux.pop();
        }
        
        while(!invertida.empty()){
            cout << invertida.top() << " ";
            invertida.pop();
        }
        cout << "\n";
    }
};

/**
 * @brief Programa principal donde realizar las pruebas y probar la clase
 * @return 0 si todo funciona bien, otro numero en caso de error
 */
int main ()
{
    int insertar, pos_insertar, pos_borrar;
    enunciado();

    MyListaPila prueba;
    prueba.introduce();
    cout << "\nQue numero quieres insertar y en que posicion(dato, pos):";
    cin >> insertar >> pos_insertar;

    cout << "Antes de insertar" << endl;
    prueba.imprimir();

    prueba.insertar(pos_insertar,insertar);
    cout << "Despues de insertar" << endl;
    prueba.imprimir();

    cout << "\nQue posicion quieres borrar(pos):";
    cin >> pos_borrar;

    prueba.borrar(pos_borrar);
    cout << "Tras borrar" << endl;
    prueba.imprimir();
    
    return 0;
}
