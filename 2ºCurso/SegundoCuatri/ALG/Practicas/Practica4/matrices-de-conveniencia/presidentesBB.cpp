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
#include <queue>
using namespace std;

const int n = 10;
int c[n][n];
int a[n], optimo[n], maxConv=0;
int n_expandidos = 0, n_podas = 0;


struct nodo{
    int cota_local;
    int conveniencia;
    int n_sentados;
    bool estaSentados[n];
    int sentados[n];
    bool operator<(nodo n) const{
        return cota_local<n.cota_local;
    }
};
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
int calculaconveniencia(int *a){
    int resultado=0;
    bool terminar=false;
    for (int i = 0; i < n-1 and !terminar; i++){
        if (a[i+1] != -1){
            resultado += c[a[i]][a[i+1]]*2;
        }else{
            terminar = true;
        }
    }
    if (a[n-1] != -1){
        resultado += c[a[0]][a[n-1]]*2;
    }
    return resultado;
}


//---------------------- ALGORITMO OPTIMO P.R HEAP --------------------------
void generapermutaciones(int m, int * a) {
    if (m==1) {
        if (calculaconveniencia(a) > maxConv){
            maxConv=calculaconveniencia(a);
            for (int i = 0; i < n; i++){
                optimo[i]=a[i];
            }
            
        }
    }
    else
        for (int i= 0; i < m; i++) {
            generapermutaciones(m-1, a);
            if (m%2==0) swap(a[i],a[m-1]);
            else
                swap(a[0],a[m-1]);
            }
}
int calcularCotaLocal(const nodo &nod){
    int resultado=0,max_conv_pri=-1,max_conv_ult=-1, max=-1, primer_pre= nod.sentados[0], ultimo_pre, conv;
    resultado += nod.conveniencia;
    if ( nod.n_sentados > 0){                       // Si hay algun presidente se sumara a la cota local la maxima
        ultimo_pre=nod.sentados[nod.n_sentados-1];  // conveniencia de los presidentes de los extremos con cualquier otro
        for (int i = 0; i < n;i++){
            conv = c[primer_pre][i]*2;
            if (i != primer_pre and conv > max_conv_pri){
                max_conv_pri= conv;
                resultado+=conv;
            }
            conv = c[ultimo_pre][i]*2;
            if (i != ultimo_pre and conv > max_conv_ult){
                max_conv_ult = conv;
                resultado+=conv;
            }
            
        }
    }
    for (int i = 0; i < n;i++){             // Se añade a la cota_local la maxima conveniencia de los presidentes no sentados con cualquier otro
        max=-1;
        if (!nod.estaSentados[i]){
            for (int j = i+1; j < n;j++){
                conv=c[i][j]*2;
                if (conv > max){
                    max = conv;
                    resultado+=conv;
                }
                
            }
        }
    }
    return resultado;
}
void solucionBB(int n, int* a){
    int cota_global=-1, max_conv=-1;
    priority_queue<nodo> vivos;
    nodo raiz, hijo;
    for (int i = 0; i < n; i++){
        raiz.sentados[i]=-1;
        raiz.estaSentados[i]=false;
    }
    raiz.n_sentados=0;
    raiz.conveniencia=0;
    raiz.cota_local= calcularCotaLocal(raiz);
    vivos.push(raiz);
    do{
        nodo actual = vivos.top();
        vivos.pop();
        if(actual.n_sentados==n){                   // Cuando ya esten sentados todos los presidentes en un nodo 
            if (actual.conveniencia > cota_global){ // se comprueba si hay que actualizar la mejor solucion y la cota global
                cota_global = actual.conveniencia;
            }
            if (actual.conveniencia > max_conv){
                max_conv=actual.conveniencia;
                for (int i = 0; i < n; i++){
                    a[i]=actual.sentados[i];
                }
                
            }
        }else if (actual.cota_local > cota_global){ // Funcion factibilidad:(cota_local > cota_global) Si la cota local del nodo actual es mayor
            n_expandidos++;
            for (int i = 0; i < n;i++){             // a la cota global se genererán todos los descendientes que también cumplan la factibilidad
                hijo = actual;
                if (!actual.estaSentados[i]){
                    hijo.sentados[hijo.n_sentados]=i;
                    hijo.estaSentados[i]=true;
                    hijo.n_sentados++;
                    hijo.conveniencia=calculaconveniencia(hijo.sentados);
                    hijo.cota_local=calcularCotaLocal(hijo);
                    if (hijo.cota_local > cota_global){
                        vivos.push(hijo);
                    }
                    else
                        n_podas++;
                }
            }

        }
        else
            n_podas++;
    }while(!vivos.empty());
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
    generapermutaciones(n,a);

    cout << "\nLa conveniencia optima de la asignacion es: ";
    cout << calculaconveniencia(optimo) << endl;
    cout << endl;
    
    //Vector asignacion resultado
    cout << "\nVector resultado optimo: ";
    for(int i = 0; i < n; i++)
        cout << optimo[i] << " ";
    cout << endl;
    
    solucionBB(n, a);
    cout << "\nVector resultado B&B: ";
    for(int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
    //Calcula la conveniencia total de la asignacion dada
    cout << "\nLa conveniencia del algoritmo B&B asignacion es: ";
    cout << calculaconveniencia(a) << endl;

    cout << "El numero de nodos expandidos son: " << n_expandidos << endl;
    cout << "El numero de nodos podados son: " << n_podas << endl;
    
    return 0;
}

