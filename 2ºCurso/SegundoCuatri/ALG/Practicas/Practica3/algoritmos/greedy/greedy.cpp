/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   greedyTiempo.cpp
 * Author: yerasito
 *
 * Created on 28 de abril de 2022, 0:16
 */
#include <vector>
#include <set>

using namespace std;

void greedy(){
    for (int i=0; i<n; i++)
        a[i]=-1;
    
    vector<set<candidato, comparaCandidatos>> candidatos;
    candidatos.resize(n);

    //Ordena candidatos de mayor a menor empezando del presidente 0 a n-1
    int j = 0;
    for(auto it = candidatos.begin(); it != candidatos.end(); ++it){
        for(int i = 0; i < n; i++){
            candidato nuevo;
            nuevo.presidente = i;
            nuevo.valor = c[i][j];
            (*it).insert(nuevo);
        }
        j++;
    }
    
    //Mete al mejor candidato
    j=0;
    for(auto it = candidatos.begin(); it != candidatos.end(); ++it){
        auto itset = (*it).begin();
        while( estaEnVector((*itset).presidente) and itset != (*it).end() ){
            itset++;
        }
        a[j] = (*itset).presidente;
        j++;
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
