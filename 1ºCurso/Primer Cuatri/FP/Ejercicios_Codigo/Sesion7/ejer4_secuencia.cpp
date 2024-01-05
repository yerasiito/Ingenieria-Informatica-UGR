//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

int main(){
    int computo=0,util=0,i=0,j=0,solucion;
    int pos=0; /*Inicializamos a 0 para comparar al final si no ha sido modificado e imprimir que "no hay solucion" */

    //Introduciion de datos
    cout << "Introduce el valor de util: ";
    cin >> util;
    int v[util];

    cout << "Introduce el vector: ";
    for (i=0;i<util;i++){
        cin >> v[i];
    }
    i=0;

    cout << "Inserte el solucion: ";
    cin >> solucion;

    //Cómputo
    for (i=0;i<util;i++){
        for (j=i;j<util;j++){
            computo=computo+v[j];
            if(computo == solucion){
                pos=i;
            }
        }
        computo=0;
    }
   if(pos>0)
      cout << pos+1 << endl; /*El mas 1 es para que la posicion a imprimir sea logica*/
   else
      cout << "No hay solucion" << endl;
}
