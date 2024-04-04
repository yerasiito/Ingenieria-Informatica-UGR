#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

high_resolution_clock::time_point tantes, tdespues;
duration<double> transcurrido;

const int capacidad = 20;
int n=10;

int Mochila(int i, int d, int w,int sol[], vector<vector<int>> mej, int *p, int *b, int *max_obj){
    int resultado, cogiendo, sin_coger;
    // Si el beneficio ya ha sido calculado anteriormente se aprovecha el resultado
    if (mej[w][d] != -1){
        return mej[w][d];
    }
    // Si se alcanza el máximo de objetos de un tipo se pasa al siguiente tipo
    if (max_obj[i] == d){
        i++;
    }
    // Si no queda espacio en la mochila o ya se han comprobado todos los objetos se devuelve 0
    if ((max_obj[n-1] == d) or w<=0){
        resultado = 0;
    // Si no cabe el siguiente objeto no se escoge
    }else if (p[i] > w){
        resultado = Mochila(i, d+1, w, sol, mej, p, b, max_obj);
    }else{
        // Se calcula el beneficio máximo cogiendo o no cogiendo el objeto
        int aux[n], aux2[n];
        for (int i = 0; i < n; i++){
            aux[i]=aux2[i]=0;
        }
        cogiendo=b[i] + Mochila(i, d+1, w-p[i], aux, mej, p, b, max_obj);
        sin_coger=Mochila(i, d+1, w, aux2, mej, p, b, max_obj);
        resultado=max(cogiendo, sin_coger);
        if (cogiendo > sin_coger){
            aux[i]++;
        }
        for (int i = 0; i < n; i++)
        {
            if (cogiendo > sin_coger){
                sol[i]=aux[i];
            }else{
                sol[i]=aux2[i];
            }
        }

    }
    // Se almacena el beneficio obtenido en una determinada decisión con una determinada capacidad restante
    mej[w][d]=resultado;
    return resultado;
}
int main(int argc, char **argv)
{
    srand(time(0));
	if(argc > 1)
		n = atoi(argv[1]);

	int p[n],	// ={3, 4, 6}
	b[n],	// ={7, 8, 11}
	max_obj[n],  sol[n];

    for (int i = 0; i < n; i++)
    {
        p[i]=rand()%(3*capacidad/4)+capacidad/4;    // Limita el peso para que no se obtengan demasiadas decisiones de objeto y
        b[i]=rand()%20+1;                           // no se obtenga un árbol demasiado profundo
        sol[i]=0;
    }
    // Cálculo del máximo número de objetos de cada tipo acumulativo
    max_obj[0]=capacidad/p[0];
    for (int i = 1; i < n; i++)
    {
        max_obj[i]= max_obj[i-1] + capacidad/p[i];
    }
    vector<vector<int>> ben;
    for (int j = 0; j <= capacidad ; j++)
    {
        vector<int> v;
        for (int k = 0; k <= max_obj[n-1] ; k++){
            if (j == 0 or k==max_obj[n-1]){
                v.push_back(0);
            }else{
                v.push_back(-1);
            }
        }
        ben.push_back(v);
    }
	tantes = high_resolution_clock::now();
	Mochila(0, 0, capacidad, sol, ben, p, b, max_obj);
	tdespues = high_resolution_clock::now();
	transcurrido = duration_cast<duration<double>>(tdespues - tantes);
	cout << n << " " << transcurrido.count() << endl;


/*
    cout << "Capacidad mochila: "<< capacidad << endl;

    cout << "Beneficios: " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << b[i] << "\t";
    }
    cout << endl;

    cout << "Pesos: " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << p[i] << "\t";
    }
    cout << endl;

    cout << "Beneficio máximo: "<< max << endl;

    cout << "Solución: " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << sol[i] << "\t";
    }
    cout << endl;*/
}
