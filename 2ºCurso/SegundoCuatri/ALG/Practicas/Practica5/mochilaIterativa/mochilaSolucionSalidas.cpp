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

    cout << "\nLos items seleccionados son: " << endl;
    while (i-1 >= 0 and M[i][c] >= 0){
        if (M[i][c] != M[i - 1][c]){
            cout << "item " << i+1 << " con peso: " << pesos[i] << " y beneficio " << beneficio[i] << endl;
            c -= pesos[i];
            beneficio_total -= beneficio[i];
        }
        else
            i--;
    }

    while(beneficio_total > 0){
        cout << "item " << 1 << " con peso: " << pesos[0] << " y beneficio " << beneficio[0] << endl;
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

    for(auto it : M){
        for(auto jt: it)
            cout << jt << "\t";

        cout << endl;
    }

    objetosSeleccionados(M, pesos, beneficio);

    cout << "\nBeneficio total: ";
    return M[n][MAX_PESO];
}

int main(int argc, char **argv)
{
    int n = 10;
    srand(time(0));
    int MAX_PESO=10;

	if(argc > 1)
		MAX_PESO = atoi(argv[1]);

    n = MAX_PESO; //Modifica el peso e items por igual

    vector<int> pesos, beneficio;

    for (int i = 0; i < n; i++)
    {
        pesos.push_back(rand()%(3*MAX_PESO/4)+MAX_PESO/4);    // Limita el peso para que no se obtengan demasiadas decisiones de objeto y
        beneficio.push_back(rand()%20+1);                           // no se obtenga un árbol demasiado profundo
	}

    cout << "Pesos:";
    for(auto it : pesos)
        cout << it << " ";
    cout << "\nBeneficios: ";
    for(auto it : beneficio)
        cout << it << " ";
    cout << endl;


    tantes = high_resolution_clock::now();
    cout << mochilaIlimitada(n, pesos, beneficio, MAX_PESO) << endl;
	tdespues = high_resolution_clock::now();
	transcurrido = duration_cast<duration<double>>(tdespues - tantes);

    cout << "NºItems: ";
	cout << n << "\tCapacidad: " << MAX_PESO << "\tTiempo: " << transcurrido.count() << endl;

    return 0;
}
