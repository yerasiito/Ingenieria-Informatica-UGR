// C++ implementation of the approach
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>
using namespace std;

const int MAX = 100;
// Stores the vertices
vector<int> store;
vector<int> maximo;

// Graph
vector<vector<int>> graph;

void ImprimeVector(vector<int> v){
    for(int i = 0; i <  v.size()-1; i++)
        cout << v[i] << " ";
    cout << endl;
}

void fuerzaBruta(vector<vector<int>> M, vector<int> & vertices){
    for(int i = 0; i < M.size(); i++){
        vector<int> aux;
        aux.push_back(i);
        for(int j = 0; j < M[i].size(); j++){
            bool factible = true;
            for(int iter = 0; iter < aux.size(); iter++)
                if(M[aux[iter]][j] != 1)
                    factible = false;
            if(factible)
                aux.push_back(j);
        }

        if(aux.size() > vertices.size()){
            vertices = aux;
        }   
    }
}

// vertices in store array is a clique or not
bool is_clique(int b)
{

	// Run a loop for all set of edges
	for (int i = 1; i < b; i++) {
		for (int j = i + 1; j < b; j++)

			// If any edge is missing
			if (graph[store[i]][store[j]] == 0)
				return false;
	}
        
        if(store.size() > maximo.size())
            maximo = store;
	return true;
}

// Function to find all the sizes
// of maximal cliques
int maxCliques(int i, int l)
{
	// Maximal clique size
	int max_ = 0;

	// Check if any vertices from i+1
	// can be inserted
	for (int j = i + 1; j <= graph.size(); j++) {

		// Add the vertex to store
		store.resize(l+1);
                store[l] = j;

		// If the graph is not a clique of size k then
		// it cannot be a clique by adding another edge
		if (is_clique(l + 1)) {

			// Update max
			max_ = max(max_, l);

			// Check if another edge can be added
			max_ = max(max_, maxCliques(j, l + 1));
		}
	}
	return max_;
}

// Driver code
int main(int argc, char** argv) {
   string line;
   
   //Lee el archivo pasado por parámetro
   ifstream f(argv[1]);
   
   getline(f, line); //Cogemos la primera linea y la imprimimos
   //cout << line;
   
   while (std::getline(f, line)) //Lee la matriz
   {
        std::istringstream iss(line);
        graph.emplace_back(std::istream_iterator<int>(iss),
                                 std::istream_iterator<int>());
   }
//   fuerzaBruta(graph,store);
//   cout << "Solucion Bruto";
//   ImprimeVector(store);

   store.clear();
   
   cout << "Numero de clique Maximo " << maxCliques(0, 1);
   cout << "\nVertices: ";
   ImprimeVector(maximo);

    return 0;
}