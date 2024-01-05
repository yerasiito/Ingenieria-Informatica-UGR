//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

#include <iostream>

using namespace std;

int main(){
   const int MAX_PEDIDOS = 100;
   const int MAX_TECNICOS = 100;
   int tarifa[MAX_TECNICOS][MAX_PEDIDOS];
   bool A[MAX_TECNICOS][MAX_PEDIDOS];
   bool cogidos[MAX_PEDIDOS];
   int tecnicos,pedidos;
   int menor;
   int pos_menor = 100;      //Lo inicializamos a cualquier número que no se vaya a utilizar como posicion en la matriz tarifa(como si pongo 123433124)

   //Entrada de Datos

   cout << "Introduce el numero de técnicos: ";
   cin >> tecnicos;

   pedidos = tecnicos;

   cout << "\nIntroduce la matriz tarifa: " << endl;

   for(int i = 0; i < tecnicos; i++)
      for(int j = 0; j < pedidos; j++)
         cin >> tarifa[i][j];

   //Cómputo

   int precio_total = 0;

   for(int i = 0; i < tecnicos; i++){
      menor = 100;
      pos_menor = 100;
      for(int j = 0; j < pedidos; j++){
         if(tarifa[i][j] < menor && cogidos[j] == false){
               menor = tarifa[i][j];
               pos_menor = j;
         }
      }
   cogidos[pos_menor] = true;
   A[i][pos_menor] = true;
   precio_total += menor;
   }


   //Salida de datos

   /*Bool*/
   cout << "\n\n" << "Asignacion de pedidos:" << endl;

   for(int i=0; i<tecnicos; i++){
      cout << "\n";

   for(int j=0; j<pedidos; j++){
      cout << A[i][j] << '\t';
      }
   }

   cout << endl << "------------------------------";
   /*Asignacion de pedidos*/

   for(int i = 0; i < tecnicos; i++){
      for(int j = 0; j < pedidos; j++){
         if(A[i][j] == true)
         cout << "\nTécnico " << i << " --> Pedido " << j;
      }
	}
   cout <<endl << "------------------------------";
	cout << "\nEl coste total es de: " << precio_total << endl;


   return 0;
}


