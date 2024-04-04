# ifndef __GAMESELECTOR_H__
# define __GAMESELECTOR_H__

# include "IncludesSFML.h"
# include <iostream>
# include "ClickableSprite.h"
# include "Board.h"


static const int game_selector_bt_width = 320;
static const int game_selector_bt_height = 60;
static const int game_selector_bt_state_offset = 20;

struct GameParameters{
    string type_j1, type_j2;
    int id_j1, id_j2;
    int port;
    string ip;
    string name_j1, name_j2;
    bool gui;
    bool server;
    bool ninja_server;
    BoardConfig config;

    bool random;
    bool private_room;
};

class TextBox{
    private:
        Text text;
        RectangleShape shape;
        Color color;

        bool allow_typing;
        bool only_numeric;

        bool focused;
        bool hovered;
        bool enabled;

        Keyboard::Key last_press;
        Time last_press_time;
        Clock clock;
        int wait_press_time;

        int max_size;

    public:
        TextBox();

        TextBox(const Font &font);

        void setText(const string &text);

        void setFont(const Font &font);

        void setSize(const Vector2f &size);

        void setPosition(const Vector2f &position);

        void setColor(const Color &color);

        inline void setMaxSize(int max_size){ this->max_size = max_size; }

        void draw(RenderWindow & window);

        void processKeys();

        inline void setAllowTyping(bool allow_typing){this->allow_typing = allow_typing;}
        bool getAllowTyping() const{return allow_typing;}

        inline void setOnlyNumeric(bool only_numeric){this->only_numeric = only_numeric;}
        bool getOnlyNumeric() const{return only_numeric;}

        inline string getText() const{return text.getString();}

        FloatRect getGlobalBounds() const;

        inline bool isFocused() const{return focused;}
        inline void setFocused(bool focused, Window &container){this->focused = focused; onFocusAction(container);}
        void onFocusAction(Window & container);

        inline bool isHovered() const{return hovered;}
        inline void setHovered(bool hovered, Window & container){this->hovered = hovered; onHoverAction(container);}
        void onHoverAction(Window &container);

        inline bool isEnabled() const{return enabled;}
        inline void setEnabled(bool enabled, Window & container){this->enabled = enabled; onEnableAction(container);}
        void onEnableAction(Window &container);

};

class GameSelector: public RenderWindow{
private:
    class StandardGSButton: public ClickableSprite{
    protected:
        int start_pos;

        virtual void updateButton();



    public:
        inline StandardGSButton() : ClickableSprite(){}
        inline StandardGSButton(const Texture &t) : ClickableSprite(t){}

        virtual void onClickAction(Window &container);
        inline virtual void onEnableAction(Window &container){ updateButton();}
        virtual void onSelectionAction(Window &container) = 0;
        virtual void onHoverAction(Window &container);
        inline virtual void onLockAction(Window &container){ updateButton();}
    };
    class TwoPlayerButton: public StandardGSButton{
        protected:
            //void updateButton();

        public:
            inline TwoPlayerButton(): StandardGSButton(){}
            inline TwoPlayerButton(const Texture &t): StandardGSButton(t) { start_pos = 0; updateButton();};

            void onSelectionAction(Window &container);
    };

    class VSHeuristicButton: public StandardGSButton{
        protected:
            //void updateButton();

        public:
            inline VSHeuristicButton() : StandardGSButton() {}
            inline VSHeuristicButton(const Texture &t) : StandardGSButton(t) {start_pos=110;updateButton();};

            //void onClickAction(Window &container);
            //void onEnableAction(Window &container);
            void onSelectionAction(Window &container);
            //void onHoverAction(Window &container);
            //void onLockAction(Window &container);
    };

    class Ninja1Button: public StandardGSButton{
        protected:
            //void updateButton();

        public:
            inline Ninja1Button() : StandardGSButton() {}
            inline Ninja1Button(const Texture &t) : StandardGSButton(t) {start_pos=190;updateButton();};

            //void onClickAction(Window &container);
            //void onEnableAction(Window &container);
            void onSelectionAction(Window &container);
            //void onHoverAction(Window &container);
            //void onLockAction(Window &container);
    };

    class Ninja2Button: public StandardGSButton{
        protected:
            //void updateButton();

        public:
            inline Ninja2Button() : StandardGSButton() {}
            inline Ninja2Button(const Texture &t) : StandardGSButton(t) { start_pos = 270; updateButton();};

