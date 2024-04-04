#ifndef __DICE_H__
#define __DICE_H__

# include <vector>
# include <map>
# include "Attributes.h"

using namespace std;

class Dice{
    private:
        /**
         * @brief Dados para cada jugador. Los dados se agrupan por capas.
         * La primera capa contiene los dados clásicos del 1-6.
         * Se pueden añadir nuevas capas para forzar valores especiales,
         * como mover 10 o 20.
         * 
         */
        map <color, vector<vector <int>> > dice;        
    
    public:
        /**
         * @brief Constructor por defecto de un nuevo objeto Dice
         * 
         */
        Dice();

        /**
         * @brief Constructor de un nuevo objeto Dice
         * 
         * @param d 
         */
        Dice (const map <color, vector<vector <int> >> & d);

        /**
         * @brief Devuelve el dado para un cierto jugador "player".
         * 
         * @param player 
         * @return const vector<int>& 
         */
        const vector<int> & getDice (color player) const;

        /**
         * @brief Devuelve los dados de todas las capas de un jugador.
         * 
         * @param player 
         * @return const vector<vector<int>>& 
         */
        const vector<vector<int>> & getAllDiceLayers(color player) const;

        /**
         * @brief Devuelve el tamaño de las capas de los dados de un jugador.
         * 
         * @param player 
         * @return const vector<vector<int>>& 
         */
        const int getLayersSize(color player) const;

        /**
         * @brief Elimina el número "n" del dado del jugador "player".
         * 
         * @param player 
         * @param n 
         */
        void removeNumber (color player, int n);

        /**
         * @brief Resetear el dado del jugador "player" por el dado "new_dice". Default <1,2,3,4,5,6>.
         * 
         * @param player 
         * @param new_dice, por defecto {1,2,3,4,5,6}
         */
        void resetDice (color player , const vector<int> & new_dice = {1,2,3,4,5,6});

        /**
         * @brief Función que comprueba si el número "n" está en el dado del jugador "player".
         * 
         * @param player 
         * @param n 
         * @return true 
         * @return false 
         */
        bool isAvailable(color player, int n) const;

        /**
         * @brief Función que añade un valor al dado del jugador "player".
         * 
         */
        void addNumber(color player, int n);

        /**
         * @brief Fuerza que el próximo número de dado del jugador "player" sea (únicamente) "n".
         * 
         * @param player 
         * @return int 
         */
        void forceNumber(color player, int n);
};

#endif