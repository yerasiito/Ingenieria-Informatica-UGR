/**
 * @file BloquesSudoku.h
 * @brief Fichero cabecera de las clases @c Bloque y @c BloquesSudoku
 * @author López Ramírez, Yeray
 * @date Octubre 2021
 */

#ifndef BLOQUESSUDOKU_H
#define BLOQUESSUDOKU_H

#include <iostream>
#include <vector>
#include "Casilla.h"

#define TAMA_MAX = 5

using namespace std;

/**
 * @brief Bloque
 * Una clase que agrupa las casillas de una Matriz, se utiliza en la clase
 *  BloquesSudoku para la clase SudokuKiller
 */
class Bloque{
    private:
        int tama, suma; //tamaño de bloque y la suma de sus valores
        vector<pair> casillas; //vector de pares de posiciones de casillas(fil, col)
    
    public:
        
        /**
         * @brief Constructor por defecto
         */
        Bloque();
        
        /**
         * @brief Constructor con parametros
         * @param tam : int, Tamaño del bloque
         */
        Bloque(int tam);
        
        /**
         * @brief Constructor de copia
         * @param b : Bloque, El bloque a copiar
         */
        Bloque(const Bloque &b);
        
        /**
         * @brief Obtiene el tamaño del bloque
         * @return el tamaño del bloque
         */
        int getTamanio();
        
        /**
         * @brief Obtiene la suma de los valores bloque, llama a sumaValores
         * @return la suma del valor en las casillas del bloque
         */
        int getSumaBloque();
        
        /**
         * @brief Obtiene un objeto Casilla
         * @param i : int, posición de la casilla en el vector
         * @return el objeto Casilla
         */
        Casilla getCasilla(int i);
        
        /**
         * @brief Establece los parametros de una casilla
         * @param i : int, Posicion de la casilla a modificar
         * @param fil : int, La posicion en la fila de la casilla
         * @param col : int, La posicion en la columna de la casilla
         * @param val : int, El valor de la casilla
         */
        void setCasilla(int i, int fil, int col, int val);
        
        /**
         * @brief Añade una nueva casilla al bloque, tama++
         * @param val : int, El valor de la casilla
         * @param fil : int, La posicion en la fila de la casilla
         * @param col : int, La posicion en la columna de la casilla
         * @return true si es añadida, false en otro caso
         * @pre val != null && val > 0 && val < 0
         * @pre tama < TAMA_MAX
         * @pre esCasillaContigua==true
         */
        bool aniadirCasilla(int val, int fil, int col);
        
        /**
         * @brief Elimina la casilla del bloque
         * @param i : int, Posicion de la casilla a eliminar
         * @return true si se elimina correctamente, false en otro caso
         * @pre i < tama && i >= 0
         */
        bool eliminarCasilla(int i);
        
        /**
         * @brief Comprueba que la nueva casilla sea contigua a alguna existente
         * en el bloque
         * @param nueva : Casilla, La casilla a comprobar
         * @pre Si tama==0, devuelve true
         * @return true si la casilla es contigua, false en otro caso
         */
        bool esCasillaContigua(Casilla nueva);
        
        /**
         * @brief Suma los valores de las casillas del bloque y modifica el
         * atributo suma
         */
        void sumaValores();
        
        
};

/**
 * @brief BloquesSudoku
 * Una clase que contiene los bloques del Sudoku, se utiliza para la clase 
 * SudokuKiller y ResolverSudokuKiller
 */
class BloquesSudoku{
    private:
        int numBloques;
        vector<Bloque> BloquesSudoku; //vector de bloques
    public:
        
        /**
         * @brief Constructor por defecto
         */
        BloquesSudoku();
        
        /**
         * @brief Constructor con parametros
         * @param num : int, Numero de bloques a crear
         */
        BloquesSudoku(int num);
        
        /**
         * @brief Obtiene un objeto Bloque del vector de objetos de BloquesSudoku
         * @param i : int, Posicion del objeto a obtener en el vector
         * @return un objeto Bloque
         */
        Bloque getBloquesSudoku(int i);
        
        /**
         * @brief Modifica un bloque a partir de otro
         * @param i : int, La posicion del bloque a modificar
         * @param b : Bloque, El bloque de copia
         */
        void setBloquesSudoku(int i, Bloque b);
        
        /**
         * @brief Modifica un bloque a partir de un vector de casillas
         * @param i : int, La posicion del bloque a modificar
         * @param <Casilla> : Vector, Las casillas a copiar
         */
        void setBloquesSudoku(int i, vector<Casilla>);
        
        /**
         * @brief Añade un bloque al vector de BloquesSudoku
         * @param b : Bloque, El bloque a añadir
         * @return true si se inserta correctamente, false en otro caso
         */
        bool aniadirBloque(Bloque b);
        
        /**
         * @brief elimina un bloque del vector
         * @param i : int, Posicion del bloque a eliminar
         * @return true si se borra correctamente, false en otro caso
         */
        bool eliminarBloque(int i);
        
        /**
         * @brief Calcula el total de los atributos suma de los bloques pedidos
         * @param ibloques : vector<int>, Posiciones de los bloques a calcular
         * @return la suma total de los bloques dados
         */
        int sumaBloques(vector<int> ibloques);
        
    
};

/**
 * @brief Comprueba que 2 bloques no se solapan
 * @param izq
 * @param dcha
 * @return true si alguna casilla coincide, false en otro caso
 */
bool seSolapaBloques(Bloque izq, Bloque dcha);

/**
 * @brief Compara si 2 bloques son iguales
 * @param izq
 * @param dcha
 * @return true cuando las casillas que lo formas son iguales, false en otro caso
 */
bool esMismoBloque(Bloque izq, Bloque dcha);

    
#endif /* BLOQUESSUDOKU_H */

