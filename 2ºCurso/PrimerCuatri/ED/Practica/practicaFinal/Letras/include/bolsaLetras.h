#ifndef __BOLSA_LETRAS_H__
#define __BOLSA_LETRAS_H__

#include <unordered_set>
#include <sstream>
#include <iterator> //funcion advance

#include "letra.h"
#include "conjuntoLetras.h"
#include "diccionario.h"

/**
  * @file bolsaLetras.h
  * @brief T.D.A. bolsaLetras
  * @author Yeray Lopez Ramirez
  * @author Jaime Castillo Ucles
  * @date Diciembre 2021
  */
class bolsaLetras{
	private:
		unordered_multiset<char> bolsa;

	public:
		/**
		 * @brief Constructor por defecto
		 */
		bolsaLetras() = default;

		/**
		 * @brief Constructor de copia.
		 * @param otra bolsaLetras a copiar
		 */
		bolsaLetras(const bolsaLetras & otra);

		/**
		 * @brief Constructor por parámetros.
		 * @param c conjunto de letras con el que llenar la bolsa
		 */
		bolsaLetras(const conjuntoLetras & c);

		/**
		 * @brief Devuelve el numero de letras en la bolsa
		 */
		int tama() const;

		/**
		 * @brief Devuelve la bolsa
		 * @return unordered_multiset<char> Bolsa de letras
		 */
		unordered_multiset<char> getBolsa();

		/**
		 * @brief Añade un Objeto Letra a la bolsa
		 * @param L Letra a añadir (a partir de un objeto del TDA Letra)
		 */
		void aniadeLetra(const Letra & L);

		/**
		 * @brief Añadir una letra a la bolsa
		 * @param L Letra a añadir (a partir de un caracter)
		 */
		void aniadeLetra(const char & l);

		/**
		 * @brief Elimina un Objeto Letra de la bolsa de letras
		 * @param L Letra a eliminar (a partir de un objeto del TDA Letra)
		 */
		void quitaLetra(const Letra & L, bool todas);

		/**
		 * @brief Elimina una letra de la bolsa de letras
		 * @param L letra a eliminar (a partir de un caracter)
		 */
		void quitaLetra(const char & l, bool todas);

		/**
		 * @brief Devuelve una bolsa con un "num" de letras aleatorias de la bolsa actual
		 * @param num Tamaño de la bolsa a obtener
		 * @return bolsaLetras con "num" de letras aleatorias
		 */
		bolsaLetras getLetras(int num);

		/**
		 * @brief Obtiene todas las soluciones de la bolsa:
         * Devuelve todas las palabras posibles con las letras de la bolsa y que existan en el diccionario.
         * Además obtiene su puntuación según el modo de juego
		 * @param Letras El Conjunto de Letras para obtener la puntuacion de cada palabra
		 * @param d Diccionario que contiene las palabras
		 * @param modo Modo de juego
		 * @return conjunto de pares, con la solucion, el primer elemento del
		 *  pair es la puntuacion y el segundo la palabra
		 */
		set<pair<int,string>> getSoluciones(const conjuntoLetras & Letras, const Diccionario & d, const char & modo);

		/**
		 * @brief Comprueba si un Objeto Letra dado existe
		 * @param L Objeto Letra a comprobar
		 * @bool true si existe el caracter que contiene el Objeto Letra, false en otro caso
		 */
		bool Esta(const Letra & L);

		/**
		 * @brief Comprueba si una letra dada existe
		 * @param c Caracter a comprobar
		 * @bool true si existe el carácter, false en otro caso
		 */
		bool Esta(const char & c);

		/**
		 * @brief Comprueba si una palabra se puede formar con las letras de la bolsa
		 * @param palabra La palabra a comprobar
		 * @return true si la palabra es válida según las reglas, false en otro caso
		 */
		bool palabraValida(const string palabra);

		/**
		 * @brief Lee de un flujo de entrada y lo escribe en un objeto Bolsa de Letras
		 * @param is flujo de entrada
         * @param bolsa objeto que recibe el flujo de entrada
         * @return el flujo de entrada
        **/
		friend istream & operator>> (istream &is, bolsaLetras &bolsa);

      /**
       * @brief Escribe el objeto Bolsa de Letras en un flujo de salida
       * @param os flujo de salida
       * @param bolsa el objeto bolsaLetras que se imprime
       * @return el flujo de salida
       **/
		friend ostream & operator << (ostream &os, const bolsaLetras &bolsa);

		class iterator {
        private:
            unordered_multiset<char>::const_iterator it; //el unordered_multiset usa iterador constante
        public:
				/**
				 * @brief Constructor por defecto
				 */
				iterator() = default;

				/**
				 * @brief Sobrecarga del operator*
				 * @return string Objeta Letra al que apunta el iterador
				 */
				char operator* ();

				/**
				 * @brief Sobrecarga del operator++
				 * @return el iterador apuntando a la siguiente posición
				 */
				iterator & operator ++ ();

				/**
				 * @brief Sobrecarga del operator==
				 * @param i El iterador a comparar con el actual
				 * @return true si los iteratores son iguales, false si no lo son
				 */
				bool operator ==(const iterator &i);

				/**
				 * @brief Sobrecarga del operator!=
				 * @param i El iterador a comparar con el actual
                 * @return true si los iteratores no son iguales, false si lo son
				 */
				bool operator !=(const iterator &i);

				friend class bolsaLetras;
		};

		/**
		 * @brief Devuelve el iterador apuntando al inicio de la bolsa
		 * @return iterador apuntando al inicio
		 */
		iterator begin();

		/**
		 * @brief Devuelve el iterador apuntando al inicio de la bolsa
		 * @return iterador apuntando al inicio
		 */
		iterator begin() const;

		/**
		 * @brief Devuelve el iterador apuntando al final de la bolsa
		 * @return iterador apuntando al final
		 */
		iterator end();

		/**
		 * @brief Devuelve el iterador apuntando al final de la bolsa
		 * @return iterador apuntando al final
		 */
		iterator end() const;

};

#endif
