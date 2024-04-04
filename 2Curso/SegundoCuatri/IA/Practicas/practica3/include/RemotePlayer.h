#ifndef __REMOTEPLAYER_H__
#define __REMOTEPLAYER_H__

#include "Attributes.h"
#include "Player.h"
#include "Connection.h"
#include <memory>

class RemotePlayer : public Player {
    private:
        //ParchisRemote *controller;    
        shared_ptr<ParchisRemote> controller;


    public:
        void perceive(Parchis &p);

        inline RemotePlayer(const string &name, shared_ptr<ParchisRemote> controller) :Player(name) {
            this->controller = controller;
        }

        virtual bool move();

        inline virtual bool isRemote() const{return true;}

        virtual bool readyForNextTurn();
};

#endif