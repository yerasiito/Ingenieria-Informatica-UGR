#ifndef __PIECESPRITE_H__
#define __PIECESPRITE_H__

#include "ClickableSprite.h"
#include "IncludesSFML.h"
#include "Attributes.h"
// #include "ParchisGUI.h"

using namespace std;

class PieceSprite: public ClickableSprite{
    private:
        int id;
        color c;

        static const map <color, vector<int>> col2textrec;

        static const map <color, vector<int>> col2selectedrec;

    public:

        PieceSprite(const Texture & t, int id, color c);

        inline int getId(){ return this->id;}
        inline color getModelColor(){return this->c;}

        void onClickAction(Window & container);
        void onEnableAction(Window & container);
        void onSelectionAction(Window & container);
        void onHoverAction(Window & container);
        void onLockAction(Window & container);
};

#endif