            //void onClickAction(Window &container);
            //void onEnableAction(Window &container);
            void onSelectionAction(Window &container);
            //void onHoverAction(Window &container);
            //void onLockAction(Window &container);
    };

    class Ninja3Button: public StandardGSButton{
        protected:
            //void updateButton();

        public:
            inline Ninja3Button() : StandardGSButton() {}
            inline Ninja3Button(const Texture &t) : StandardGSButton(t) { start_pos = 350; updateButton();};

            //void onClickAction(Window &container);
            //void onEnableAction(Window &container);
            void onSelectionAction(Window &container);
            //void onHoverAction(Window &container);
            //void onLockAction(Window &container);
    };

    class HeuristicVSHeuristicButton: public StandardGSButton{
        protected:
            //void updateButton();

        public:
            inline HeuristicVSHeuristicButton() : StandardGSButton() {}
            inline HeuristicVSHeuristicButton(const Texture &t) : StandardGSButton(t) { start_pos = 460; updateButton();};

            //void onClickAction(Window &container);
            //void onEnableAction(Window &container);
            void onSelectionAction(Window &container);
            //void onHoverAction(Window &container);
            //void onLockAction(Window &container);
    };

    class HeuristicVSNinjaButton: public StandardGSButton{
        protected:
            //void updateButton();

        public:
            inline HeuristicVSNinjaButton() : StandardGSButton() {}
            inline HeuristicVSNinjaButton(const Texture &t) : StandardGSButton(t) { start_pos = 540; updateButton();};

            //void onClickAction(Window &container);
            //void onEnableAction(Window &container);
            void onSelectionAction(Window &container);
            //void onHoverAction(Window &container);
            //void onLockAction(Window &container);
    };

    class NinjaVSHeuristicButton: public StandardGSButton{
        protected:
            //void updateButton();

        public:
            inline NinjaVSHeuristicButton() : StandardGSButton() {}
            inline NinjaVSHeuristicButton(const Texture &t) : StandardGSButton(t) { start_pos = 620; updateButton();};

            //void onClickAction(Window &container);
            //void onEnableAction(Window &container);
            void onSelectionAction(Window &container);
            //void onHoverAction(Window &container);
            //void onLockAction(Window &container);
    };

    class OnlineClientButton: public StandardGSButton{
        protected:
            //void updateButton();

        public:
            inline OnlineClientButton() : StandardGSButton() {}
            inline OnlineClientButton(const Texture &t) : StandardGSButton(t) { start_pos = 730; updateButton();};

            //void onClickAction(Window &container);
            //void onEnableAction(Window &container);
            void onSelectionAction(Window &container);
            //void onHoverAction(Window &container);
            //void onLockAction(Window &container);
    };

    class OnlineServerButton : public StandardGSButton{
        protected:
            //void updateButton();

        public:
            inline OnlineServerButton() : StandardGSButton() {}
            inline OnlineServerButton(const Texture &t) : StandardGSButton(t) { start_pos = 810; updateButton();};

            //void onClickAction(Window &container);
            //void onEnableAction(Window &container);
            void onSelectionAction(Window &container);
            //void onHoverAction(Window &container);
            //void onLockAction(Window &container);
    };

    class RandomPairingButton : public StandardGSButton{
        protected:
            //void updateButton();

        public:
            inline RandomPairingButton() : StandardGSButton() {}
            inline RandomPairingButton(const Texture &t) : StandardGSButton(t) { start_pos = 890; updateButton();};

            //void onClickAction(Window &container);
            //void onEnableAction(Window &container);
            void onSelectionAction(Window &container);
            //void onHoverAction(Window &container);
            //void onLockAction(Window &container);
    };

    class PrivateRoomButton: public StandardGSButton{
        protected:
            //void updateButton();

        public:
            inline PrivateRoomButton() : StandardGSButton() {}
            inline PrivateRoomButton(const Texture &t) : StandardGSButton(t) { start_pos = 970; updateButton();};

            //void onClickAction(Window &container);
            //void onEnableAction(Window &container);
            void onSelectionAction(Window &container);
            //void onHoverAction(Window &container);
            //void onLockAction(Window &container);
    };

    class UseGUIButton : public StandardGSButton{
        protected:
            void updateButton();

        public:
            inline UseGUIButton() : StandardGSButton() {}
            inline UseGUIButton(const Texture &t) : StandardGSButton(t) { start_pos = 1090; updateButton();};

            void onClickAction(Window &container);
            //void onEnableAction(Window &container);
            void onSelectionAction(Window &container);
            //void onHoverAction(Window &container);
            //void onLockAction(Window &container);
    };

