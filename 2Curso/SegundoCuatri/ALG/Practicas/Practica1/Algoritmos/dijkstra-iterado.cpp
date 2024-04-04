#include<iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <cmath>  
using namespace std;

#include<chrono>
using namespace chrono;

high_resolution_clock::time_point tantes, tdespues;
duration<double> transcurrido;

static int const MAX_LONG  = 100;

int ** ReservaMatriz(int dim)
{
  int **M;
  if (dim  <= 0)
    {
      cerr<< "\n ERROR: Dimension de la matriz debe ser mayor que 0" << endl;
      exit(1);
    }
  M = new int * [dim];
  if (M == NULL)
    {
      cerr << "\n ERROR: No puedo reservar memoria para un matriz de "
	   << dim << " x " << dim << "elementos" << endl;
      exit(1);
    }
  for (int i = 0; i < dim; i++)
    {
      M[i]= new int [dim];
      if (M[i] == NULL)
	{
	  cerr << "ERROR: No puedo reservar memoria para un matriz de "
	       << dim << " x " << dim << endl;
	  for (int j = 0; j < i; j++)
	    delete [] M[i];
	  delete [] M;
	  exit(1);
	} 
    }
  return M;
}	


/**********************************************************************/

void LiberaMatriz(int ** & M, int dim)
{
  for (int i = 0; i < dim; i++)
    delete [] M[i];
  delete [] M;
  M = NULL;
}		


/**********************************************************************/
void RellenaMatriz(int **M, int dim)
{
  for (int i = 0; i < dim; i++)
    for (int j = 0; j < dim; j++)
      if (i != j)
	M[i][j]= (rand() % MAX_LONG);
}			


/**********************************************************************/

//This method returns a minimum distance for the 
// vertex which is not included in Tset.

int minimumDist(int dist[], bool Tset[], int dim) 
{
	int min=INT_MAX,index;
              
	for(int i=0;i<dim;i++) 
	{
		if(Tset[i]==false && dist[i]<=min)      
		{
			min=dist[i];
			index=i;
		}
	}
	return index;
}

void Dijkstra(int **M, int **Sal, int dim, int src) // adjacency matrix used
{
	int dist[dim]; // integer array to calculate minimum distance for each node.                            
	bool Tset[dim];// boolean array to mark visted/unvisted for each node.
	
	// set the nodes with infinity distance
	// except for the initial node and mark
	// them unvisited.  
	for(int i = 0; i<dim; i++)
	{
		dist[i] = INT_MAX;
		Tset[i] = false;	
	}
	
	dist[src] = 0;   // Source vertex distance is set to zero.             
	
	for(int k = 0; k<dim; k++)                           
	{
		int m=minimumDist(dist,Tset,dim); // vertex not yet included.
		Tset[m]=true;// m with minimum distance included in Tset.
		for(int i = 0; i<dim; i++)                  
		{
			// Updating the minimum distance for the particular node.
			//if(!Tset[i] && graph[m][i] && dist[m]!=INT_MAX && dist[m]+graph[m][i]<dist[i])
			if(!Tset[i] && dist[m]!=INT_MAX && dist[m]+M[m][i]<dist[i])
				dist[i]=dist[m]+M[m][i];
		}
	}
	for(int i = 0; i<dim; i++)  
	   Sal[src][i]=dist[i];
} 

int main (int argc, char **argv)
//int main()
{
//  clock_t tantes;    // Valor del reloj antes de la ejecución
//  clock_t tdespues;  // Valor del reloj después de la ejecución
  int dim;           // Dimensión de la matriz

  //Lectura de los parametros de entrada
  if (argc != 2)
    {
      cout << "Parámetros de entrada: " << endl
	   << "1.- Número de nodos" << endl << endl;
      return 1;	
    }	

  dim = atoi(argv[1]);	
  int ** M = ReservaMatriz(dim);
  int ** Sal = ReservaMatriz(dim);
  srand(time(NULL));
  RellenaMatriz(M,dim);
/*  cout<<"Matriz de distancias"<<endl;    
  for (int i = 0; i < dim;i++) {
   for (int j = 0; j < dim;j++)
	cout <<M[i][j]<<" ";
   cout<<endl;
  }
  cout<<endl;
*/

  tantes = high_resolution_clock::now(); // Tiempo de inicio
	for (int src=0;src<dim;src++)
	    Dijkstra(M,Sal,dim,src);

  tdespues = high_resolution_clock::now();    // Anotamos el tiempo de finalización
  transcurrido = duration_cast<duration<double>>(tdespues - tantes); //Calculamos la diferencia

  //Mostrar resultados
  cout << dim << "\t" << transcurrido.count() << endl;

//  cout << "Tiempo: " << ((double)(tdespues-tantes))/CLOCKS_PER_SEC << " s" << endl;
/*  cout<<"Matriz de distancias minimas"<<endl;  
  for (int i = 0; i < dim;i++) {
   for (int j = 0; j < dim;j++)
	cout <<Sal[i][j]<<" ";
   cout<<endl;
  }
  cout<<endl;
*/
  LiberaMatriz(M,dim);
  LiberaMatriz(Sal,dim);
	return 0;	                        
}
