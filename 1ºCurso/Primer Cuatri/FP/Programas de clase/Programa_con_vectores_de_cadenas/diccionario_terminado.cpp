/**
  * @file diccionario.cpp
  * @brief Programa para listar un diccionario tras barajar
  *
  * @author Don Oreo
  * @date Diciembre-2020
  *
  * El programa es un ejemplo de uso de string y vectores-C con numeros aleatorios
  *
  * El programa no usara el tipo vector de char, aunque si el vector-C con objetos de
  * tipo string. Debera crear un vector con el siguiente contenido:
  *       "caballero",  "Dulcinea",   "historia",   "escudero",
  *       "rocinante",  "adelante",   "gobernador", "andantes",
  *       "voluntad",   "capitulo",   "menester",   "doncella",
  *       "caballeria", "castillo",   "Fernando",   "finalmente",
  *       "aventura",   "hermosura",  "palabras",   "gobierno",
  *       "intencion",  "cardenio",   "pensamientos", "Luscinda",
  *       "lagrimas",   "aposento",   "aventuras",  "quisiera",
  *       "libertad",   "desgracia",  "entendimiento", "pensamiento",
  *       "licencia",   "Mercedes",   "semejantes", "silencio",
  *       "valeroso",   "doncellas",  "labrador",   "caballerias",
  *       "cristiano",  "cristianos", "discreto",   "hicieron",
  *       "llegaron",   "quisiere",   "espaldas",   "muestras",
  *       "escuderos",  "discurso",   "grandeza",   "altisidora",
  *       "princesa",   "haciendo",   "renegado",   "provecho",
  *       "quedaron",   "resolucion", "presente",   "encantadores",
  *       "enamorado",  "valiente",   "encantado",  "molino",
  *       "licenciado", "necesidad",  "responder",  "discrecion",
  *       "ejercicio",  "hacienda",   "posadero",   "rocinante",
  *       "presencia",  "historias",  "presentes",  "verdadero"
  *
  * A continuacion, debera barajar las entradas del vector. Para ello, puede hacer tantos
  * intercambios como palabras tiene el diccionario. Un intercambio consiste en seleccionar
  * dos posiciones e intercambiar los contenidos de las dos casillas del vector.
  *
  * Finalmente, tendra que listar el nuevo diccionario, con las mismas palabra pero en
  * distinto orden. Ademas, para cada palabra, debe dibujar tantos guiones como letras tenga
  * debajo. Por ejemplo, el listado puede comenzar asi:
  *       1.- caballero
  *           ---------
  *       2.- Dulcinea
  *           --------
  *       3.- valiente
  *           --------
  *       4.- valeroso
  *           --------
  *
  * y terminar:
  *       74.- licenciado
  *            ----------
  *       75.- escudero
  *            --------
  *       76.- provecho
  *            --------
  *
  */
#include <iostream>
#include<time.h>
#include<stdlib.h>
using namespace std;

int main(){
    srand(time(NULL));
    int n1,numero2,palabras=75;
    char separador = '-';
    string intercambio;
    string diccionario[palabras] = {"Dulcinea",   "historia",   "escudero",
        "rocinante",  "adelante",   "gobernador", "andantes",
        "voluntad",   "capitulo",   "menester",   "doncella",
        "caballeria", "castillo",   "Fernando",   "finalmente",
        "aventura",   "hermosura",  "palabras",   "gobierno",
        "intencion",  "cardenio",   "pensamientos", "Luscinda",
        "lagrimas",   "aposento",   "aventuras",  "quisiera",
        "libertad",   "desgracia",  "entendimiento", "pensamiento",
        "licencia",   "Mercedes",   "semejantes", "silencio",
        "valeroso",   "doncellas",  "labrador",   "caballerias",
        "cristiano",  "cristianos", "discreto",   "hicieron",
        "llegaron",   "quisiere",   "espaldas",   "muestras",
        "escuderos",  "discurso",   "grandeza",   "altisidora",
        "princesa",   "haciendo",   "renegado",   "provecho",
        "quedaron",   "resolucion", "presente",   "encantadores",
        "enamorado",  "valiente",   "encantado",  "molino",
        "licenciado", "necesidad",  "responder",  "discrecion",
        "ejercicio",  "hacienda",   "posadero",   "rocinante",
        "presencia",  "historias",  "presentes",  "verdadero"};

   palabras = sizeof(diccionario)/sizeof(string);
    for (int i=0 ; i < palabras ; i++){
        n1=rand()%palabras;
        numero2=rand()%palabras;
        intercambio=diccionario[n1];
        diccionario[n1]=diccionario[numero2];
        diccionario[numero2]=intercambio;
    }

    for (int i=0 ; i < palabras ; i++){
        int tamanio = diccionario[i].size();
        cout << i+1 << " " << diccionario[i] << endl;
        if (i+1 >= 10){
            cout << "   ";
        }
        else{
            cout << "  ";
        }
        for (int i=0 ; i < tamanio ; i++){
            cout << separador;
        }
        cout << endl;
    }
}
