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

	Elemento y = q.frente();
	cout<< y <<endl;

	 while (!q.empty() ){
		 Elemento x = q.frente();
		 cout << x <<endl;
		 q.quitar();
 	}
 	
 	return 0;
 }
