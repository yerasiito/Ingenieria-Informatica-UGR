/**
 * 
 * @file SudokuKiller.h
 * @brief Fichero cabecera de la clase @c SudokuKiller
 * @author López Ramírez, Yeray
 * @date Octubre 2021
 */

#ifndef SUDOKUKILLER_H
#define SUDOKUKILLER_H

#include <iostream>
#include <vector>
#include "Matriz.h"

using namespace std;

/**
 * @brief Sudoku
 * Clase basica del cual se creará la version killer del sudoku
 */
class Sudoku
{
    private:
        Matriz sudoku();
        BloquesSudoku cajas;
        
        /**
         * @brief Inicializa los valores del sudoku, por defecto Matriz(9); 
         */
        void init();
    public:
        /**
         * @brief Constructor por defecto. Genera un sudoku aleatorio con el
         * metodo GenerarSudoku.
         */
        Sudoku();
        
        /**
         * @brief Constructor con parámetros
         * @param m : Matriz, La matriz a partir se crea el sudoku, se verifica
         * con el metodo SudokuValido
         */
        Sudoku(Matriz m);
        
        /**
         * @brief Obtiene el valor en la casilla dada
         * @param fil : int, Posicion en la fila
         * @param col : int, Posicion en la columna
         * @return El valor de la casilla
         */
        int getValorCasilla(int fil, int col);
        
        /**
         * @brief Devuelve la matriz sudoku
         * @return 
         */
        Matriz getSudoku();
        
        
        /**
         * @brief Genera un sudoku normal terminado a partir de un algoritmo aleatorio y
         * llama a SudokuValido para comprobar si es correcto
         * @return La matriz Sudoku generada
         */
        Matriz GenerarSudoku();
    
};
    /**
     * @brief SudokuKiller
     * Una clase para crear y gestionar el sudoku killer completo, se utiliza
     *  la clase Matriz y la utiliza ResolverSudokuKiller
     */
    class SudokuKiller{
        private:
            Matriz sudokuKiller;
            BloquesSudoku cajas;
            BloquesSudoku bloquesKiller;
                
        /**
         * @brief Apartir de un sudoku NORMAL ya terminado, generamos los bloqueskiller
         * @param sudoku : Matriz, La Matriz de donde creamos los bloqueskiller
         */
        void GenerarSudokuKillerCompleto(Sudoku sudoku);
        
        public:
            /**
             * @brief Constructor por defecto, llama a Generarsudoku de la clase
             * Sudoku y lo devuelve como parametro a GenerarSudokuKillerCompleto
             */
            SudokuKiller();
            
            /**
             * @brief Constructor con parametros. Crea un sudoku nuevo a partir
             * de la matriz dada y llama al siguiente constructor.
             * Si es incorrecta, se llama al constructor por defecto
             * @param sudoku : Matriz 
             */
            SudokuKiller(Matriz sudoku);
            
            /**
             * @brief Constructor con parametros, llama al metodo GenerarSudokuKillerCompleto
             * @param sudoku : Sudoku
             */
            SudokuKiller(Sudoku sudoku);

            /**
             * @brief Devuelve un objeto SudokuKiller vacio listo para jugar. 
             * Usa el metodo GenerarSudokuKillerCompleto, copia el objeto e inicializa
             * sus valores a null para el jugador.
             */
            SudokuKiller GenerarSudokiller();

            /**
             * @brief Verifica si el sudoku dado está completo y cumple las reglas
             * para considerarse resuelto
             * @param resuelto : SudokuKiller, El sudoku a comprobar
             * @return true si está completamente resuelto, false en otro caso
             */
            bool EstaResuelto(SudokuKiller resuelto);
    };

    /**
     * @brief Comprueba que la matriz dada cumple las reglas del sudoku
     * @return true si los valores cumplen las reglas del sudoku, false en otro caso
     * -No se repiten numeros de la misma fila o columna o caja(3x3)
     */
    bool SudokuValido(Matriz M);
    
    /**
     * @brief verifica que los numeros de la matriz sudoku coinciden con el valor
     * suma de los bloques killer
     * @param sudoku : SudokuKiller, 
     * @return true si suma==sumaValores(), false en otro caso
     */
    bool BloquesValido(SudokuKiller sudoku);
    
    /**
     * @brief Verifica que el sudoku dado es un killer y que todo está correcto
     * @param sudoku : SudokuKiller, El sudoku a verificar
     * @return true si cumple las condiciones del killer y los metodos SudokuValido
     * y Bloques valido dan true, false en otro caso
     */
    bool SudokuKillerValido(SudokuKiller sudoku);

#endif /* SUDOKUKILLER_H */

