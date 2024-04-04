#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;
const int n = 7, capacidad = 20;
int p[n]/* ={3, 4, 6} */, b[n]/* ={7, 8, 11} */, max_obj[n];
int Mochila(int i, int d, int w,int sol[], vector<vector<int>> mej){
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
        resultado = Mochila(i, d+1, w, sol, mej);
    }else{
        // Se calcula el beneficio máximo cogiendo o no cogiendo el objeto
        int aux[n], aux2[n];
        for (int i = 0; i < n; i++){
            aux[i]=aux2[i]=0;
        }
        cogiendo=b[i] + Mochila(i, d+1, w-p[i], aux, mej);
        sin_coger=Mochila(i, d+1, w, aux2, mej);
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
    int sol[n];
    srand(time(0));
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
    
    int max=Mochila(0, 0, capacidad, sol, ben);
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
    cout << endl;
}