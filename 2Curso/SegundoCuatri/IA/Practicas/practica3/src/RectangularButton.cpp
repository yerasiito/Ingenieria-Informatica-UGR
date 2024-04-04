# include "RectangularButton.h"


RectangularButton::RectangularButton(const Texture & t):Button(t){
    this->setTextureRect(IntRect(0, 0, 100, 100));
}

void RectangularButton::refreshButton(){
    if(enabled){
        this->setColor(Color(this->background_color.r / 2, this->background_color.g / 2, this->background_color.b / 2));
    }
    else if(selected){
        this->setColor(this->background_color);
    }
    else if(hovered){
        this->setColor(this->background_color);
    }
    else if(clicked){
        this->setColor(this->background_color);
    }
    else{
        this->setColor(this->background_color);
    }
}