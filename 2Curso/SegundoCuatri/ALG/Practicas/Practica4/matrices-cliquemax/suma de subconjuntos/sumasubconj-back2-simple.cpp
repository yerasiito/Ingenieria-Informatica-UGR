#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <vector>

//Problema de la suma de subconjuntos. El calculo de la factibilidad es O(1). Version sencilla (poco estructurada)

vector<int> X;
vector<int> W;
int n;
int M;
int contadorSoluciones;
int sumatoria;
int resto;

bool factible(int k){		
        bool factible = false;
        if (((sumatoria + resto >= M) && (sumatoria + W[k+1] <= M)) || (sumatoria == M))
                factible = true;
        return factible;
	}

void ProcesaSolucion() {
    ///*
        cout << "Solucion: ";
            for (int i=0; i<X.size(); i++){
                if (X[i]==1) cout << W[i] << " ";
        }
        cout << endl;
    //*/
        contadorSoluciones++;
}

void back_recursivo(int k){
    
if (k==n) ProcesaSolucion();
else {
    X[k]=1;
    sumatoria = sumatoria + W[k];
    resto = resto - W[k];
    if (factible(k)) back_recursivo(k+1);
    sumatoria = sumatoria - W[k];
    resto = resto + W[k];

    X[k]=0;
    resto = resto - W[k];
    if (factible(k)) back_recursivo(k+1);
    resto = resto + W[k];
    }
}

int main(int argc, char * argv[])
{
  
  if (argc != 3)
  {
    cerr << "Formato " << argv[0] << " <num_elem>" << " <valor M> " << endl;
    return -1;
  }

  n = atoi(argv[1]);
  M = atoi(argv[2]);

for (int i = 0; i < n; i++)
        W.push_back(i+1);
contadorSoluciones = 0;
sumatoria = 0;
resto = 0;
for (int i=0; i<W.size(); i++) resto = resto + W[i];
X.resize(n);

  clock_t tantes;
  clock_t tdespues;

	tantes = clock();
        back_recursivo(0);
	tdespues = clock();

	cout << "Soluciones: " << contadorSoluciones << endl;

  cout << n << " " << (double)(tdespues - tantes) / CLOCKS_PER_SEC << endl;


  return 0;
}
