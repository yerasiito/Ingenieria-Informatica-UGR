 #include <iostream>
 #include "Cola_max_Pila.h"
 #include "pila.h"
 
 using namespace std;
 
 
 /**
 * @brief Función principal del programa
 */
 
// class Cola_max;
// class Pila<T>;
 
 int main(){
	 Cola_max q;
	 int dato;
     /*
     int i;
	 for ( i=10; i>=0 ; i--)
		 q.poner(i);
	*/
     cout << "Introduce un dato a la cola(0 para salir):";
    cin >> dato;
	while(dato != 0){
        q.poner(dato);
        cin >> dato;
    }
	 while (!q.empty() ){
		 Elemento x = q.frente();
		 cout << x <<endl;
		 q.quitar();
 	}
 	
 	return 0;
 }
