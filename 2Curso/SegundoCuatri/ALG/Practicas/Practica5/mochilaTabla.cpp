#include <iostream>
#include <vector>
using namespace std;

int mochilaBD(int MAX_PESO, int pesos[], int beneficios[], int n)
{
    int item, peso;
    vector<vector<int>> M(n + 1, vector<int>(MAX_PESO + 1));
        
    //Inicializa fila a 0
    for(peso = 0; peso <= MAX_PESO; peso++)
        M[0][peso] = 0;

	// Construimos la tabla
	for(item = 1; item <= n; item++)
	{
            //Inicializa las columnas a 0
            M[item][0] = 0;
            
            for(peso = 1; peso <= pesos[item]-1; peso++)
                M[item][peso] = M[item-1][peso];
            
            for(peso = pesos[item]; peso <= MAX_PESO; peso++)
            {
                if ( (M[item-1][peso - pesos[item]] + beneficios[item]) > M[item-1][peso])
                    M[item][peso] = M[item-1][peso - pesos[item]] + beneficios[item];
                else
                    M[item][peso] = M[item-1][peso];
            }
	}
        
        cout << "Tabla Resultante: " << endl;
        for(auto it : M){
            for(auto jt : it)
                cout << jt << "\t";
            cout << endl;
        }
        cout << "\nEl beneficio máximo es: ";
	return M[n][MAX_PESO];
}

// Driver Code
int main()
{
	int pesos[] = {0, 3, 4, 6};
	int beneficio[] = {0, 7, 8, 11};
	const int MAX_PESO = 10;
	int n = sizeof(beneficio) / sizeof(beneficio[0]) - 1;
        
	cout << mochilaBD(MAX_PESO, pesos, beneficio, n) << endl;
	
	return 0;
}