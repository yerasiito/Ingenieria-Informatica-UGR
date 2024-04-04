#include <iostream>
#include <vector>
using namespace std;

int mochilaPD(int MAX_PESO, vector<int> pesos, vector<int> beneficios, int n)
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

            for(peso = 1; peso <= pesos[item]-1; peso++){
                M[item][peso] = M[item-1][peso];
            }

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

int main()
{
	vector<int> pesos = {0, 2, 1, 3, 2};
	vector<int> beneficio = {0, 12, 10, 20, 15};
	const int MAX_PESO = 5;
        
        //Duplicamos los pesos y beneficios de cada item hasta que pueda ocupar toda la mochila
        vector<int> pesosMultiple, beneficiosMultiple;
        for(int i = 0; i <= pesos.size(); i++){
            int peso = pesos[i];
            while(peso != 0 and peso <= MAX_PESO){
                pesosMultiple.push_back(pesos[i]);
                beneficiosMultiple.push_back(beneficio[i]);
                peso += pesos[i];
            }
        }
        cout << "Pesos multiples: ";
        for(auto it : pesosMultiple)
            cout << it << " ";
        cout << endl;
        cout << "Beneficios multiples: ";
        for(auto it : beneficiosMultiple)
            cout << it << " ";
        cout << endl;

	int n = pesosMultiple.size();

	cout << mochilaPD(MAX_PESO, pesosMultiple, beneficiosMultiple, n) << endl;

	return 0;
}
