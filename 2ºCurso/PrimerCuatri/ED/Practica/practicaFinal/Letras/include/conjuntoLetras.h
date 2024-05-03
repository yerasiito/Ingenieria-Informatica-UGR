#ifndef __conjunto_letras_h__
#define __conjunto_letras_h__

#include <iostream>
#include <set>

#include "letra.h"
#include "diccionario.h"

using namespace std;

/**
* @file conjuntoLetras.h
* @brief T.D.A Clase ConjuntoLetras que gestiona los archivos letra.txt
* @author Yeray López Ramírez
* @author Jaime Castillo Ucles
* @date Diciembre 2021
*/
class conjuntoLetras{
private:
    set<Letra> Letras;
public:

    static const string formato; //La cabecera del archivo

    /**
     * @brief Constructor por defecto
     */
    conjuntoLetras() = default;

    /**
    * @brief Devuelve el numero de letras que hay en el set<Letra>
    * @return El numero de letras
    */
    int tama() const;

    /**
    * @brief Devuelve el set de letras
    * @return set<Letra> con las letras del conjunto
    */
    set<Letra> getLetras() const;

    /**
    * @brief Añade una Letra al set de letras
    * @param Letra La Letra a añadir
    */
    void aniadeLetra(const Letra &Letra);

    /**
    * @brief Elimina una letra del set de letras
    * @param Letra La Letra a eliminar
    */
    void quitaLetra(const Letra &Letra);

    /**
    * @brief Devuelve una Letra del conjunto de letras
    * @param i Posicion de la letra
    * @return la Letra del conjunto
    */
    Letra getLetra(const int &i) const;


    /**
    * @brief Devuelve una Letra del set de Letras
    * @param c Caracter con el que buscar la letra
    * @return una Letra del set
    */
    Letra getLetra(const char & c) const;


    /**
    * @brief Comprobar si una letra pertenece al set de letras
    * @param letra Letra a comprobar
    * @return true si la encuentra, false en otro caso
    */
    bool Esta(const Letra &Letra) const;


    /**
    * @brief Calcula la puntuacion de una palabra, dado un modo de juego
    * @param palabra Palabra a calcular la puntuacion
    * @param modo Mode de juego
    * @return la puntuación de la palabra
    */
    int PuntuacionPalabra(const string palabra, const char & modo) const;


    /**
    * @brief Devuelve el total de las frecuencias de todas las letras del conjunto
    * @return la frecuencia total de letras
    */
    int frecuenciaTotal() const;

    /**
    * @brief Cuenta las letras del diccinario pasado por parámetro
    * @param d Diccionario a contar
    * @return un objeto conjuntoLetras con la frecuencia de las letras
    */
    conjuntoLetras contarLetras(const Diccionario &d);

    /**
    * @brief Lee de un flujo de entrada
    * @param is flujo de entrada
    * @param conjunto el objeto a ser leído
    * @return el flujo de entrada
    **/
    friend istream & operator>> (istream &is, conjuntoLetras &conjunto);

    /**
    * @brief Escribe en un flujo de salida el conjunto de Letras
    * @param os flujo de salida
    * @param conjunto el objeto conjunto a escribir
    * @return el flujo de salida
    **/
    friend ostream & operator <<(ostream &os, const conjuntoLetras &conjunto);

    class iterator {
    private:
        set<Letra>::iterator it;
    public:
        /**
        * @brief Constructor por defecto, crea un iterator vacio
        */
        iterator() = default;

        /**
        * @brief Operador de acceso *
        * @return string Objeto al que apunta el iterador
        *
        */
        Letra operator* ();

        /**
        * @brief Operador ++, avanza en una posicion el iterador constante
        * @return iterator Iterados actual
        */
        iterator & operator++ ();

        /**
        * @brief Operador ==, comprueba si un operador es igual a otro
        * @param i Iterador a comparar con el iterador implicito
        * @return bool Resultado de la comprobacion, true si se cumple, false si no
        */
        bool operator==(const iterator &i);

        /**
        * @brief Operador !=, comprueba si un operador es distinto a otro
        * @param i Iterador a comparar con el iterador implicito
        * @return bool Resultado de la comprobacion, true si se cumple, false si no
        */
        bool operator !=(const iterator &i);

        friend class conjuntoLetras;
		};

    /**
    * @brief Devuelve un iterador del TDA iterator, que apunta al inicio de la lista de palabras
    * @return iterator Iterador que apunta al inicio de la lista_palabras
    */
    iterator begin();

    /**
    * @brief Devuelve un iterador del TDA iterator, que apunta al fin de la lista de palabras
    * @return iterator Iterador que apunta al fin de la lista_palabras
    */
    iterator end();

    /**
    * @brief Devuelve un iterador del TDA iterator, que apunta al inicio de la lista de palabras
    * @return iterator Iterador que apunta al inicio de la lista_palabras
    */
    iterator begin() const;

    /**
    * @brief Devuelve un iterador del TDA iterator, que apunta al fin de la lista de palabras
    * @return iterator Iterador que apunta al fin de la lista_palabras
    */
    iterator end() const;
};

#endif
