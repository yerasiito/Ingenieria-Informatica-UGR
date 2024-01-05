//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// // Don Oreo y el Compa Mamado
//
//////////////////////////////////////////////////////////////////////////

//Mediana movil

#include <iostream>
using namespace std;

int main(){
  const float ceroKelvin = -273,15;
	const int TAMANIO = 1e6;
	double temperaturas[TAMANIO];
	double ordenados[TAMANIO];
	int posicion = 0, N = 3;
   double mediana;

	cout << "Introduzca las temperaturas: \n";
	cin >> temperaturas[posicion];


   //Lectura de Datos

	while(temperaturas[posicion] >= ceroKelvin){
		posicion++;
		cin >> temperaturas[posicion];
	}
   //Computo

   double a_insertar;
   int k;

 /*//Cálculo de la mediana
   Primero ordenamos las temperaturas y posteriormente hacemos su mediana*/

	for(int iter = 0; iter < posicion - (N-1); iter++){
      //asignamos los N temperaturas al vector ordenador
      for(int i=iter;i < N+iter; i++)
         ordenados[i] = temperaturas[i];
      for (int j = iter; j < N+iter; j++){
         a_insertar = ordenados[j];

         for (k = j; k > iter && a_insertar < ordenados[k-1]; k--)   // Ordenación de menor a mayor
            ordenados[k] = ordenados[k-1];

         ordenados[k] = a_insertar;
      }
   /*//Comprobar ordenacion
   cout << "El vector ordenado es: ";
   for (int j = iter; j < N+iter; j++)
      cout << ordenados[j] << " ";
   */
		mediana = 0;
		if(N % 2 != 0)
			mediana = ordenados[iter+(N/2)];
		else
			mediana = (ordenados[iter+(N/2)] + ordenados[iter+(N/2)-1]) / 2;

		cout << " " << mediana;
	}

	cout << " " << temperaturas[posicion];
}

