#include <iostream>
#include <ctime>
using namespace std;


void Burbuja(double *v, int posini, int posfin) {

    int i, j;
    double aux;
    bool haycambios= true;

    i= posini;
    while (haycambios) {

        haycambios=false; // Suponemos vector ya ordenado

        // Recorremos vector de final a i
        for (j= posfin; j>i; j--) {

            // Dos elementos consecutivos mal ordenados
            if (v[j-1]>v[j]) {
                aux= v[j]; // Los intercambiamos
                v[j]= v[j-1];
                v[j-1]= aux;

                // Al intercambiar, hay cambio
                haycambios= true;
            }
        }

        i++;
	}
}


int main()
{
    const int SIZE= 20000;
    double vect[SIZE];
    unsigned long tini, tfin;

    for (int TAM= 1000; TAM<=SIZE; TAM+= 1000) {

        // Ejemplo: Vector al revés
        for (int i= 0; i<TAM; i++)
            vect[i]= TAM-i;

        tini= clock(); // Tiempo inicial
        Burbuja(vect, 0, TAM-1);
        tfin= clock(); // Tiempo final

        cout<<"N: "<<TAM<<" T (ms.): "<<1000.0*(tfin-tini)/(double)CLOCKS_PER_SEC<<endl;
    }
    return 0;
}
