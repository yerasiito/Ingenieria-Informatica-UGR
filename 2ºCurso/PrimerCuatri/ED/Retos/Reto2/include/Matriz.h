/**
  * @file Matriz.h
  * @brief Fichero cabecera de la clase @c Matriz
  * @author estudiante1: López Ramírez, Yeray
  * @date 28 de Octubre de 2021
  *
  */

#ifndef MATRIZ_H
#define MATRIZ_H
#include <iostream>

using namespace std;


/**
 * @brief Matriz
 * Un template para el tipo de datos abstracto Matriz, se utiliza para las 
 * clases BloquesSudoku, SudokuKiller y ResolverSudokuKiller
 */
template <class M>
class Matriz
{
    private:
        M **matriz;
        int filas, columnas;
        
        /**
         * @brief Inicializa los valores de la matriz a 0
         */
        void init();
    
    public:
        
        /**
         * @brief Constructor sin parametros
         */
        
        Matriz();
        
        /**
         * @brief Constructor de dos parámetros: filas y columnas
         * @param f : int, Numero de filas
         * @param c : int, Numero de columnas
         * @pre f > 0 && f != null
         * @pre c > 0 && c != null
         */
        Matriz(int f, int c);
        
        /**
         * @brief Destructor de la clase Matriz
         */
        ~Matriz();
        
        /**
         * @brief Obtiene el valor que almacena la matriz en la fila y columna
         * que se pasan como parametro
         * @param f : int, Numero de filas
         * @param c : int, Numero de columnas
         * @pre fil > 0 && fil != null
         * @pre col > 0 && col != null
         * @return La casilla en la fila y columana dadas
         */
        int getCasilla(int fil, int col);
        
        /**
         * @brief Obtiene el numero de filas
         * @return El numero de filas de la Matriz
         */
        int getFila();
        
        /**
         * @brief Obtiene el numero de columnas
         * @return El numero de columnas de la Matriz
         */
        int getColumna();
        
        /**
         * @brief Inserta un nuevo valor en una casilla de la Matriz
         * @param fil : int, Posicion de la fila
         * @param col : int, Posicion de la columna
         * @param valor : M, El valor que queremos insertar
         * @pre fil > 0 && fil < filas
         * @pre col > 0 && col < columnas
         * @pre valor != null
         */
        void insertarValor(int fil, int col, const M &valor);
        
        /**
         * @brief Borrar un valor dentro de la matriz
         * @param f : int Posicion de la fila
         * @param c : int Posicion de la columna
         * @pre fil > 0 && fil < filas
         * @pre col > 0 && col < columnas
         */
        void eliminarValor(int fil, int col);
        
};

#endif /* MATRIZ_H */