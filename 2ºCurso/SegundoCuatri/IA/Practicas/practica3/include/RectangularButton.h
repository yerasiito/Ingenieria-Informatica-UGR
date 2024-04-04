#ifndef __RECT_BUTTON_H__
#define __RECT_BUTTON_H__

#include "Button.h"
#include "IncludesSFML.h"

using namespace std;

class RectangularButton: public Button{
    private:
        //static const Texture button_texture;

    public:
        inline RectangularButton(): Button(){}

        RectangularButton(const Texture & t);

        void refreshButton();



};

#endif