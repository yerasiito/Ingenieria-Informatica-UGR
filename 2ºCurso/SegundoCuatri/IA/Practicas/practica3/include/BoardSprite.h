#ifndef __BOARDSPRITE_H__
#define __BOARDSPRITE_H__

#include "ClickableSprite.h"
#include "IncludesSFML.h"
#include "Attributes.h"
//#include "ParchisGUI.h"

#define PI 3.14159265

using namespace std;

class BoardSprite: public ClickableSprite{
    private:

    public:
        inline BoardSprite():ClickableSprite(){}
        BoardSprite(const Texture & t);

        void onClickAction(Window &container);
        void onEnableAction(Window &container);
        void onSelectionAction(Window &container);
        void onHoverAction(Window &container);
        void onLockAction(Window &container);
};

#endif