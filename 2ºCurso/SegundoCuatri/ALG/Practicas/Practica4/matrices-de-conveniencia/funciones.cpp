/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: yerasito
 *
 * Created on 5 de mayo de 2022, 15:48
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;

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

void EliminaFilas(vector<vector<int>> & matrix, const vector<int> & aEliminar){
    for(int i = aEliminar.size()-1; i > -1; i--)
        matrix.erase(matrix.begin()+aEliminar[i]);
}

void EliminaColumnas(vector<vector<int>> & Matrix, const vector<int> & aEliminar){
    for(int i=0; i < Matrix.size();i++)
        for(int j = aEliminar.size()-1; j > -1; j--)
            Matrix[i].erase(Matrix[i].begin()+aEliminar[j]);
}

void ImprimeVector(vector<int> v){
    cout << endl;
    for(int i = 0; i <  v.size(); i++)
        cout << v[i] << " ";
    cout << endl;
}

void ImprimeMatriz(vector<vector<int>> Matrix){
    cout << "\n\nLa matriz es: ";
    for(int i = 0; i < Matrix.size(); i++){
        cout << endl;
        for(int j = 0; j < Matrix[i].size(); j++)
            cout << Matrix[i][j] << " ";
    }
    cout << endl;
}

void PermutarSig(const int & tama, vector<int> & aEliminar, int n){

    
    if(aEliminar[n] < tama-1)
        aEliminar[n]++;
    ImprimeVector(aEliminar);

    if( n == 0 and aEliminar[n] >= (tama-aEliminar.size())){
        aEliminar.push_back(0);
        for(int i = 0; i < aEliminar.size()-1; i++)
            aEliminar[i] = i;
        aEliminar[aEliminar.size()-1] = aEliminar.size()-2;
        cout << endl;
    }
    else if(aEliminar[n] >= (tama-aEliminar.size())){
        if(aEliminar[n-1] < tama-2)
            aEliminar[n] = aEliminar[n-1]+2;
        PermutarSig(tama,aEliminar, n-1);
    }
}
   

void fuerzaBruta2(const vector<vector<int>> &M, vector<int> & vertices){
    vector<int> aEliminar;
    bool clique = false;

    vector<vector<int>> aux = M;
    
    aEliminar.push_back(0);
    
    while(!clique){
        clique = true;
        
        //Elimina Columnas
        EliminaColumnas(aux, aEliminar);
        //Elimina Filas
        EliminaFilas(aux, aEliminar);
        
        //Comprueba factibilidad
        for(int i = 0; i < aux.size(); i++){
            for(int j = i+1; j < aux[i].size(); j++)
                if(aux[i][j] != 1)
                    clique = false;
        }
        
        if(!clique){ //si falla, cambia aEliminar
            aux = M;
            PermutarSig(M.size(), aEliminar, aEliminar.size()-1);
        }
    }
    
    //Elimina los vertices para la solucion
    for(int i = aEliminar.size()-1; i > -1; i--){
        vertices.erase(vertices.begin() + aEliminar[i]);
    }    
}
    
class Solucion{
private:
    vector<vector<int>> M;
    int n;
    int contadorSoluciones;
public:
    vector<int> vertices;

    Solucion( const vector<int> &v, const vector<vector<int>> M) {
        this->vertices = v;
        this->M = M;
        n = M.size();
        
        vertices.resize(M.size());
        fill(vertices.begin(), vertices.end(),-1);
        contadorSoluciones = 0;
    }
    
    int size() const{
        return n;
    }
    
    void iniciaComp(int k){
        vertices[k] = -1;
    }
    
    void SigValComp(int k){
        vertices[k]++;
    }
    
    bool TodosGenerados(int k){
        return (vertices[k] >= n);
    }
    
    bool Factible(int k){
        bool factible = true;
            
        for(int i = 0; i < k && factible; i++){
            if(vertices[i] == vertices[k] or M[i][vertices[k]] != 1)
                factible = false;
        }
        
        return factible;
    }
    
    int getContadorSoluciones(){
        return contadorSoluciones;
    }
    
    void ProcesaSolucion(){
        cout << "\nSolucion ";
        for(int i = 0; vertices[i] != -1; i++)
            cout << "v" << vertices[i] << " ";
        cout << endl;
        contadorSoluciones++;
    }
    
    void VueltaAtras(int pos){
        if (pos == vertices.size())
            return;
        vertices[pos] = -1;
    }
};

void back_recursivo(Solucion &Sol, int k){
    cout << "\nk=" << k;
    if(k == 6)
        Sol.ProcesaSolucion();
    else{
        Sol.iniciaComp(k);
        Sol.SigValComp(k);
        
        while(!Sol.TodosGenerados(k)){
            if(Sol.Factible(k)){
                back_recursivo(Sol, k+1);
            }
            Sol.SigValComp(k);
        }
    }
}

/*
 * 
 */
int main(int argc, char** argv) {
   string line;
   int n;
   vector<vector<int>> M;
   
   //Lee el archivo pasado por parámetro
   ifstream f(argv[1]);
   
   getline(f, line); //Cogemos la primera linea y la imprimimos
   cout << line;
   
   while (std::getline(f, line)) //Lee la matriz
   {
        std::istringstream iss(line);
        M.emplace_back(std::istream_iterator<int>(iss),
                                 std::istream_iterator<int>());
   }
   
   //Imprime la matriz
   for(int i = 0; i < M.size(); i++){
       cout << endl;
       for(int j = 0; j < M[i].size(); j++)
           cout << M[i][j] << " ";
   }
   cout << endl;
   
   
   //---------------------------------------------------------------------------
   //Insertar algoritmo de clique
   vector<int> vertices; //vector solucion
   Solucion sol(vertices, M);

   for(int i = 0; i < M.size(); i++)  
       vertices.push_back(i);
   
   fuerzaBruta2(M,vertices);
   
    cout << "\n\nClique max " << vertices.size() << endl;

    for(int i = 0; i < vertices.size(); i++)
        cout << vertices[i] << " ";
    cout << endl;
   
   //back_recursivo(sol, 0);
   //---------------------------------------------------------------------------
   
   // n = M.size()
   cout << "\n\nLa matriz es de tamaño " << M.size() << endl;
    
    return 0;
}

