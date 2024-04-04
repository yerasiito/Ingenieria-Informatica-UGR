/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
//package burbujajava;

/**
 *
 * @author manupc
 */
public class BurbujaJava {


    public static void Burbuja (double [] v, int posini, int posfin) {

        int i, j;
        double aux;
        boolean haycambios= true;

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
    
    public static void main(String[] args) {

        final int SIZE= 20000;
        double []vect= new double[SIZE];
        long tini, tfin;

        for (int TAM= 1000; TAM<=SIZE; TAM+= 1000) {

            // Ejemplo: Vector al revés
            for (int i= 0; i<TAM; i++) 
                vect[i]= TAM-i;

            tini= System.currentTimeMillis(); // Tiempo inicial
            Burbuja(vect, 0, TAM-1);
            tfin= System.currentTimeMillis(); // Tiempo final

            System.out.println("N: "+TAM+" T (ms): "+(tfin-tini));
        }
    }
    
}
