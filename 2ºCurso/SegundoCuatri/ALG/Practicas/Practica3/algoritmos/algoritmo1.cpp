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
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<vector<int>> c;
vector<int> a;

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
void generapermutaciones(int m) {
    if (m==1) {
        //for (int i=0; i < n; i++) cout <<a[i]<<" ";
        //sustituir la escritura de la permutacion por la evaluacion de la misma
        //e ir guardando la que vaya dando mejor conveniencia
    }
    else
        for (int i= 0; i < m; i++) {
            generapermutaciones(m-1);
            if (m%2==0) swap(a[i],a[m-1]);
            else
                swap(a[0],a[m-1]);
            }
}


struct candidato{
    int presidente;
    int valor;
};

struct comparaCandidatos{
    bool operator()(const candidato & candidato1, const candidato &candidato2) const
    {
        return candidato1.valor > candidato2.valor;
    }
};

bool estaEnVector(int presidente){
    return find(a.begin(), a.end(), presidente) != a.end();
}

void imprimeMatriz(){
    cout << "Matriz de conveniencia: ";
    for(int i = 0; i < n; i++){
        cout << endl;
        for(int j = 0; j < n; j++)
            cout << c[i][j] << "\t";
    }
}

void greedy(){
    for (int i=0; i<n; i++)
        a[i]=-1;
    
    vector<set<candidato, comparaCandidatos>> candidatos;
    candidatos.resize(n);

    //Ordena candidatos de mayor a menor empezando del presidente 0 a n-1
    int j = 0;
    
    //El bucle completo es O(n²)
    for(auto it = candidatos.begin(); it != candidatos.end(); ++it){ //O(n)
        for(int i = 0; i < n; i++){ //O(n)
            candidato nuevo;
            nuevo.presidente = i;
            nuevo.valor = c[i][j];
            (*it).insert(nuevo);
        }
        j++;
    }
    
    //Mete al mejor candidato
    j=0;
    for(auto it = candidatos.begin(); it != candidatos.end(); ++it){ //O(n)
        auto itset = (*it).begin();
        while( estaEnVector((*itset).presidente) and itset != (*it).end() ){ //O(n²) ya que estaEnVector es O(n) + while=O(n)
            itset++;
        }
        a[j] = (*itset).presidente;
        j++;
    }
}

/*
 * 
 */
int main(int argc, char** argv) {
    cout << "Introduce el numero de presidentes:";
    cin >> n;
    a.resize(n);
    c.resize(n, vector<int>(n));
    //Genera la matriz de conveniencia
    generaconveniencias();
    
    //Imprime la matriz de conveniencia
    imprimeMatriz();
    
    //Calcular la solución optima-----------------------------------------------
    for (int i=0; i<n; i++)
        a[i]=i;
    generapermutaciones(n);
    cout << endl;
    
    cout << "\nVector optimo resultado: ";
    for(int i = 0; i < n; i++)
        cout << a[i] << " ";
    
    cout << "\nLa conveniencia optima es: ";
    cout << calculaconveniencia() << endl;
    
    //Algoritmo de asignacion---------------------------------------------------
    greedy();      
    
    cout << "\nVector greedy resultado: ";
    for(int i = 0; i < n; i++)
        cout << a[i] << " ";
    
    cout << "\nLa conveniencia greedy es: ";
    cout << calculaconveniencia() << endl;
    
    cout << endl;

    //--------------------------------------------------------------------------
    
    return 0;
}

