 #include <iostream>
 #include "Pila_max_Cola.h"
 #include "cola.h"

 using namespace std;


 /**
 * @brief Función principal del programa
 */

// class Cola_max;
// class Pila<T>;

 int main(){
	 Pila_max q;
	 /*
     int i;
	 for ( i=10; i>=0 ; i--)
		 q.poner(i);
	*/
    int dato;
    cout << "Introduce un dato a la pila(0 para salir):";
    cin >> dato;
	while(dato != 0){
        q.poner(dato);
        cin >> dato;
    }

	 while (!q.empty()){
		 cout << q.frente() << endl;
		 q.quitar();
 	}

 	return 0;
 }

