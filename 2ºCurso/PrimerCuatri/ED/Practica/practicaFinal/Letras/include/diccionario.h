#ifndef _DICCIONARIO_H
#define _DICCIONARIO_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>
#include <vector>

using namespace std;

/**
* @file diccionario.h
* @brief T.D.A Clase Diccionario
* @author Yeray López Ramírez
* @author Jaime Castillo Ucles
* @date Diciembre 2021
*/
class Diccionario {
private:

	set<string> datos;

public:

    ///////////////////////////////////////////////////////////////////////////////
    // CONSTRUCTORES
    ///////////////////////////////////////////////////////////////////////////////

	/**
	 * @brief Construye un diccionario vacío
	 */
	Diccionario() = default; //Se coge el por defecto

	/**
	 * @brief Constructor de copia
	 */
	Diccionario( const Diccionario &diccionario );

    ///////////////////////////////////////////////////////////////////////////////
    //CONSULTA
    ///////////////////////////////////////////////////////////////////////////////

	/**
	 * @brief Consulta el tamaño del diccionario
	 * @return Cantidad de palabras almacenadas
	 */
	size_t size() const; //Puede ser int tb pero es mas "correcto" size_t

	/**
	 * @brief Indica si una palabra está en el diccionario o no
     * @param palabra: la palabra que se quiere buscar
	 * @return true si la palabra está en el diccionario. False en caso contrario
	 */
	bool Esta(const string & palabra) const;

	/**
	 * @brief Consulta cuántas palabras tienen dicha longitud
	 * @return Vector con dicha cantidad de palabras
	 */
	vector<string> PalabrasLongitud(const size_t longitud) const;

    ///////////////////////////////////////////////////////////////////////////////
    //MODIFICADORES
    ///////////////////////////////////////////////////////////////////////////////

	/**
	 * @brief Añade una nueva palabra al diccionario
	 * @param nueva_palabra Palabra a añadir
	 */
	void aniade(const string& nueva_palabra );

    ///////////////////////////////////////////////////////////////////////////////
    //OPERADORES
    ///////////////////////////////////////////////////////////////////////////////

	Diccionario & operator= (const Diccionario& diccionario);
	friend istream & operator>> (istream &is, Diccionario &diccionario);
	friend ostream & operator<< (ostream &os, const Diccionario &diccionario);
	friend ifstream & operator>> (ifstream &in, Diccionario &diccionario);
    ///////////////////////////////////////////////////////////////////////////////
    //ITERADORES
    ///////////////////////////////////////////////////////////////////////////////

    class iterator{
    private:
        set<string>::iterator it;
    public:

        iterator() = default; //Nada que tocar, por defecto

        string operator *(){
            return *(this->it);
        }

        iterator & operator++(){
            ++this->it;
            return *this;
        }

        bool operator ==(const iterator &i){
            return this->it == i.it;
        }

        bool operator !=(const iterator &i){
            return this->it != i.it;
        }

        friend class Diccionario;

    };

    iterator begin(){
        iterator iter;
        iter.it = datos.begin();
        return iter;
    };

    iterator end(){
        iterator iter;
        iter.it = datos.end();
        return iter;
    };

    iterator begin() const{
        iterator iter;
        iter.it = datos.begin();
        return iter;
    };

    iterator end() const{
        iterator iter;
        iter.it = datos.end();
        return iter;
    };

};

///////////////////////////////////////////////////////////////////////////////
//FUNCION EXTERNA
///////////////////////////////////////////////////////////////////////////////
/**
 * @brief Función externa para mejorar la salida.
 * Hace un salto de linea cada "intercalar" veces
 * @param c Contador con el numero de impresiones hechas
 * @param intercalar Cada cuantas impresiones se quiere dar el salto
 */
void intercalado(int c, int intercalar);

#endif
