#ifndef __PLAYER_H__
#define __PLAYER_H__

# include "Attributes.h"

class Parchis;

class Player{
    protected:
        string name;
        int jugador;
        vector<color> colors;

        Parchis *actual;
    public:
        virtual void perceive(Parchis & p);

        inline Player(const string & name){this->name = name; actual = NULL;}

        inline string getName() const{return name;}

        /**
         * @brief Función abstracta que define el movimiento devuelto por el jugador.
         * 
         * @param dice 
         * @param id_piece 
         * @param c_piece 
         * @return true 
         * @return false 
         */
        virtual bool move() = 0;

        inline virtual bool canUseGUI() const{return false;}

        inline virtual bool canThink() const{return false;}

        inline virtual bool isRemote() const{return false;}

        inline virtual bool readyForNextTurn(){return true;}

};
#endif