#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <vector>

//Problema de la suma de subconjuntos. El calculo de la factibilidad es O(1)

class Solucion {
private:
	vector<int> X;
	vector<int> W;
	int M;
	int contadorSoluciones;
	int sumatoria;
	int resto;

public:
	Solucion(const vector<int> &vectorNumeros, const int valorObjetivo) {
		W = vectorNumeros;
		M = valorObjetivo;
		contadorSoluciones = 0;
		sumatoria = 0;
		resto = 0;
		for (int i=0; i<W.size(); i++){
			X.push_back(2);
			resto = resto + W[i];
		}
	}

	int size() const {
		return (X.size());
	}

	void IniciaComp(int k) {
		X[k] = 2;
	}

	void SigValComp(int k) {
		X[k]--;

		if (X[k] == 1){
			sumatoria = sumatoria + W[k];
			resto = resto - W[k];
		}
		if (X[k] == 0)
			sumatoria = sumatoria - W[k];
	}

	bool TodosGenerados(int k) {
		return (X[k] == -1);
	}

	bool Factible(int k){		
		bool factible = false;

		if (((sumatoria + resto >= M) && (sumatoria + W[k+1] <= M)) || (sumatoria == M))
			factible = true;

		return factible;
	}

	void ProcesaSolucion() {
            ///*
                cout << "Solucion: ";
		for (int i=0; i<X.size(); i++){
		//	cout << X[i]*W[i] << " ";
                        if (X[i]==1) cout << W[i] << " ";
		}
		cout << endl;
            //*/
		contadorSoluciones++;
	}
	
	int getContadorSoluciones(){
		return contadorSoluciones;
	}

	void VueltaAtras(int pos){
		if (pos == X.size())
			return;
		resto = resto + W[pos];
		X[pos] = 2;
	}
};

void back_recursivo(Solucion &Sol, int k){
	if (k == Sol.size())
		Sol.ProcesaSolucion();
	else {
		Sol.IniciaComp(k);
		Sol.SigValComp(k);
		while (!Sol.TodosGenerados(k)) {
			if (Sol.Factible(k)){
				back_recursivo(Sol, k+1);
				Sol.VueltaAtras(k+1);
			}
			Sol.SigValComp(k);
		}
	}
}

int main(int argc, char * argv[])
{
  
  if (argc != 3)
  {
    cerr << "Formato " << argv[0] << " <num_elem>" << " <valor M> " << endl;
    return -1;
  }

  int n = atoi(argv[1]);
  int M = atoi(argv[2]);
  vector<int> T;

	for (int i = 0; i < n; i++)
		T.push_back(i+1);

	//cout << "T: ";
	//for (int i = 0; i < n; i++)
	//	cout << T[i] << " ";
	//cout << endl;

  clock_t tantes;
  clock_t tdespues;

	Solucion sol(T, M);
	tantes = clock();
        back_recursivo(sol, 0);
	tdespues = clock();

	cout << "Soluciones: " << sol.getContadorSoluciones() << endl;

  cout << n << " " << (double)(tdespues - tantes) / CLOCKS_PER_SEC << endl;

  return 0;
}
