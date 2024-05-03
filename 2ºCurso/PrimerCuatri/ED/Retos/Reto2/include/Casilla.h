/**
  * @file Casilla.h
  * @brief Fichero cabecera de la clase @c Casilla
  * @author López Ramírez, Yeray
  * @date 28 de Octubre de 2021
  *
  */

#ifndef CASILLA_H
#define CASILLA_H

#include "BloquesSudoku.h"

/**
 * @brief Casilla
 * Una clase que contiene los datos básicos de una casilla del sudoku, a partir
 * de una matriz sudoku proporcionada por la clase SudokuKiller
 */
class Casilla 
{
private:
    int fila, columna, valor; 

public:

    /**
     * @brief Constructor por defecto
     */
    Casilla();

    /**
     * @brief Constructor con parametros
     * @param fil : int
     * @param col : int
     */
    Casilla(int fil, int col);
     
    /**
     * @brief Constructor con parametros
     * @param fil : int
     * @param col : int
     * @param valor : int
     * @pre valor>0 && valor<10
     */
    Casilla(int fil, int col, int valor);
    /**
     * @brief Detecta pares invalidos
     * @return Devuelve true cuando sus parametros son -1, y falso en otro caso
     */
    bool isEmpty() const;
    
    /**
     * @brief Obtiene la fila
     * @return La fila de la casilla
     */
    const int getFila() const;

    /**
     * @brief Obtiene la columna
     * @return  La columna de la casilla
     */
    const int getColumna() const;
    
    /**
     * @brief Obtiene el valor de la casilla
     * @return El valor
     */
    const int getValor() const;
 
    /**
     * @brief Modifica el valor de la fila al valor dado
     * @param fil : int
     */
    void setFila(const int fil);

    /**
     * @brief Modifica el valor de la columna al valor dado
     * @param col : int
     */
    void setColumna(const int col);
    
    /**
     * @brief Modifica el valor de la casilla al valor dado
     * @param valor : int
     */
    void setValor(const int valor);

    /**
     * @brief Modifica la fila y columna
     * @param fil : int
     * @param col : int
     */
    void setPosicion(int fil, int col);
    
    /**
     * @brief modifica todos los valores propios de una casilla
     * @param fil : int
     * @param col : int
     * @param valor : int
     * @pre valor>0 && valor<10
     */
    void setCasilla(int fil, int col, int valor);

    /**
     * @brief Convierte el objeto Casilla en un string
     * @return un string en el formato -> Fila: fil , Columna; col , Valor: val
     */
    std::string to_string() const;

    /**
     * @brief Establece el par por defecto. Filas, columnas, valor == -1
     */
    void initDefault();
  
};

/**
 * @brief comprueba que dos casillas son iguales
 * @param izq : Casilla
 * @param dcha : Casilla
 * @return true cuando sus posiciones son iguales, false en otro caso
 */
bool mismaCasilla(const Casilla & izq, const Casilla & dcha);

#endif /* CASILLA_H */

