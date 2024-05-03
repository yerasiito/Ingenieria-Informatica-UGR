/**
 * @file main.cpp
 * @brief Fichero main.cpp
 * @author López Ramírez, Yeray
 * @author Castillo Ucles, Jaime
 * @date Octubre 2021
 */

/**
 * @brief To implement by the programmer
 */
#include <iostream>
#include <ResolverSudokuKiller.h>
using namespace std;


/**
 * @brief Pseudo main de ejemplo para resolver un sudokuKiller
 * @param argc Numero de argumentos pasados al main
 * @param argv Cadenas de string que representan los argumentos
 * @return 
 */
int main(int argc, char** argv) {
    /*******************/
    SudokuKiller aux;
    
    //1 - Crea un nuevo sudokukiller aleatorio
    SudokuKiller nuevo;
    //2 - Genera una version sin resolver del sudokukiller anterior y se la pasa a ResolverSudokukiller
    ResolverSudokuKiller aResolver(nuevo.GenerarSudokiller());
    //3 - Intenta resolverlo
    aux = aResolver.ResuelveSudoku();
    //4 - Comprueba que la matriz "resuelta" lo está realmente
    nuevo.EstaResuelto(aux);
    
    //Extras. Imprimir el sudoku etc etc
    
    
    /*******************/
}