#ifndef __GUI_PLAYER_H__
#define __GUI_PLAYER_H__

# include "Attributes.h"
# include "AIPlayer.h"
# include <iostream>
# include "ParchisGUI.h"

using namespace std;

class ParchisGUI;

class GUIPlayer: public AIPlayer{
    private:
        ParchisGUI *gui;

        bool auto_think;

        color next_move_color;
        int next_move_id;
        int next_move_dice;

        bool next_move_confirmed;

        bool think_next_move;

    public:
        virtual void perceive(Parchis &p);

        GUIPlayer(const string & name);

        GUIPlayer(const string & name, int id);

        GUIPlayer(const string & name, ParchisGUI & gui);

        GUIPlayer(const string & name, int id, ParchisGUI & gui);

        inline void setGUI(ParchisGUI & gui){
            this->gui = &gui;
        }

        /**
         * @brief Función abstracta que define el movimiento devuelto por el jugador.
         * 
         * @param dice 
         * @param id_piece 
         * @param c_piece 
         * @return true 
         * @return false 
         */
        bool move();

        inline bool isAutoThinking() const{
            return auto_think;
        }

        inline void setAutoThinking(bool auto_think){
            this->auto_think = auto_think;
        }

        inline virtual bool canUseGUI() const{ return !auto_think && !think_next_move && !next_move_confirmed;}

        void setNextMoveColor(color c);

        void setNextMoveId(int id);

        void setNextMoveDice(int dice);

        void setNextMove(color c, int id, int dice);

        void confirmNextMove();

        void thinkNextMove();

        bool readyForNextTurn();

};
#endif