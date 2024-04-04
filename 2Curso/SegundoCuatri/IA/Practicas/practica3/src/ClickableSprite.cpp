#include "ClickableSprite.h"

void ClickableSprite::setEnabled(bool b, Window & container){
    this->enabled = b;
    onEnableAction(container);
}

void ClickableSprite::setSelected(bool b, Window & container)
{
    this->selected = b;
    onSelectionAction(container);
}

void ClickableSprite::setClicked(bool b, Window & container)
{
    this->clicked = b;
    onClickAction(container);
}

void ClickableSprite::setHovered(bool b, Window & container)
{
    this->hovered = b;
    onHoverAction(container);
}

void ClickableSprite::setLocked(bool b, Window & container){
    this->locked = b;
    onLockAction(container);
}