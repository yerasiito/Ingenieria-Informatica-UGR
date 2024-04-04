#ifndef __PARCHISGUI_H__
#define __PARCHISGUI_H__

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <math.h>
#include <fstream>
#include "Board.h"
#include "Attributes.h"
#include "Parchis.h"
#include "DiceSprite.h"
#include "PieceSprite.h"
#include "BoardSprite.h"
//#include "RectangularButton.h"
#include "Button.h"
#include "ClickableSprite.h"
#include "SpriteAnimator.h"
#include <list>
#include <queue>
//#include "GUIPlayer.h"
//#include <thread>

using namespace sf;
using namespace std;

class ParchisGUI: public RenderWindow
{
private:
    static const map<Box, vector<Vector2i>> box2position;

    static const float ASPECT_RATIO;

    static const int getInitialWindowWidth();
    static const int getInitialWindowHeight();

    //RenderWindow game_window;
    Parchis *model;
    
    //Textures' definitions
    Texture tBackground;
    Texture tBoard;
    Texture tPieces;
    Texture tDices;
    Texture tSkipBt;
    Texture tButtons;
        
    //Sprites' definitions
    Sprite background;
    map <color, vector<PieceSprite>> pieces;
    map <color, vector<DiceSprite>> dices;
    map <color, vector<DiceSprite>> special_10_20_dice;
    // vector<BoardSprite> boards;
    BoardSprite board;

    // Buttons' definitions
    SkipTurnButton skip_turn_button;
    MoveHeuristicButton move_heuristic_button;
    AutoHeuristicButton auto_heuristic_button;
    MusicOnOffButton music_on_off_button;
    SoundOnOffButton sound_on_off_button;

    // Turns arrow and text
    Sprite turns_arrow;
    Text turns_arrow_text;
    static const IntRect turns_arrow_rect;
    static const map<color, int> color2turns_arrow_pos;

    //Sprites utilities to reduce the code.
    vector<Drawable*> all_drawable_sprites;
    vector<ClickableSprite*> all_clickable_sprites;

    //Sprites lists separated by views.
    vector<Sprite*> general_drawable_sprites;

    vector<Sprite*> board_drawable_sprites;
    vector<Sprite*> dice_drawable_sprites;
    vector<Sprite*> bt_panel_drawable_sprites;

    vector<ClickableSprite*> board_clickable_sprites;
    vector<ClickableSprite*> dice_clickable_sprites;
    vector<ClickableSprite*> bt_panel_clickable_sprites;

    // Views
    View general_view;
    View board_view;
    View dice_view;
    View bt_panel_view;

    //Music booleans
    bool music_enabled;
    bool sound_effects_enabled;

    //Click booleans
    bool clicked;

    //Cursor
    Cursor cursor;
    Cursor default_cursor;

    //List of animations.
    //list<SpriteAnimator> animations;
    // Several channels for animations, so that several animations can be run in parallel but also animations can be chained.
    queue<SpriteAnimator> animations_ch1; // Normal piece animations.
    queue<SpriteAnimator> animations_ch2; // Piece animations with collisions.
    queue<SpriteAnimator> animations_ch3; // Piece animations with anti-collisions.
    queue<SpriteAnimator> animations_ch4; // Out-board animations (like turns arrow).

    vector<queue<SpriteAnimator>*> all_animators; // All channels.

    // Hebra del juego (no puede desarrollarse en la misma hebra que la GUI porque entonces cada acción en el juego bloquearía la GUI)
    Thread game_thread;

    // Para exclusión mutua
    Mutex mutex;
    
    // Bool para indicar si hay que llamar a la hebra del juego en el bucle principal.
    bool call_thread_start;

    // Sonidos en el juego.
    SoundBuffer sound_buffer_move;
    SoundBuffer sound_buffer_boing;
    SoundBuffer sound_buffer_forbidden;
    SoundBuffer sound_buffer_eaten;
    SoundBuffer sound_buffer_applause;

    Sound sound_move;
    Sound sound_boing;
    Sound sound_forbidden;
    Sound sound_eaten;
    Sound sound_applause;

    static const string sound_move_file;
    static const string sound_boing_file;
    static const string sound_forbidden_file;
    static const string sound_eaten_file;
    static const string sound_applause_file;

    bool music_on;
    bool sound_on;

    //Last dice number
    volatile int last_dice;

    // Bool to activate board rotations.
    bool rotate_board;
    float rotate_angle0;

    // Music-related variables
    Music background_theme;
    static const string background_theme_file;

    Music background_theme_hurryup;
    static const string background_theme_hurryup_file;

    Music *current_background_theme;

    // Window icon
    Image icon;
    static const string icon_file;

