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
	 int i;
	 /*
	 for ( i=10; i>=0 ; i--)
		 q.poner(i);
	*/
	q.poner(4);
	q.poner(5);
	q.poner(6);
	q.poner(7);
	q.poner(22);
	q.poner(11);
	
	 while (!q.empty() ){
		 Elemento x = q.frente();
		 cout << x <<endl;
		 q.quitar();
 	}
 	
 	return 0;
 }
