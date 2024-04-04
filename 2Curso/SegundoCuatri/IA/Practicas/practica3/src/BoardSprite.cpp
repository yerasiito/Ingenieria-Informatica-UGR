# include "BoardSprite.h"
# include "ParchisGUI.h"

BoardSprite::BoardSprite(const Texture & t): ClickableSprite(t){}

void BoardSprite::onClickAction(Window & container){
    ParchisGUI *gui = dynamic_cast<ParchisGUI *>(&container);

    if(enabled && !locked && clicked){
        Vector2i pos = Mouse::getPosition(*gui);
        FloatRect board_box = this->getGlobalBounds();
        Vector2f board_center(board_box.left + board_box.width / 2, board_box.top + board_box.height / 2);
        gui->rotate_board = true;
        gui->rotate_angle0 = atan2(pos.x - board_center.x, pos.y - board_center.y) * 180.f / PI;
    }
    else{
        gui->rotate_board = false;
    }
}

void BoardSprite::onHoverAction(Window & container){
    ParchisGUI *gui = dynamic_cast<ParchisGUI *>(&container);
    if(hovered){
        gui->setHandCursor();
    }
}

void BoardSprite::onSelectionAction(Window & container){}

void BoardSprite::onLockAction(Window &container) {}

void BoardSprite::onEnableAction(Window &container) {}