    // Locks for the game buttons.
    volatile bool animation_lock;
    volatile bool not_playable_lock;

    // Turn variable (used to sync with the game).
    int gui_turn;

    /**
     * @brief Función que ejecuta el código interno del ciclo de juego del parchís.
     * 
     */
    void gameLoop();

    /**
     * @brief Función que inicia el código interno del parchís.
     * 
     */
    void startGameLoop();

    /**
     * @brief Función que procesa las colisiones del ratón con fichas, dados, etc.
     * 
     */
    void processMouse();

    /**
     * @brief Función que procesa los eventos del ratón.
     * 
     */
    void processEvents();

    /**
     * @brief Función que procesa las animaciones.
     * 
     */
    void processAnimations();

    /**
     * @brief Función que procesa el resto de elementos de la interfaz (música, etc)
     * 
     */
    void processSettings();

    /**
     * @brief Función que refresca la ventana principal.
     * 
     */
    void paint();

    /**
     * @brief Agrupa todos los sprites en un vector común para facilitar dibujado y eventos.
     * 
     */
    void collectSprites();

    /**
     * @brief Acción a ejecutar por defecto cuando el ratón no está colocado sobre ningún otro elemento de la ventana.
     * 
     */
    void defaultHover();

    /**
     * @brief Actualiza los sprites (habilitados, botones, posiciones, ...)..
     * 
     */
    void updateSprites();

    void updateSpritesLock();

    void selectAction(color col, int dice, bool b);

    void animationLock(bool lock);

    void notPlayableLock(bool lock);

    bool animationsRunning();

    // Funciones para activar distintos cursores en el juego.
    void setDefaultCursor();
    void setNormalCursor();
    void setForbiddenCursor();
    void setThinkingCursor();
    void setHandCursor();
    void setSpecialHandCursor();
    void setConnectingCursor();

    // Funciones para cambiar el default cursor, el que se muestra por defecto cuando no se hoverea nada (deprecated).
    void setDefaultCursorNormal();
    void setDefaultCursorForbidden();
    void setDefaultCursorThinking();
    void setDefaultCursorHand();
    void setDefaultCursorSpecialHand();
    void setDefaultCursorConnecting();

    // Funciones para ejecutar un sonido.
    void initializeSoundEffects();
    void playQueuedMoveSounds();
    void playMoveSound();
    void playBoingSound();
    void playForbiddenSound();
    void playEatenSound();
    void playApplauseSound();

    queue <void (ParchisGUI::*)(void)> animation_ch1_callbacks;

    void setSoundEffects(bool on);

    /**
     * @brief Encola un movimiento de ficha.
     * 
     */
    void queueMove(color col, int id, Box start, Box end, void (ParchisGUI::*callback)(void) = NULL);

    /**
     * @brief Encola la animación de la flecha de turnos.
     * 
     */
    void queueTurnsArrow(color col);

    /**
     * @brief Activa o desactiva la música de fondo.
     * 
     * @param on 
     */
    void setBackgroundMusic(bool on);

    /**
     * @brief 
     * 
     */
    void initializeBackgroundMusic();

    /**
     * @brief 
     * 
     */
    void switchBackgroundMusic();

    /**
     * @brief 
     * 
     */
    void checkHurryUp();

    /**
     * @brief Método privado que implementa el box2position evitando colisiones.
     * 
     * @param c 
     * @param id 
     * @return Vector2f 
     */
    Vector2f box3position(color c, int id, int pos);
    Vector2f box3position(Box b, int id, int pos);

    // FPS
    float fps, avg_fps;
    float current_time;
    long total_frames;
    Clock game_clock;

public:
    ParchisGUI(Parchis & model);
    
    
    /**
     * @brief Bucle principal del juego. 
     * 
     */
    void mainLoop();

    /**
     * @brief Lanzar la ventana.
     * 
     */
    void run();

    //void moveFichas(float t, int i, box_type bt, color c, Sprite &);
    //void moveFichas(float t, int i_orig, box_type bt_orig, color c_orig, int i_end, box_type bt_end, color c_end, Sprite &);
    //void set_color(color my_color, Sprite &);
    //void load_player(color my_color, Sprite &ficha1, Sprite &ficha2, Sprite &ficha3, Sprite &ficha4);
    //int num_box(int pos_x, int pos_y);


    friend class PieceSprite;
    friend class DiceSprite;
    friend class BoardSprite;
    friend class SkipTurnButton;
    friend class MoveHeuristicButton;
    friend class AutoHeuristicButton;
    friend class MusicOnOffButton;
    friend class SoundOnOffButton;

    friend class GUIPlayer;
};

#endif
