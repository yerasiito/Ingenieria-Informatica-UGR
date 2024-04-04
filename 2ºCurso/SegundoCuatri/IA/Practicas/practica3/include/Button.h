/**
 * @file Button.h
 * @author your name (you@domain.com)
 * @brief En este fichero se definen todos los botones de la GUI distintos de fichas y dados. Cada botón es un ClickableSprite.
 * @version 0.1
 * @date 2022-04-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "ClickableSprite.h"
#include "IncludesSFML.h"
#include "Attributes.h"
#include <memory>

using namespace std;

/**
 * @deprecated
 * 
 */
class NOButton: public ClickableSprite{
    protected:
        Text text;
        Color background_color;

        void (*click_action)(Window & container, NOButton &b);
        void (*enable_action)(Window &container, NOButton &b);
        void (*selection_action)(Window &container, NOButton &b);
        void (*hover_action)(Window &container, NOButton &b);
        void (*lock_action)(Window &container, NOButton &b);

    public:
        inline NOButton(): ClickableSprite(){}
        NOButton(const Texture & t);

        void onClickAction(Window &container);
        void onEnableAction(Window &container);
        void onSelectionAction(Window &container);
        void onHoverAction(Window &container);
        void onLockAction(Window &container);

        void setClickAction(void (*action)(Window & container, NOButton & this_btn));
        void setEnableAction(void (*action)(Window &container, NOButton &this_btn));
        void setSelectionAction(void (*action)(Window &container, NOButton &this_btn));
        void setHoverAction(void (*action)(Window &container, NOButton &this_btn));
        void setLockAction(void (*action)(Window &container, NOButton &this_btn));

        void setText(const String & txt);
        void setTextColor(Color col);
        void setBackgroundColor(Color col);
        virtual void refreshButton() = 0;

        void setButtonSize(Vector2f size);
        void setButtonSize(float width, float height);

        void setButtonPosition(Vector2f pos);
        void setButtonPosition(float posx, float posy);

};

/**
 * @brief Botones de Parchis.  No añade nada de funcionalidad.
 * 
 */
class ParchisButton: public ClickableSprite{
    public:
        inline ParchisButton(): ClickableSprite(){}
        inline ParchisButton(const Texture & t): ClickableSprite(t){}
};

/**
 * @brief Botón para ejecutar el próximo movimiento a través de la heurística.
 * 
 */
class MoveHeuristicButton: public ParchisButton{
    private:
        static const Vector2i length;
        static const Vector2i normal_offset;
        static const Vector2i hover_offset;
        static const Vector2i selected_offset;

        void updateButton(); 
    public:
        inline MoveHeuristicButton(): ParchisButton(){}
        MoveHeuristicButton(const Texture & t);
        
        void onClickAction(Window &container);
        void onEnableAction(Window &container);
        void onSelectionAction(Window &container);
        void onHoverAction(Window &container);
        void onLockAction(Window &container);
};

/**
 * @brief Botón para usar la heurística de forma activada mientras este botón esté activado.
 * 
 */
class AutoHeuristicButton: public ParchisButton{
    private:
        static const Vector2i length;
        static const Vector2i normal_offset;
        static const Vector2i hover_offset;
        static const Vector2i selected_offset;

        void updateButton();

    public:
        inline AutoHeuristicButton(): ParchisButton(){}
        AutoHeuristicButton(const Texture & t);

        void onClickAction(Window &container);
        void onEnableAction(Window &container);
        void onSelectionAction(Window &container);
        void onHoverAction(Window &container);
        void onLockAction(Window &container);
};

/**
 * @brief Botón para activar/desactivar la música de fondo.
 * 
 */
class MusicOnOffButton: public ParchisButton{
    private:
        static const Vector2i length;
        static const Vector2i on_offset;
        static const Vector2i off_offset;

        bool music_on;

        void updateButton();
        
    public:
        inline MusicOnOffButton(): ParchisButton(){music_on = false;}
        MusicOnOffButton(const Texture & t);
        
        void onClickAction(Window &container);
        void onEnableAction(Window &container);
        void onSelectionAction(Window &container);
        void onHoverAction(Window &container);
        void onLockAction(Window &container);
};

/**
 * @brief Botón para activar/desactivar los sonidos de fondo.
 * 
 */
class SoundOnOffButton: public ParchisButton{
    private:
        static const Vector2i length;
        static const Vector2i on_offset;
        static const Vector2i off_offset;

        bool sound_on;

        void updateButton();
    public:
        inline SoundOnOffButton(): ParchisButton(){}
        SoundOnOffButton(const Texture & t);
        
        void onClickAction(Window &container);
        void onEnableAction(Window &container);
        void onSelectionAction(Window &container);
        void onHoverAction(Window &container);
        void onLockAction(Window &container);
};

/**
 * @brief Botón para pasar el turno cuando el jugador no pueda mover.
 * 
 */
class SkipTurnButton: public ParchisButton{
    private:
        color c;

        static const map <color, vector<int>> col2textrec;

        static const map <color, vector<int>> col2selectedrec;

    public:
        inline SkipTurnButton(): ParchisButton(){}
        SkipTurnButton(const Texture & t, color c = yellow);

        inline color getModelColor(){return this->c;}
        void setModelColor(color c);

        void onClickAction(Window & container);
        void onEnableAction(Window & container);
        void onSelectionAction(Window & container);
        void onHoverAction(Window & container);
        void onLockAction(Window & container);

};

#endif