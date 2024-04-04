#include<iostream>
#include<vector>
#include <chrono>
using namespace std;
using namespace std::chrono;

high_resolution_clock::time_point tantes, tdespues;
duration<double> transcurrido;

void objetosSeleccionados(vector<vector<int>> M, vector<int> pesos, vector<int> beneficio){
    int i = M.size()-1, c = M[0].size()-1;
    int beneficio_total = M[i][c];

    while (i-1 >= 0 and M[i][c] >= 0){
        if (M[i][c] != M[i - 1][c]){
            c -= pesos[i];
            beneficio_total -= beneficio[i];
        }
        else
            i--;
    }

    while(beneficio_total > 0){
        beneficio_total -= beneficio[0];
    }
}

int mochilaIlimitada(int n, vector<int> pesos, vector<int> beneficio, int MAX_PESO){
    vector<vector<int>> M;
    M.resize(n+1, vector<int>(MAX_PESO+1));

    // Cuando la capacidad es 0, no se puede seleccionar ningún item
    for(int i = 0; i <= n; i++)
        M[i][0] = 0;

    // Cuando un solo item es considerado, obtiene el beneficio de usarlo para toda la mochila
    for(int c = 0; c <= MAX_PESO+1 and pesos[0] != 0; c++)
        M[0][c] = (c / pesos[0]) * beneficio[0];

    //Para cada item, comprueba para cada posible capacidad
    for(int i = 1; i <= n; i++){
        for(int c = 1; c <= MAX_PESO; c++){
            if (pesos[i] <= c)
                M[i][c] = max(M[i - 1][c], beneficio[i] + M[i][c - pesos[i]]);
            else
                M[i][c] = M[i - 1][c];
        }
    }
    objetosSeleccionados(M, pesos, beneficio);

    return M[n][MAX_PESO];
}

int main(int argc, char **argv)
{
    int n = 10;
    srand(time(0));
    const int MAX_PESO=20;

	if(argc > 1)
		n = atoi(argv[1]);


    vector<int> pesos, beneficio;

    for (int i = 0; i < n; i++)
    {
        pesos.push_back(rand()%(3*MAX_PESO/4)+MAX_PESO/4);    // Limita el peso para que no se obtengan demasiadas decisiones de objeto y
        beneficio.push_back(rand()%20+1);                           // no se obtenga un árbol demasiado profundo
	}

    tantes = high_resolution_clock::now();
    mochilaIlimitada(n, pesos, beneficio, MAX_PESO);
	tdespues = high_resolution_clock::now();
	transcurrido = duration_cast<duration<double>>(tdespues - tantes);

	cout << n << " " << transcurrido.count() << endl;

    return 0;
}
