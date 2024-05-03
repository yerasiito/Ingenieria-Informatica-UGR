/**
 * @file ResolverSudokuKiller.h
 * @brief Fichero cabecera de la clase @c ResolverSudokuKiller
 * @author López Ramírez, Yeray
 * @date Octubre 2021
 */


#ifndef RESOLVERSUDOKUKILLER_H
#define RESOLVERSUDOKUKILLER_H

#include <SudokuKiller.h>

/**
 * @brief ResolverSudokuKiller
 * Una clase que resuelve el juego del Sudoku Killer a partir de algoritmos 
 * logicos humanos, utiliza la clase SudokuKiller
 */
class ResolverSudokuKiller{
    private:
        int ***sudoku; //Matriz tridimensional ya que cada casilla contendrá un vector de posibles valores
        BloquesSudoku caja;
        BloquesSudoku bloquesKiller;
    public:
        
        /**
         * @brief Constructor por defecto
         */
        ResolverSudokuKiller();
        
        /**
         * @brief utiliza los metodos y algoritmos de la clase para resolver el sudoku dado
         * @param aResolver : Sudokukiller, El sudoku devuelto por el metodo 
         * GenerarSudokuKiller para resolverlo
         * @return el sudoku completamente resuelto
         */
        SudokuKiller ResuelveSudoku(SudokuKiller aResolver);
        
        /**
         * @brief Devuelve los posibles valores de la caja/region de 3x3 del sudoku
         * Si el vector resultante contiene un solo elemento, lo inserta automaticamente
         * @param i : int, la posicion de la caja solicitada
         * @pre i>=0 && i < caja.getTama()
         * @return Los valores posibles de la caja
         */
        vector<int> SecuenciaCaja(int i);
                
        /**
         * @brief Obtiene todos los valores posibles dentro de un bloque killer
         * a partir de la suma. Tendrá en cuenta los valores de SecuenciaCaja()
         * Si el vector resultante contiene un solo elemento, lo inserta automaticamente
         * @param i : int, La posicion del bloque dentro del vector de bloquerKiller
         * @pre i>=0 && i<bloquesKiller.getTama()
         * @return Los valores posibles en el bloque dado
         */
        vector<int> SecuenciaBloqueKiller(int i);
        
        /**
         * @brief Una Secuencia Única implica que para un bloque el numero de valores
         * es igual a su tamaño, la disposicion de los valores es desconocida.
         * Matemáticamente ciertas sumas de valores para determinados tamaños dan
         * siempre una secuencia Única. Se pueden buscar a fuerza bruta o almacenarlas en una lista
         * Escribe los valores posibles en las casillas
         */
        void BuscaSecuenciasUnicas();
        
        /**
         * @brief Comprueba si existen cajas, filas o columnas que contengan
         * bloques killer completos excepto una casilla, cuyo valor se calcula
         * 45*numero de caja,fila,columa - la suma de los bloques killer(metodo sumaBloques)
         */
        void Regla45();
        
        /**
         * @brief Descarta las combinaciones de numeros que contengan un numero
         * que ya existe en la caja,fila,columna o bloque killer. Regla basica de sudoku
         * @param i
         */
        void DescartaSecuencias(int i);
        
        /**
         * @brief Calcula las combinaciones posibles de numeros para un valor concreto
         * y un tamanio de bloque
         * @param valor : int, El valor total de la secuencia
         * @param tama : int, El tamaño de la secuencia
         * @return las posibles combinaciones para un total y tamaño
         */
        vector<int> SecuenciasPosibles(int valor, int tama);
    
};


#endif /* RESOLVERSUDOKUKILLER_H */

