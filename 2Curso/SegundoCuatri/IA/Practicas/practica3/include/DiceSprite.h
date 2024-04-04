#ifndef __DICESPRITE_H__
#define __DICESPRITE_H__

#include "ClickableSprite.h"
#include "IncludesSFML.h"
#include "Attributes.h"
// #include "ParchisGUI.h"

using namespace std;

//class ParchisGUI;

class DiceSprite: public ClickableSprite{
    private:
        int number;
        color c;

        //Definiciones para los dados
        static const map <int, vector<int>> num2textrec;
        static const map <int, vector<int>> num2selectedrec;

        static const map <color, Color> color2DisabledColor;
        static const map <color, Color> color2SelectedColor;

    public:
        static const map <color, Color> color2Color;

        //inline DiceSprite() : ClickableSprite(), number(-1), c(color::none){}
        DiceSprite(const Texture & t, int n, color c);

        inline int getNumber(){return number;}
        inline color getModelColor(){return this->c;}

        void setNumber(int n);
        void setModelColor(color c);

        void onClickAction(Window & container);
        void onEnableAction(Window & container);
        void onSelectionAction(Window & container);
        void onHoverAction(Window & container);
        void onLockAction(Window & container);
};

#endif