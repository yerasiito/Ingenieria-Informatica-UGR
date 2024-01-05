
#include <iostream>
#include <string>
using namespace std;

/**
* 3. [Errores en funciones void] Encuentre los errores, si los hubiese, en las siguientes
* funciones void:
**/

/*
void EliminaUltimo(string cadena){
cadena.pop_back();
}
*/
//Una funcion void no puede modificar una variable ya que no la puede devolver

/*
void Imprime(double valor){
double valor;
cout << valor;
}
*/
//Se redeclara la variable valor

/*
void Cuadrado (int entero){
return entero*entero;
}
*/
//Un void no puede devolver una variable mediante un return
