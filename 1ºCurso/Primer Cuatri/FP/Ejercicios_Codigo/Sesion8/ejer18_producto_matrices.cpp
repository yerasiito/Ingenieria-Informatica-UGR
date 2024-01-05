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
   const int MAX_FIL = 10, MAX_COL = 10;
   double matrA[MAX_FIL][MAX_COL],matrB[MAX_FIL][MAX_COL], multpl[MAX_FIL][MAX_COL];
   double trasp[MAX_COL][MAX_FIL];
   int n, m,k;
   int a_insertar;

	//Entrada de datos

	cout << "Introduce el numero de filas y columnas de la primera matriz con un máximo de "
	<< MAX_FIL << " filas" << " y " << MAX_COL << " columnas." << endl;

	//matrA--> n x m
   cin >> n;
   cin >> m;

   for (int i=0; i<n; i++)
      for (int j=0; j<m; j++)
         cin >> matrA[i][j];

	//matrB--> m x k
   cout << "Introduce el numero columnas de la segunda matriz con un máximo de "
	<< MAX_COL << " columnas." << endl;

	cin >> k;

	for (int i=0; i<m; i++)
      for (int j=0; j<k; j++)
         cin >> matrB[i][j];

   ///////////////////////////////////////////////////////////////////////////

   for(int l=0; l<k; l++){
      for(int j=0; j<n; j++){
         a_insertar=0;
         for(int i=0; i<m; i++){
            a_insertar = a_insertar + matrA[j][i] * matrB[i][l];
         }
         multpl[j][l]= a_insertar;
      }
   }

	//Salida de Datos

	cout << "\n\n";
   cout << "Matriz primera:\n";

   for (int i=0; i<n; i++){
      cout << "\n";

      for (int j=0; j<m; j++)
         cout << matrA[i][j] << '\t';
   }

	cout << "\n\n";
   cout << "Matriz segunda:\n";

   for (int i=0; i<m; i++){
      cout << "\n";

      for (int j=0; j<k; j++)
         cout << matrB[i][j] << '\t';
   }

	cout << "\n\n";
   cout << "Matriz multiplicada:\n";

   for (int i=0; i<n; i++){
      cout << "\n";

      for (int j=0; j<k; j++)
         cout << multpl[i][j] << '\t';
   }
}