    class PlayerIDButton : public StandardGSButton{
        private:
            int id;
        protected:
            void updateButton();

        public:
            inline PlayerIDButton() : StandardGSButton() {}
            inline PlayerIDButton(const Texture &t) : StandardGSButton(t), id(1) { start_pos = 1330; selected=true; updateButton();};

            void onClickAction(Window &container);
            //void onEnableAction(Window &container);
            void onSelectionAction(Window &container);
            //void onHoverAction(Window &container);
            //void onLockAction(Window &container);
    };

    class StartGameButton : public StandardGSButton{
        protected:
            void updateButton();

        public:
            inline StartGameButton() : StandardGSButton() {}
            inline StartGameButton(const Texture &t): StandardGSButton(t){ start_pos = 1210; updateButton();};

            void onClickAction(Window &container);
            //void onEnableAction(Window &container);
            inline void onSelectionAction(Window &container){}
            //void onHoverAction(Window &container);
            //void onLockAction(Window &container);
    };

    class TextBoxIncDecButton : public ClickableSprite{
        private:
            TextBox * textbox;
            bool inc;
        public:
            inline TextBoxIncDecButton() : ClickableSprite() {}
            TextBoxIncDecButton(const Texture &t, bool inc);
            TextBoxIncDecButton(const Texture &t, TextBox & textbox, bool inc);
            inline void setTextBox(TextBox & textbox){ this->textbox = &textbox; }

            void onClickAction(Window &container);
            inline void onEnableAction(Window &container){}
            inline void onSelectionAction(Window &container){}
            void onHoverAction(Window &container);
            inline void onLockAction(Window &container){}
    };


    Cursor cursor;
    void setForbiddenCursor();
    void setDefaultCursor();
    void setHandCursor();
    void setTextCursor();

    Font window_fonts;

    void defaultHover();

    void updateSelection(StandardGSButton & current_selection);

    //Texture for the buttons
    Texture tButtons;

    //Definition of buttons.
    TwoPlayerButton two_player_button;
    VSHeuristicButton vs_heuristic_button;
    Ninja1Button ninja1_button;
    Ninja2Button ninja2_button;
    Ninja3Button ninja3_button;
    HeuristicVSHeuristicButton heuristic_vs_heuristic_button;
    HeuristicVSNinjaButton heuristic_vs_ninja_button;
    NinjaVSHeuristicButton ninja_vs_heuristic_button;
    OnlineClientButton online_client_button;
    OnlineServerButton online_server_button;
    RandomPairingButton random_pairing_button;
    PrivateRoomButton private_room_button;
    UseGUIButton use_gui_button;
    PlayerIDButton player_id_button;
    StartGameButton start_game_button;

    TextBox * focused_textbox;

    TextBox ai1_id;
    TextBoxIncDecButton ai1_id_incbt;
    TextBoxIncDecButton ai1_id_decbt;

    TextBox ai2_id;
    TextBoxIncDecButton ai2_id_incbt;
    TextBoxIncDecButton ai2_id_decbt;

    TextBox ip_box;
    TextBox port_box;

    TextBox p1_name;
    TextBox p2_name;

    Text ai1_id_text;
    Text ai2_id_text;
    Text ip_text;
    Text port_text;

    Text p1_name_text;
    Text p2_name_text;
    
    vector<StandardGSButton*> gs_buttons;
    vector<StandardGSButton*> exclusive_selection_buttons;

    vector<ClickableSprite*> other_buttons;
    vector<TextBox*> text_boxes;
    vector<Text*> labels; 

    void windowLoop();
    void processMouse();
    void processEvents();
    void paint();

    //void collectSprites();
    View view;


    friend class StandardGSButton;
    friend class TwoPlayerButton;
    friend class VSHeuristicButton;
    friend class Ninja1Button;
    friend class Ninja2Button;
    friend class Ninja3Button;
    friend class HeuristicVSHeuristicButton;
    friend class HeuristicVSNinjaButton;
    friend class NinjaVSHeuristicButton;
    friend class OnlineClientButton;
    friend class OnlineServerButton;
    friend class RandomPairingButton;
    friend class UseGUIButton;
    friend class PlayerIDButton;
    friend class StartGameButton;
    friend class TextBoxIncDecButton;
    friend class TextBox;

public:
    GameSelector();

    GameParameters game_parameters;

    void run();

    inline const GameParameters & getGameParameters() const { return game_parameters; }
};


# endif