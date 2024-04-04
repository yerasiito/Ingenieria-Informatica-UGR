#ifndef __BOARD_H__
#define __BOARD_H__

# include <vector>
# include <map>
# include "Attributes.h"

using namespace std;

/**
 * @brief Enumerado para definir distintas configuraciones de tableros.
 * 
 */
enum BoardConfig{
    ALL_AT_HOME, // Todas las fichas comienzan en su casa.
    GROUPED,     // Una ficha comienza en la casa, las otras tres ocupan los tres primeros seguros de su color.
    ALTERNED,    // Una ficha de cada color comienza en la casa, el resto se van colocando en los seguros alternando los colores. 
    ALMOST_GOAL, // Todas las fichas comienzan en el pasillo de la meta (sin utilidad real, solo para facilitar depuración).
    DEBUG,       // Para depurar determinadas situaciones (ir mofdificando según necesidad)v
};


class Board{
    private:
        //Conjunto de todas las piezas del tablero
        //Se usa como identificador el color, y después un vector con las casillas en las que 
        //está cada una de las 4 piezas.
        map<color, vector<Box> > pieces;

    public:
        /**
         * @brief Constructor por defecto
         * 
         */
        Board();

        /**
         * @brief Constructor a partir de un objeto Board.
         * 
         * @param d 
         */
        Board (const map <color, vector <Box> > & b);

        /**
         * @brief Construye un nuevo tablero a partir de la configuración indicada.
         * 
         */
        Board(const BoardConfig & config);

        /**
         * @brief Sobrecarga del operador de igualdad.
         * 
         * @param board 
         * @return true 
         * @return false 
         */
        bool operator==(const Board & board) const;

        /**
         * @brief Función que devuelve el Box correspondiente a la ficha 
         * en la posición "idx" del vector de fichas de color "c".
         * 
         * @param c 
         * @param idx 
         * @return Box 
         */
        const Box & getPiece(const color c, const int idx) const;

        /**
         * @brief Función que devuelve el vector de Box del color "c".
         * 
         * @param c 
         * @return Box 
         */
        const vector<Box> & getPieces(const color c) const;

        /**
         * @brief Función que mueve la ficha de la posición "idx" del vector 
         * de fichas de color "c" al box "final_box".
         * 
         * @param c 
         * @param idx 
         * @param final_box 
         */
        void movePiece(const color c, const int idx, const Box & final_box);

        /**
         * @brief Actualiza el tablero según la configuración especificada.
         * 
         * @param config 
         */
        void setFromConfig(const BoardConfig & config);
};


#endif