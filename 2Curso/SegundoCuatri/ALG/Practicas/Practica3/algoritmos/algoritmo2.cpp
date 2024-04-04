/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: yerasito
 *
 * Created on 27 de abril de 2022, 17:44
 */

#include <cstdlib>
#include <iostream>
#include <map>
using namespace std;

const int n = 7;
int c[n][n];
int a[n];

//---------------------- Genera matrices de conveniencia ----------------------
double uniforme() 
{
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}

void generaconveniencias() {
 srand(time(0));
 for (int i = 0; i < n-1; i++)
   for (int j = i+1; j < n; j++) {
        double u=uniforme();
        c[i][j]=(int)(u*101);
        c[j][i]=c[i][j];
     }
 for (int i = 0; i < n; i++) c[i][i]=0;
}

//---------------------- Calcula conveniencia ----------------------
int calculaconveniencia() {
    int suma=0;
    for (int i=1; i<n-1; i++){
        suma+=c[a[i]][a[i-1]]+c[a[i]][a[i+1]]; // desde 1 hasta n-2
    }
    
    suma+=c[a[0]][a[n-1]]+c[a[0]][a[1]]; //se añade los que están al lado de 0
    suma+=c[a[n-1]][a[n-2]]+c[a[n-1]][a[0]]; //se añade los que están al lado de n-1

    return suma;
}


//---------------------- ALGORITMO OPTIMO P.R HEAP --------------------------
void generapermutaciones(int m, int * a) {
    if (m==1) {
        //for (int i=0; i < n; i++) cout <<a[i]<<" ";
        //sustituir la escritura de la permutacion por la evaluacion de la misma
        //e ir guardando la que vaya dando mejor conveniencia
    }
    else
        for (int i= 0; i < m; i++) {
            generapermutaciones(m-1, a);
            if (m%2==0) swap(a[i],a[m-1]);
            else
                swap(a[0],a[m-1]);
            }
}

/*
 * 
 */
 void solucionGreedy(int n, int * a) {
 	bool candidatos[n];
    int max = -1, pres, izq= n-1, der=1;
    bool insertarIzq;
    map<int, bool> sentados;

    // Función selección:
    // Inicialmente se selecciona a uno de los presidentes
    // que tienen la mejor conveniencia entre sí 

    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
        	if (c[i][j] > max){
        		max = c[i][j];
        		pres = i;
        		a[0]=i;
        	}
        }
    }
    max = -1;
    a[0]=pres;
    sentados[pres]=true;
    // Función solución:
    // Cuando las posiciones a la izquierda y a la derecha de los 
    // presidentes adyacentes se cruzan el vector con la solución estará lleno
    while (der != (izq + 1) % n){
    	max = -1;
    	for (int i = 0; i < n; i++){

            // Se selecciona al candidato que mejor conveniencia tenga
            // con los presidentes de la izquierda o de la derecha
    		if (c[a[(izq+1) % n]][i] > max and sentados[i] == false){
    			max = c[a[(izq+1) % n]][i];
    			pres = i;
    			insertarIzq=true;
    		}
    		if (c[a[(der+n-1)%n]][i] > max and sentados[i] == false){
    			max = c[a[(der+n-1)%n]][i];
    			pres = i;
    			insertarIzq=false;
    		}
        }

        // Se elimina al seleccionado de los candidatos
        sentados[pres]=true;
        // Se inserta al presidente a la izquierda o a la derecha
        // de los presidentes ya seleccionados de forma adyacente
        if (insertarIzq){
            a[izq]=pres;
            izq = (izq + n-1) % n;
        }else{
            a[der]=pres;
            der = (der + 1) % n;
        }
    }

    
    
}
int main(int argc, char** argv) {
    //Inicializa el vector de asignacion
    for (int i=0; i<n; i++)
        a[i]=i;
    
    
    //Genera la matriz de conveniencia
    generaconveniencias();
    //Imprime la matriz de conveniencia
    cout << "Matriz de conveniencia: ";
    for(int i = 0; i < n; i++){
        cout << endl;
        for(int j = 0; j < n; j++)
            cout << c[i][j] << "\t";
    }
    
    //Insertar algoritmo de asignacion
    
    //Calcular la solución optima
    // generapermutaciones(n,a);
    cout << "\nLa conveniencia optima de la asignacion es: ";
    cout << calculaconveniencia() << endl;
    cout << endl;
    
    //Vector asignacion resultado
    cout << "\nVector resultado optimo: ";
    for(int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
    
    solucionGreedy(n, a);
    cout << "\nVector resultado greedy: ";
    for(int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
    //Calcula la conveniencia total de la asignacion dada
    cout << "\nLa conveniencia del algoritmo greedy asignacion es: ";
    cout << calculaconveniencia() << endl;
    
    return 0;
}

