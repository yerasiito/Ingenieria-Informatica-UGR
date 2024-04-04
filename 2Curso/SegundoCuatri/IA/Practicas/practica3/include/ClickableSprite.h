#ifndef __CLICKABLESPRITE_H__
#define __CLICKABLESPRITE_H__

#include <iostream>
#include "IncludesSFML.h"

using namespace std;

class ClickableSprite: public Sprite{
    protected:
        bool enabled;
        bool selected;
        bool clicked;
        bool hovered;
        bool locked;

    public:
        inline ClickableSprite(): Sprite(){}

        inline ClickableSprite(const Texture & t): Sprite(t) {
            enabled = true;
            selected = false;
            clicked = false;
            hovered = false;
            locked = false;
        };

        inline const bool isEnabled() const{return enabled;}

        inline const bool isSelected() const{return selected;}

        inline const bool isClicked() const{return clicked;}

        inline const bool isLocked() const{return locked;}

        inline const bool isHovered() const{return hovered;}

        void setEnabled(bool b, Window & container);

        void setSelected(bool b, Window & container);
    
        void setClicked(bool b, Window & container);

        void setHovered(bool b, Window & container);

        void setLocked(bool b, Window & container);

        virtual void onEnableAction(Window & container) = 0;

        virtual void onSelectionAction(Window & container) = 0;

        virtual void onClickAction(Window & container) = 0;

        virtual void onHoverAction(Window & container) = 0;

        virtual void onLockAction(Window & container) = 0;

};

#endif