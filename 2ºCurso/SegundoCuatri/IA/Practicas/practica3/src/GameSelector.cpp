# include "GameSelector.h"
# include <utility>


TextBox::TextBox(){
    shape.setSize(Vector2f(150, 30));
    shape.setFillColor(Color::White);
    shape.setOutlineColor(Color::Black);
    shape.setOutlineThickness(1);
    //text.setFont(font);
    text.setFillColor(Color::Black);
    text.setCharacterSize(30);
    last_press_time = clock.getElapsedTime();

    focused = false;
    enabled = true;
    hovered = false;
    allow_typing = false;
    only_numeric = false;
    wait_press_time = 500;
}

TextBox::TextBox(const Font &font){
    shape.setSize(Vector2f(150, 30));
    shape.setFillColor(Color::White);
    shape.setOutlineColor(Color::Black);
    shape.setOutlineThickness(1);
    setFont(font);
    text.setFillColor(Color::Black);
    text.setCharacterSize(30);
    last_press_time = clock.getElapsedTime();

    focused = false;
    enabled = true;
    hovered = false;
    allow_typing = false;
    only_numeric = false;
    wait_press_time = 500;
}

void TextBox::setText(const string & text){
    this->text.setString(text);
}

void TextBox::setFont(const Font & font){
    this->text.setFont(font);
}

void TextBox::setSize(const Vector2f & size){
    // Set the text font proportionally to the size
    this->text.setCharacterSize(size.y -2);
    this->shape.setSize(size);
    // Set the t
}

void TextBox::setPosition(const Vector2f & position){
    shape.setPosition(position);
    text.setPosition(position.x + 5, position.y - 5);
}

void TextBox::setColor(const Color & color){
    //shape.setFillColor(color);
    text.setFillColor(color);
}

void TextBox::draw(RenderWindow & window){
    window.draw(shape);
    window.draw(text);
}

void TextBox::onHoverAction(Window & container){
    if(hovered){
        GameSelector * gs = static_cast<GameSelector *>(&container);
        if(allow_typing && enabled){
            gs->setTextCursor();
        }
        else{
            gs->setForbiddenCursor();
        }
    }
}

void TextBox::onFocusAction(Window & container){
    GameSelector *gs = static_cast<GameSelector *>(&container);
    if(focused && enabled && allow_typing){
        shape.setFillColor(Color::Cyan);
        gs->focused_textbox = this;
    }
    else{
        if(!enabled) shape.setFillColor(Color(128, 128, 128));
        else shape.setFillColor(Color::White);
        if(!focused && gs->focused_textbox == this){
            gs->focused_textbox = NULL;
        }
    }
}

void TextBox::onEnableAction(Window & container){
    if(!enabled){
        shape.setFillColor(Color(128, 128, 128));
    }
    else{
        shape.setFillColor(Color::White);
    }
}

FloatRect TextBox::getGlobalBounds() const{
    return shape.getGlobalBounds();
}

void TextBox::processKeys(){
    if(allow_typing && enabled){
        bool shift = Keyboard::isKeyPressed(Keyboard::LShift) || Keyboard::isKeyPressed(Keyboard::RShift);
        vector<Keyboard::Key> numeric_keys = {Keyboard::Num0, Keyboard::Num1, Keyboard::Num2, Keyboard::Num3, Keyboard::Num4, Keyboard::Num5, Keyboard::Num6, Keyboard::Num7, Keyboard::Num8, Keyboard::Num9};
        vector<char> numeric_keys_char = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
        vector<char> shift_numeric_keys_char = {'=', '!', '@', '#', '$', '%', '&', '/', '(', ')'};
        vector<Keyboard::Key> numpad_keys = {Keyboard::Numpad0, Keyboard::Numpad1, Keyboard::Numpad2, Keyboard::Numpad3, Keyboard::Numpad4, Keyboard::Numpad5, Keyboard::Numpad6, Keyboard::Numpad7, Keyboard::Numpad8, Keyboard::Numpad9};
        vector<char> numpad_keys_char = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
        vector<Keyboard::Key> character_keys = {Keyboard::A, Keyboard::B, Keyboard::C, Keyboard::D, Keyboard::E, Keyboard::F, Keyboard::G, Keyboard::H, Keyboard::I, Keyboard::J, Keyboard::K, Keyboard::L, Keyboard::M, Keyboard::N, Keyboard::O, Keyboard::P, Keyboard::Q, Keyboard::R, Keyboard::S, Keyboard::T, Keyboard::U, Keyboard::V, Keyboard::W, Keyboard::X, Keyboard::Y, Keyboard::Z};
        vector<char> character_keys_char = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
        vector<char> shift_character_keys_char = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
        vector<Keyboard::Key> symbol_keys = {Keyboard::Comma, Keyboard::Period, Keyboard::Quote, Keyboard::Slash, Keyboard::Dash, Keyboard::Equal};
        vector<char> symbol_keys_char = {',', '.', '\'', '/', '-', '=', };
        vector<char> shift_symbol_keys_char = {';', ':', '?', '<', '_', '>' };
        vector<Keyboard::Key> numpad_symbol_keys = {Keyboard::Add, Keyboard::Subtract, Keyboard::Multiply, Keyboard::Divide};
        vector<char> numpad_symbol_keys_char = {'+', '-', '*', '/'};
        vector<char> shift_numpad_symbol_keys_char = {'\"', '^', '~', '\\'};
        vector<Keyboard::Key> special_keys = {Keyboard::BackSpace, Keyboard::Return, Keyboard::Space};
        
        vector<vector<Keyboard::Key> > keys;
        vector<vector<char> > keys_char;
        if(only_numeric){
            keys = {numeric_keys, numpad_keys};
            if(!shift){
                keys_char = {numeric_keys_char, numpad_keys_char};
            }
            else{
                keys_char = {numeric_keys_char, numpad_keys_char};
            }

        }
        else{
            keys = {numeric_keys, numpad_keys, character_keys, symbol_keys, numpad_symbol_keys};
            if(!shift){
                keys_char = {numeric_keys_char, numpad_keys_char, character_keys_char, symbol_keys_char, numpad_symbol_keys_char};
            }
            else{
                keys_char = {shift_numeric_keys_char, numpad_keys_char, shift_character_keys_char, shift_symbol_keys_char, shift_numpad_symbol_keys_char};
            }
        }

        if(text.getString().getSize() < max_size){
            for(int i = 0; i < keys.size(); i++){
                for(int j = 0; j < keys[i].size(); j++){
                    if(Keyboard::isKeyPressed(keys[i][j])){
                        if (last_press != keys[i][j] && clock.getElapsedTime().asMilliseconds() - last_press_time.asMilliseconds() > 50 || clock.getElapsedTime().asMilliseconds() - last_press_time.asMilliseconds() > wait_press_time)
                        {
                            text.setString(text.getString() + keys_char[i][j]);
                            last_press_time = clock.getElapsedTime();
                            wait_press_time = (last_press == keys[i][j]) ? 50 : 500;
                            last_press = keys[i][j];
                        }
                    }
                }
            }
        
            if (!only_numeric && Keyboard::isKeyPressed(Keyboard::Space))
            {
                if (last_press != Keyboard::Space && clock.getElapsedTime().asMilliseconds() - last_press_time.asMilliseconds() > 50 || clock.getElapsedTime().asMilliseconds() - last_press_time.asMilliseconds() > wait_press_time)
                {
                    text.setString(text.getString() + " ");
                    last_press_time = clock.getElapsedTime();
                    wait_press_time = (last_press == Keyboard::Space) ? 50 : 500;
                    last_press = Keyboard::Space;
                }
            }
        }
        if(Keyboard::isKeyPressed(Keyboard::Backspace)){
            if (last_press != Keyboard::Backspace && clock.getElapsedTime().asMilliseconds() - last_press_time.asMilliseconds() > 50 || clock.getElapsedTime().asMilliseconds() - last_press_time.asMilliseconds() > wait_press_time)
            {
                string curr_text = text.getString();
                if (curr_text.size() > 0)
                {
                    curr_text.pop_back();
                    text.setString(curr_text);
                }
                last_press_time = clock.getElapsedTime();
                wait_press_time = (last_press == Keyboard::Backspace) ? 50 : 500;
                last_press = Keyboard::Backspace;
            }
        }
        
    }
}

GameSelector::TextBoxIncDecButton::TextBoxIncDecButton(const Texture & t, bool inc): ClickableSprite(t), textbox(NULL), inc(inc){
    if(inc){
        this->setTextureRect(IntRect(240, 1520, 55, 55));
    }
    else{
        this->setTextureRect(IntRect(10, 1520, 55, 55));
    }

}

GameSelector::TextBoxIncDecButton::TextBoxIncDecButton(const Texture &t, TextBox & textbox, bool inc): ClickableSprite(t), textbox(&textbox), inc(inc){
    if(inc){
        this->setTextureRect(IntRect(240, 1520, 55, 55));
    }
    else{
        this->setTextureRect(IntRect(10, 1520, 55, 55));
    }
}

void GameSelector::TextBoxIncDecButton::onHoverAction(Window & container){
    if (hovered)
    {
        // Set hand cursor
        GameSelector *gs = static_cast<GameSelector *>(&container);
        if (locked || !enabled)
        {
            gs->setForbiddenCursor();
        }
        else
        {
            gs->setHandCursor();
        }
    }
}

void GameSelector::TextBoxIncDecButton::onClickAction(Window &container)
{
    if (clicked && enabled && !locked)
    {
        if(textbox != NULL){
            if(inc){
                textbox->setText(to_string(stoi(textbox->getText()) + 1));
            }
            else{
                textbox->setText(to_string(stoi(textbox->getText()) - 1));
            }
        }
    }
}

void GameSelector::StandardGSButton::updateButton(){
    if(selected){
        this->setTextureRect(IntRect(2* (game_selector_bt_width + game_selector_bt_state_offset), start_pos, game_selector_bt_width + 5, game_selector_bt_height + 5));
    }
    else if (hovered && enabled && !locked)
    {
        this->setTextureRect(IntRect((game_selector_bt_width + game_selector_bt_state_offset), start_pos, game_selector_bt_width + 5, game_selector_bt_height + 5));
    }
    else
    {
        this->setTextureRect(IntRect(0, start_pos, game_selector_bt_width + 5, game_selector_bt_height + 5));
    }
}

void GameSelector::StandardGSButton::onClickAction(Window & container){
    if(clicked && enabled && !locked){
        setSelected(true, container);
    }
}

void GameSelector::StandardGSButton::onHoverAction(Window &container){
    if(hovered){
        // Set hand cursor
        GameSelector *gs = static_cast<GameSelector*>(&container);
        if (locked || !enabled)
        {
            gs->setForbiddenCursor();
        }
        else
        {
            gs->setHandCursor();
        }
    }
    updateButton();
}

void GameSelector::TwoPlayerButton::onSelectionAction(Window & container){
    if(selected){
        GameSelector *gs = static_cast<GameSelector*>(&container);
        gs->game_parameters.type_j1 = "GUI";
        gs->game_parameters.type_j2 = "GUI";
        gs->game_parameters.server = false;
        gs->game_parameters.random = false;
        gs->game_parameters.private_room = false;

        gs->use_gui_button.setSelected(true, *gs);
        gs->use_gui_button.setEnabled(false, *gs);

        gs->player_id_button.setEnabled(false, *gs);

        gs->ai1_id.setEnabled(true, container);
        gs->ai1_id_incbt.setEnabled(true, container);
        gs->ai1_id_decbt.setEnabled(true, container);
        gs->ai1_id_text.setString("ID de la IA (J1)");
        gs->ai2_id.setEnabled(true, container);
        gs->ai2_id_incbt.setEnabled(true, container);
        gs->ai2_id_decbt.setEnabled(true, container);
        gs->ai2_id_text.setString("ID de la IA (J2)");
        gs->updateSelection(*this);

        gs->ip_box.setEnabled(false, container);
        gs->ip_text.setString(L"Dirección IP / Nombre de dominio");
        gs->port_box.setEnabled(false, container);

    }
    
    updateButton();
}

void GameSelector::VSHeuristicButton::onSelectionAction(Window &container)
{
    if(selected){
        GameSelector *gs = static_cast<GameSelector*>(&container);
        gs->game_parameters.server = false;
        gs->game_parameters.random = false;
        gs->game_parameters.private_room = false;
        gs->player_id_button.setEnabled(true, *gs);

        gs->use_gui_button.setSelected(true, *gs);
        gs->use_gui_button.setEnabled(false, *gs);

        if(gs->player_id_button.isSelected()){
            gs->game_parameters.type_j1 = "GUI";
            gs->game_parameters.type_j2 = "AI";
        }
        else{
            gs->game_parameters.type_j1 = "AI";
            gs->game_parameters.type_j2 = "GUI";
        }
        gs->ai1_id.setEnabled(true, container);
        gs->ai1_id_incbt.setEnabled(true, container);
        gs->ai1_id_decbt.setEnabled(true, container);
        gs->ai1_id_text.setString("ID de la IA (J1)");
        gs->ai2_id.setEnabled(true, container);
        gs->ai2_id_incbt.setEnabled(true, container);
        gs->ai2_id_decbt.setEnabled(true, container);
        gs->ai2_id_text.setString("ID de la IA (J2)");
        gs->updateSelection(*this);

        gs->ip_box.setEnabled(false, container);
        gs->ip_text.setString(L"Dirección IP / Nombre de dominio");
        gs->port_box.setEnabled(false, container);
    }
    updateButton();
}

void GameSelector::Ninja1Button::onSelectionAction(Window &container)
{
    if(selected){
        GameSelector *gs = static_cast<GameSelector*>(&container);
        gs->game_parameters.server = false;
        gs->game_parameters.random = false;
        gs->game_parameters.private_room = false;
        gs->player_id_button.setEnabled(true, *gs);

        gs->use_gui_button.setSelected(true, *gs);
        gs->use_gui_button.setEnabled(false, *gs);

        if(gs->player_id_button.isSelected()){
            gs->game_parameters.type_j1 = "GUI";
            gs->game_parameters.type_j2 = "Ninja";
            gs->ai2_id.setText("1");
            gs->ai2_id.setEnabled(false, container);
            gs->ai2_id_incbt.setEnabled(false, container);
            gs->ai2_id_decbt.setEnabled(false, container);
            gs->ai2_id_text.setString("ID del ninja (J2)");
            gs->ai1_id.setEnabled(true, container);
            gs->ai1_id_incbt.setEnabled(true, container);
            gs->ai1_id_decbt.setEnabled(true, container);
            gs->ai1_id_text.setString("ID de la IA (J1)");

        }
        else{
            gs->game_parameters.type_j1 = "Ninja";
            gs->game_parameters.type_j2 = "GUI";
            gs->ai1_id.setText("1");
            gs->ai1_id.setEnabled(false, container);
            gs->ai1_id_incbt.setEnabled(false, container);
            gs->ai1_id_decbt.setEnabled(false, container);
            gs->ai1_id_text.setString("ID del ninja (J1)");
            gs->ai2_id.setEnabled(true, container);
            gs->ai2_id_incbt.setEnabled(true, container);
            gs->ai2_id_decbt.setEnabled(true, container);
            gs->ai2_id_text.setString("ID de la IA (J2)");
        }
        gs->updateSelection(*this);

        gs->ip_box.setEnabled(false, container);
        gs->ip_text.setString(L"Dirección IP / Nombre de dominio");
        gs->port_box.setEnabled(false, container);
    }
    updateButton();
}

void GameSelector::Ninja2Button::onSelectionAction(Window &container)
{
    if(selected){
        GameSelector *gs = static_cast<GameSelector*>(&container);
        gs->game_parameters.server = false;
        gs->game_parameters.random = false;
        gs->game_parameters.private_room = false;
        gs->player_id_button.setEnabled(true, *gs);

        gs->use_gui_button.setSelected(true, *gs);
        gs->use_gui_button.setEnabled(false, *gs);

        if(gs->player_id_button.isSelected()){
            gs->game_parameters.type_j1 = "GUI";
            gs->game_parameters.type_j2 = "Ninja";
            gs->ai2_id.setText("2");
            gs->ai2_id.setEnabled(false, container);
            gs->ai2_id_incbt.setEnabled(false, container);
            gs->ai2_id_decbt.setEnabled(false, container);
            gs->ai2_id_text.setString("ID del ninja (J2)");
            gs->ai1_id.setEnabled(true, container);
            gs->ai1_id_incbt.setEnabled(true, container);
            gs->ai1_id_decbt.setEnabled(true, container);
            gs->ai1_id_text.setString("ID de la IA (J1)");

        }
        else{
            gs->game_parameters.type_j1 = "Ninja";
            gs->game_parameters.type_j2 = "GUI";
            gs->ai1_id.setText("2");
            gs->ai1_id.setEnabled(false, container);
            gs->ai1_id_incbt.setEnabled(false, container);
            gs->ai1_id_decbt.setEnabled(false, container);
            gs->ai1_id_text.setString("ID del ninja (J1)");
            gs->ai2_id.setEnabled(true, container);
            gs->ai2_id_incbt.setEnabled(true, container);
            gs->ai2_id_decbt.setEnabled(true, container);
            gs->ai2_id_text.setString("ID de la IA (J2)");
        }
        gs->updateSelection(*this);

        gs->ip_box.setEnabled(false, container);
        gs->ip_text.setString(L"Dirección IP / Nombre de dominio");
        gs->port_box.setEnabled(false, container);
    }
    updateButton();
}

void GameSelector::Ninja3Button::onSelectionAction(Window &container)
{
    if (selected)
    {
        GameSelector *gs = static_cast<GameSelector *>(&container);
        gs->game_parameters.server = false;
        gs->game_parameters.random = false;
        gs->game_parameters.private_room = false;
        gs->player_id_button.setEnabled(true, *gs);

        gs->use_gui_button.setSelected(true, *gs);
        gs->use_gui_button.setEnabled(false, *gs);

        if (gs->player_id_button.isSelected())
        {
            gs->game_parameters.type_j1 = "GUI";
            gs->game_parameters.type_j2 = "Ninja";  
            gs->ai2_id.setText("3");
            gs->ai2_id.setEnabled(false, container);
            gs->ai2_id_incbt.setEnabled(false, container);
            gs->ai2_id_decbt.setEnabled(false, container);
            gs->ai2_id_text.setString("ID del ninja (J2)");
            gs->ai1_id.setEnabled(true, container);
            gs->ai1_id_incbt.setEnabled(true, container);
            gs->ai1_id_decbt.setEnabled(true, container);
            gs->ai1_id_text.setString("ID de la IA (J1)");
        }
        else
        {
            gs->game_parameters.type_j1 = "Ninja";
            gs->game_parameters.type_j2 = "GUI";
            gs->ai1_id.setText("3");
            gs->ai1_id.setEnabled(false, container);
            gs->ai1_id_incbt.setEnabled(false, container);
            gs->ai1_id_decbt.setEnabled(false, container);
            gs->ai1_id_text.setString("ID del ninja (J1)");
            gs->ai2_id.setEnabled(true, container);
            gs->ai2_id_incbt.setEnabled(true, container);
            gs->ai2_id_decbt.setEnabled(true, container);
            gs->ai2_id_text.setString("ID de la IA (J2)");
        }
        gs->updateSelection(*this);

        gs->ip_box.setEnabled(false, container);
        gs->ip_text.setString(L"Dirección IP / Nombre de dominio");
        gs->port_box.setEnabled(false, container);
    }
    updateButton();
}

void GameSelector::HeuristicVSHeuristicButton::onSelectionAction(Window &container)
{
    if(selected){
        GameSelector *gs = static_cast<GameSelector*>(&container);
        gs->game_parameters.server = false;
        gs->game_parameters.random = false;
        gs->game_parameters.private_room = false;

        gs->player_id_button.setEnabled(false, *gs);

        gs->use_gui_button.setEnabled(true, *gs);

        gs->game_parameters.type_j1 = "AI";
        gs->game_parameters.type_j2 = "AI";

        gs->ai1_id.setEnabled(true, container);
        gs->ai1_id_incbt.setEnabled(true, container);
        gs->ai1_id_decbt.setEnabled(true, container);
        gs->ai2_id.setEnabled(true, container);
        gs->ai2_id_incbt.setEnabled(true, container);
        gs->ai2_id_decbt.setEnabled(true, container);

        gs->ai1_id_text.setString("ID de la IA (J1)");
        gs->ai2_id_text.setString("ID de la IA (J2)");

        gs->updateSelection(*this);

        gs->ip_box.setEnabled(false, container);
        gs->ip_text.setString(L"Dirección IP / Nombre de dominio");
        gs->port_box.setEnabled(false, container);
    }

    updateButton();
}

void GameSelector::HeuristicVSNinjaButton::onSelectionAction(Window &container)
{
    if(selected){
        GameSelector *gs = static_cast<GameSelector*>(&container);
        gs->game_parameters.server = false;
        gs->game_parameters.random = false;
        gs->game_parameters.private_room = false;

        gs->player_id_button.setEnabled(false, *gs);
        gs->player_id_button.setSelected(true, *gs);

        gs->use_gui_button.setEnabled(true, *gs);

        gs->game_parameters.type_j1 = "AI";
        gs->game_parameters.type_j2 = "Ninja";

        gs->ai1_id.setEnabled(true, container);
        gs->ai1_id_incbt.setEnabled(true, container);
        gs->ai1_id_decbt.setEnabled(true, container);
        gs->ai2_id.setEnabled(true, container);
        gs->ai2_id_incbt.setEnabled(true, container);
        gs->ai2_id_decbt.setEnabled(true, container);

        gs->ai1_id_text.setString("ID de la IA (J1)");
        gs->ai2_id_text.setString("ID del ninja (J2)");

        gs->updateSelection(*this);

        gs->ip_box.setEnabled(false, container);
        gs->ip_text.setString(L"Dirección IP / Nombre de dominio");
        gs->port_box.setEnabled(false, container);
    }
    
    updateButton();
}

void GameSelector::NinjaVSHeuristicButton::onSelectionAction(Window &container)
{
    if(selected){
        GameSelector *gs = static_cast<GameSelector*>(&container);
        gs->game_parameters.server = false;
        gs->game_parameters.random = false;
        gs->game_parameters.private_room = false;

        gs->player_id_button.setEnabled(false, *gs);
        gs->player_id_button.setSelected(false, *gs);

        gs->use_gui_button.setEnabled(true, *gs);

        gs->game_parameters.type_j1 = "Ninja";
        gs->game_parameters.type_j2 = "AI";

        gs->ai1_id.setEnabled(true, container);
        gs->ai1_id_incbt.setEnabled(true, container);
        gs->ai1_id_decbt.setEnabled(true, container);
        gs->ai2_id.setEnabled(true, container);
        gs->ai2_id_incbt.setEnabled(true, container);
        gs->ai2_id_decbt.setEnabled(true, container);

        gs->ai1_id_text.setString("ID del ninja (J1)");
        gs->ai2_id_text.setString("ID de la IA (J2)");

        gs->updateSelection(*this);

        gs->ip_box.setEnabled(false, container);
        gs->ip_text.setString(L"Dirección IP / Nombre de dominio");
        gs->port_box.setEnabled(false, container);
    }
    
    updateButton();
}

void GameSelector::OnlineClientButton::onSelectionAction(Window &container)
{
    if(selected){
        GameSelector *gs = static_cast<GameSelector*>(&container);
        gs->game_parameters.server = false;
        gs->game_parameters.random = false;
        gs->game_parameters.private_room = false;

        gs->player_id_button.setEnabled(true, *gs);

        gs->use_gui_button.setSelected(true, *gs);
        gs->use_gui_button.setEnabled(false, *gs);

        if(gs->player_id_button.isSelected()){
            gs->game_parameters.type_j1 = "GUI";
            gs->game_parameters.type_j2 = "Remote";
            gs->ai2_id.setEnabled(false, container);
            gs->ai2_id_incbt.setEnabled(false, container);
            gs->ai2_id_decbt.setEnabled(false, container);
            gs->ai1_id.setEnabled(true, container);
            gs->ai1_id_incbt.setEnabled(true, container);
            gs->ai1_id_decbt.setEnabled(true, container);
        }
        else{
            gs->game_parameters.type_j1 = "Remote";
            gs->game_parameters.type_j2 = "GUI";
            gs->ai1_id.setEnabled(false, container);
            gs->ai1_id_incbt.setEnabled(false, container);
            gs->ai1_id_decbt.setEnabled(false, container);
            gs->ai2_id.setEnabled(true, container);
            gs->ai2_id_incbt.setEnabled(true, container);
            gs->ai2_id_decbt.setEnabled(true, container);
        }
        gs->updateSelection(*this);

        gs->ai1_id_text.setString("ID de la IA (J1)");
        gs->ai2_id_text.setString("ID de la IA (J2)");

        gs->ip_box.setEnabled(true, container);
        gs->ip_text.setString(L"Dirección IP / Nombre de dominio");
        gs->port_box.setEnabled(true, container);
    }
    
    updateButton();
}

void GameSelector::OnlineServerButton::onSelectionAction(Window &container)
{
    if(selected){
        GameSelector *gs = static_cast<GameSelector*>(&container);
        gs->player_id_button.setSelected(true, *gs);
        gs->player_id_button.setEnabled(false, *gs);
        gs->use_gui_button.setSelected(true, *gs);
        gs->use_gui_button.setEnabled(false, *gs);

        gs->game_parameters.server = true;
        gs->game_parameters.random = false;
        gs->game_parameters.private_room = false;

        gs->ai1_id.setEnabled(true, container);
        gs->ai1_id_incbt.setEnabled(true, container);
        gs->ai1_id_decbt.setEnabled(true, container);
        gs->ai1_id_text.setString("ID de la IA (Servidor)");
        gs->ai2_id.setEnabled(false, container);
        gs->ai2_id_incbt.setEnabled(false, container);
        gs->ai2_id_decbt.setEnabled(false, container);
        gs->ai2_id_text.setString("-");
        gs->updateSelection(*this);

        gs->ip_box.setEnabled(false, container);
        gs->ip_text.setString(L"Dirección IP / Nombre de dominio");
        gs->port_box.setEnabled(true, container);
    }
    updateButton();
}

void GameSelector::RandomPairingButton::onSelectionAction(Window &container)
{
    if(selected){
        GameSelector *gs = static_cast<GameSelector*>(&container);
        gs->game_parameters.server = false;
        gs->game_parameters.random = true;
        gs->game_parameters.private_room = false;
        gs->player_id_button.setEnabled(false, *gs);
        gs->use_gui_button.setSelected(true, *gs);
        gs->use_gui_button.setEnabled(false, *gs);

        gs->ai1_id.setEnabled(true, container);
        gs->ai1_id_incbt.setEnabled(true, container);
        gs->ai1_id_decbt.setEnabled(true, container);
        gs->ai1_id_text.setString("ID de mi IA");
        gs->ai2_id.setEnabled(false, container);
        gs->ai2_id_incbt.setEnabled(false, container);
        gs->ai2_id_decbt.setEnabled(false, container);
        gs->ai2_id_text.setString("-");

        gs->ip_box.setEnabled(false, container);
        gs->ip_text.setString(L"Dirección IP / Nombre de dominio");
        gs->port_box.setEnabled(false, container);

        gs->updateSelection(*this);

    }
    updateButton();
}

void GameSelector::PrivateRoomButton::onSelectionAction(Window &container)
{
    if(selected){
        GameSelector *gs = static_cast<GameSelector*>(&container);
        gs->game_parameters.server = false;
        gs->game_parameters.random = false;
        gs->game_parameters.private_room = true;
        gs->player_id_button.setEnabled(false, *gs);
        gs->use_gui_button.setSelected(true, *gs);
        gs->use_gui_button.setEnabled(false, *gs);

        gs->ai1_id.setEnabled(true, container);
        gs->ai1_id_incbt.setEnabled(true, container);
        gs->ai1_id_decbt.setEnabled(true, container);
        gs->ai1_id_text.setString("ID de mi IA");
        gs->ai2_id.setEnabled(false, container);
        gs->ai2_id_incbt.setEnabled(false, container);
        gs->ai2_id_decbt.setEnabled(false, container);
        gs->ai2_id_text.setString("-");

        gs->ip_box.setEnabled(true, container);
        gs->ip_text.setString(L"Nombre para la sala");
        gs->port_box.setEnabled(false, container);

        gs->updateSelection(*this);
    }
    updateButton();
}

void GameSelector::UseGUIButton::onSelectionAction(Window &container)
{
    GameSelector *gs = static_cast<GameSelector*>(&container);
    gs->game_parameters.gui = selected;
    updateButton();
}

void GameSelector::PlayerIDButton::onSelectionAction(Window &container)
{
    
    if((selected && id == 2) || (!selected && id == 1)){
        GameSelector *gs = static_cast<GameSelector*>(&container);
        // Swap the type_j1 and type_j2 variables in game_parameters
        swap(gs->game_parameters.type_j1, gs->game_parameters.type_j2);

        // Swap the enabled state ad values between the two id buttons.
        bool e1 = gs->ai1_id.isEnabled();
        gs->ai1_id.setEnabled(gs->ai2_id.isEnabled(), container);
        gs->ai2_id.setEnabled(e1, container);

        String i1 = gs->ai1_id.getText();
        gs->ai1_id.setText(gs->ai2_id.getText());
        gs->ai2_id.setText(i1);

        // Swap also the inc/dec buttons.
        e1 = gs->ai1_id_incbt.isEnabled();
        gs->ai1_id_incbt.setEnabled(gs->ai2_id_incbt.isEnabled(), container);
        gs->ai2_id_incbt.setEnabled(e1, container);

        e1 = gs->ai1_id_decbt.isEnabled();
        gs->ai1_id_decbt.setEnabled(gs->ai2_id_decbt.isEnabled(), container);
        gs->ai2_id_decbt.setEnabled(e1, container);

        if(gs->ninja1_button.isSelected() || gs->ninja2_button.isSelected() || gs->ninja3_button.isSelected()){
            if(selected){
                gs->ai1_id_text.setString("ID de la IA (J1)");
                gs->ai2_id_text.setString("ID del ninja (J2)");
            }else{
                gs->ai1_id_text.setString("ID del ninja (J1)");
                gs->ai2_id_text.setString("ID de la IA (J2)");
            }
        }
    }

    if(selected) id = 1;
    else id = 2;
    
    updateButton();
}



GameSelector::GameSelector() : RenderWindow(VideoMode(1220, 750, VideoMode::getDesktopMode().bitsPerPixel), L"Iniciar partida", Style::Titlebar | Style::Close){

    this->tButtons.loadFromFile("data/textures/game_selection_buttons.png");
    this->tButtons.setSmooth(true);

    this->two_player_button = TwoPlayerButton(tButtons);
    this->vs_heuristic_button = VSHeuristicButton(tButtons);
    this->ninja1_button = Ninja1Button(tButtons);
    this->ninja2_button = Ninja2Button(tButtons);
    this->ninja3_button = Ninja3Button(tButtons);
    this->heuristic_vs_heuristic_button = HeuristicVSHeuristicButton(tButtons);
    this->heuristic_vs_ninja_button = HeuristicVSNinjaButton(tButtons);
    this->ninja_vs_heuristic_button = NinjaVSHeuristicButton(tButtons);
    this->online_client_button = OnlineClientButton(tButtons);
    this->online_server_button = OnlineServerButton(tButtons);
    this->random_pairing_button = RandomPairingButton(tButtons);
    this->private_room_button = PrivateRoomButton(tButtons);
    this->use_gui_button = UseGUIButton(tButtons);
    this->player_id_button = PlayerIDButton(tButtons);
    this->start_game_button = StartGameButton(tButtons);

    this->two_player_button.setPosition(50, 50);

    this->vs_heuristic_button.setPosition(50, 150);
    this->ninja1_button.setPosition(50, 230);
    this->ninja2_button.setPosition(50, 310);
    this->ninja3_button.setPosition(50, 390);

    this->heuristic_vs_heuristic_button.setPosition(450, 50);
    this->heuristic_vs_ninja_button.setPosition(450, 130);
    this->ninja_vs_heuristic_button.setPosition(450, 210);

    this->online_client_button.setPosition(850, 50);
    this->online_server_button.setPosition(850, 130);
    this->random_pairing_button.setPosition(850, 210);
    this->private_room_button.setPosition(850, 290);

    this->use_gui_button.setPosition(200, 550);

    this->player_id_button.setPosition(600, 550);

    this->start_game_button.setPosition(450, 650);

    this->gs_buttons.push_back(&two_player_button);
    this->gs_buttons.push_back(&vs_heuristic_button);
    this->gs_buttons.push_back(&ninja1_button);
    this->gs_buttons.push_back(&ninja2_button);
    this->gs_buttons.push_back(&ninja3_button);
    this->gs_buttons.push_back(&heuristic_vs_heuristic_button);
    this->gs_buttons.push_back(&heuristic_vs_ninja_button);
    this->gs_buttons.push_back(&ninja_vs_heuristic_button);
    this->gs_buttons.push_back(&online_client_button);
    this->gs_buttons.push_back(&online_server_button);
    this->gs_buttons.push_back(&random_pairing_button);
    this->gs_buttons.push_back(&private_room_button);
    this->gs_buttons.push_back(&use_gui_button);
    this->gs_buttons.push_back(&player_id_button);
    this->gs_buttons.push_back(&start_game_button);

    this->exclusive_selection_buttons.push_back(&two_player_button);
    this->exclusive_selection_buttons.push_back(&vs_heuristic_button);
    this->exclusive_selection_buttons.push_back(&ninja1_button);
    this->exclusive_selection_buttons.push_back(&ninja2_button);
    this->exclusive_selection_buttons.push_back(&ninja3_button);
    this->exclusive_selection_buttons.push_back(&heuristic_vs_heuristic_button);
    this->exclusive_selection_buttons.push_back(&heuristic_vs_ninja_button);
    this->exclusive_selection_buttons.push_back(&ninja_vs_heuristic_button);
    this->exclusive_selection_buttons.push_back(&online_client_button);
    this->exclusive_selection_buttons.push_back(&online_server_button);
    this->exclusive_selection_buttons.push_back(&random_pairing_button);
    this->exclusive_selection_buttons.push_back(&private_room_button);

    if(!this->window_fonts.loadFromFile("data/fonts/arial.ttf")){
        std::cout << "Error loading font" << std::endl;
    }

    this->focused_textbox = NULL;

    this->ai1_id = TextBox(window_fonts);
    this->ai1_id_incbt = TextBoxIncDecButton(tButtons, ai1_id, true);
    this->ai1_id_decbt = TextBoxIncDecButton(tButtons, ai1_id, false);
    this->ai1_id.setPosition(Vector2f(550, 340));
    this->ai1_id.setSize(Vector2f(100, 50));
    this->ai1_id_incbt.setPosition(Vector2f(475, 340));
    this->ai1_id_decbt.setPosition(Vector2f(675, 340));
    this->ai1_id.setText("0");
    this->ai1_id.setAllowTyping(false);
    this->ai1_id.setOnlyNumeric(true);
    this->ai1_id.setMaxSize(3);

    this->ai2_id = TextBox(window_fonts);
    this->ai2_id_incbt = TextBoxIncDecButton(tButtons, ai2_id, true);
    this->ai2_id_decbt = TextBoxIncDecButton(tButtons, ai2_id, false);
    this->ai2_id.setPosition(Vector2f(550, 440));
    this->ai2_id.setSize(Vector2f(100, 50));
    this->ai2_id_incbt.setPosition(Vector2f(475, 440));
    this->ai2_id_decbt.setPosition(Vector2f(675, 440));
    this->ai2_id.setText("0");
    this->ai2_id.setAllowTyping(false);
    this->ai2_id.setOnlyNumeric(true);
    this->ai2_id.setMaxSize(3);

    this->ip_box = TextBox(window_fonts);
    this->ip_box.setPosition(Vector2f(850, 400));
    this->ip_box.setSize(Vector2f(320, 30));
    this->ip_box.setAllowTyping(true);
    this->ip_box.setOnlyNumeric(false);
    this->ip_box.setMaxSize(20);

    this->port_box = TextBox(window_fonts);
    this->port_box.setPosition(Vector2f(850, 480));
    this->port_box.setSize(Vector2f(320, 30));
    this->port_box.setAllowTyping(true);
    this->port_box.setOnlyNumeric(true);
    this->port_box.setMaxSize(8);

    this->p1_name = TextBox(window_fonts);
    this->p1_name.setPosition(Vector2f(1000, 575));
    this->p1_name.setSize(Vector2f(170, 30));
    this->p1_name.setAllowTyping(true);
    this->p1_name.setOnlyNumeric(false);
    this->p1_name.setMaxSize(10);
    this->p1_name.setText("J1");

    this->p2_name = TextBox(window_fonts);
    this->p2_name.setPosition(Vector2f(1000, 650));
    this->p2_name.setSize(Vector2f(170, 30));
    this->p2_name.setAllowTyping(true);
    this->p2_name.setOnlyNumeric(false);
    this->p2_name.setMaxSize(10);
    this->p2_name.setText("J2");

    this->ai1_id_text.setFont(window_fonts);
    this->ai1_id_text.setString("ID de la IA (J1)");
    this->ai1_id_text.setPosition(Vector2f(530, 310));
    this->ai1_id_text.setCharacterSize(20);
    this->ai1_id_text.setFillColor(Color::Black);
    this->ai1_id_text.setStyle(Text::Bold);

    this->ai2_id_text.setFont(window_fonts);
    this->ai2_id_text.setString("ID de la IA (J2)");
    this->ai2_id_text.setPosition(Vector2f(530, 410));
    this->ai2_id_text.setCharacterSize(20);
    this->ai2_id_text.setFillColor(Color::Black);
    this->ai2_id_text.setStyle(Text::Bold);

    this->ip_text.setFont(window_fonts);
    this->ip_text.setString(L"Dirección IP / Nombre de dominio");
    this->ip_text.setPosition(Vector2f(850, 375));
    this->ip_text.setCharacterSize(20);
    this->ip_text.setFillColor(Color::Black);
    this->ip_text.setStyle(Text::Bold);

    this->port_text.setFont(window_fonts);
    this->port_text.setString("Puerto");
    this->port_text.setPosition(Vector2f(850, 455));
    this->port_text.setCharacterSize(20);
    this->port_text.setFillColor(Color::Black);
    this->port_text.setStyle(Text::Bold);

    this->p1_name_text.setFont(window_fonts);
    this->p1_name_text.setString("Nombre J1");
    this->p1_name_text.setPosition(Vector2f(1000, 545));
    this->p1_name_text.setCharacterSize(20);
    this->p1_name_text.setFillColor(Color::Black);
    this->p1_name_text.setStyle(Text::Bold);

    this->p2_name_text.setFont(window_fonts);
    this->p2_name_text.setString("Nombre J2");
    this->p2_name_text.setPosition(Vector2f(1000, 620));
    this->p2_name_text.setCharacterSize(20);
    this->p2_name_text.setFillColor(Color::Black);
    this->p2_name_text.setStyle(Text::Bold);


    other_buttons = {&ai1_id_incbt, &ai1_id_decbt, &ai2_id_incbt, &ai2_id_decbt};
    text_boxes = {&ai1_id, &ai2_id, &ip_box, &port_box, &p1_name, &p2_name};
    labels = {&ai1_id_text, &ai2_id_text, &ip_text, &port_text, &p1_name_text, &p2_name_text};

    view = View(FloatRect(0, 0, this->getSize().x, this->getSize().y));
    view.setViewport(FloatRect(0.f, 0.f, 1.f, 1.f));

    this->two_player_button.setSelected(true, *this);

    this->setFramerateLimit(30);
}

void GameSelector::windowLoop(){
    processMouse();
    processEvents();
    if(isOpen()){
        paint();
    }
}

void GameSelector::run(){
    while(isOpen()){
        windowLoop();
    }
}

void GameSelector::processMouse(){
    Vector2i pos = Mouse::getPosition(*this);
    Vector2f world_pos;

    this->setView(view);
    world_pos = this->mapPixelToCoords(pos);

    bool already_hovered = false;

    for (int i = gs_buttons.size() - 1; i >= 0; i--)
    {
        ClickableSprite *current_sprite = gs_buttons[i];
        if (current_sprite->getGlobalBounds().contains(world_pos) && !already_hovered)
        {
            current_sprite->setHovered(true, *this);
            already_hovered = true;
        }
        else
        {
            current_sprite->setHovered(false, *this);
        }
    }


    for (int i = other_buttons.size() - 1; i >= 0; i--)
    {
        ClickableSprite *current_sprite = other_buttons[i];
        if (current_sprite->getGlobalBounds().contains(world_pos) && !already_hovered)
        {
            current_sprite->setHovered(true, *this);
            already_hovered = true;
        }
        else
        {
            current_sprite->setHovered(false, *this);
        }
    }

    for (int i = text_boxes.size() - 1; i >= 0; i--)
    {
        TextBox *current_textbox = text_boxes[i];
        if (current_textbox->getGlobalBounds().contains(world_pos) && !already_hovered)
        {
            current_textbox->setHovered(true, *this);
            already_hovered = true;
        }
        else
        {
            current_textbox->setHovered(false, *this);
        }
    }

    if (!already_hovered)
    {
        this->defaultHover();
    }
}

void GameSelector::processEvents(){
    Event event;

    while (this->pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            this->close();
            exit(0);
        }

        if(event.type == Event::MouseButtonPressed || event.type == Event::MouseButtonReleased){ // Eventos de ratón.
            bool clicked;
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
                clicked = true;
            else
                clicked = false;

            //clicked = true;
            Vector2i pos = Mouse::getPosition(*this);
            Vector2f world_pos;

            cout << pos.x << " " << pos.y << endl;
            //world_pos = window.mapPixelToCoords(pos);

            // Eventos en la vista del tablero.
            this->setView(view);
            world_pos = this->mapPixelToCoords(pos);

            for(int i = gs_buttons.size() - 1; i >= 0; i--){
                ClickableSprite *current_sprite = gs_buttons[i];
                if(clicked && current_sprite->getGlobalBounds().contains(world_pos)){
                    current_sprite->setClicked(true, *this);
                }
                else{
                    current_sprite->setClicked(false, *this);
                }
                
            }

            for(int i = other_buttons.size() - 1; i >= 0; i--){
                ClickableSprite *current_sprite = other_buttons[i];
                if(clicked && current_sprite->getGlobalBounds().contains(world_pos)){
                    current_sprite->setClicked(true, *this);
                }
                else{
                    current_sprite->setClicked(false, *this);
                }
            }

            for(int i = text_boxes.size() - 1; i >= 0; i--){
                TextBox *current_textbox = text_boxes[i];
                if(clicked && current_textbox->getGlobalBounds().contains(world_pos)){
                    current_textbox->setFocused(true, *this);
                }
                else if(clicked){
                    current_textbox->setFocused(false, *this);
                }
            }

        }
    }
    // Eventos de teclado (en el foco activo).
    if (focused_textbox != NULL)
    {
        focused_textbox->processKeys();
    }
}

void GameSelector::paint(){
    this->clear(Color::White);

    this->setView(view);
    for (int i = 0; i < gs_buttons.size(); i++)
    {
        this->draw(*gs_buttons[i]);
    }

    for (int i = 0; i < other_buttons.size(); i++)
    {
        this->draw(*other_buttons[i]);
    }

    for (int i = 0; i < text_boxes.size(); i++)
    {
        text_boxes[i]->draw(*this);
    }

    for (int i = 0; i < labels.size(); i++)
    {
        this->draw(*labels[i]);
    }

    this->display();
}

void GameSelector::defaultHover()
{
    this->setDefaultCursor();
}

void GameSelector::setForbiddenCursor()
{
    if (cursor.loadFromSystem(Cursor::NotAllowed))
        this->setMouseCursor(cursor);
}

void GameSelector::setHandCursor()
{
    if (cursor.loadFromSystem(Cursor::Hand))
        this->setMouseCursor(cursor);
}

void GameSelector::setTextCursor()
{
    if (cursor.loadFromSystem(Cursor::Text))
        this->setMouseCursor(cursor);
}

void GameSelector::setDefaultCursor()
{
    if (cursor.loadFromSystem(Cursor::Arrow))
        this->setMouseCursor(cursor);
}

void GameSelector::updateSelection(GameSelector::StandardGSButton & current_selection){
    // Check if current_selectio belongs to exclusive_selection_buttons vector (call to std::find)
    if(std::find(exclusive_selection_buttons.begin(), exclusive_selection_buttons.end(), &current_selection) != exclusive_selection_buttons.end()){
        // If it does, then we need to deselect all other buttons in the vector
        for(int i = 0; i < exclusive_selection_buttons.size(); i++){
            if(exclusive_selection_buttons[i] != &current_selection){
                exclusive_selection_buttons[i]->setSelected(false, *this);
            }
        }
    }
}

void GameSelector::UseGUIButton::updateButton(){
    if (selected && hovered)
    {
        this->setTextureRect(IntRect(1 * (game_selector_bt_width + game_selector_bt_state_offset), start_pos, game_selector_bt_width + 5, game_selector_bt_height + 5));
    }
    else if (selected)
    {
        this->setTextureRect(IntRect(0 * (game_selector_bt_width + game_selector_bt_state_offset), start_pos, game_selector_bt_width + 5, game_selector_bt_height + 5));
    }
    else if(hovered)
    {
        this->setTextureRect(IntRect(3 * (game_selector_bt_width + game_selector_bt_state_offset), start_pos, game_selector_bt_width + 5, game_selector_bt_height + 5));
    }
    else{
        this->setTextureRect(IntRect(2 * (game_selector_bt_width + game_selector_bt_state_offset), start_pos, game_selector_bt_width + 5, game_selector_bt_height + 5));
    }

    if (enabled)
    {
        this->setColor(Color::White);
    }
    else
    {
        this->setColor(Color(128, 128, 128));
    }
}

void GameSelector::PlayerIDButton::updateButton()
{
    if (selected && hovered)
    {
        this->setTextureRect(IntRect(1 * (game_selector_bt_width + game_selector_bt_state_offset), start_pos, game_selector_bt_width + 5, game_selector_bt_height + 5));
    }
    else if (selected)
    {
        this->setTextureRect(IntRect(0 * (game_selector_bt_width + game_selector_bt_state_offset), start_pos, game_selector_bt_width + 5, game_selector_bt_height + 5));
    }
    else if (hovered)
    {
        this->setTextureRect(IntRect(3 * (game_selector_bt_width + game_selector_bt_state_offset), start_pos, game_selector_bt_width + 5, game_selector_bt_height + 5));
    }
    else
    {
        this->setTextureRect(IntRect(2 * (game_selector_bt_width + game_selector_bt_state_offset), start_pos, game_selector_bt_width + 5, game_selector_bt_height + 5));
    }

    if(enabled){
        this->setColor(Color::White);
    }
    else{
        this->setColor(Color(128, 128, 128));
    }
}

void GameSelector::UseGUIButton::onClickAction(Window & container){
    if(clicked && enabled && !locked){
        this->setSelected(!isSelected(), container);
    }
}

void GameSelector::PlayerIDButton::onClickAction(Window & container){
    if(clicked && enabled && !locked){
        this->setSelected(!isSelected(), container);
    }
}

void GameSelector::StartGameButton::onClickAction(Window & container){
    if(clicked && enabled && !locked){
        GameSelector *gs = static_cast<GameSelector*>(&container);
        gs->game_parameters.id_j1 = stoi(gs->ai1_id.getText());
        gs->game_parameters.id_j2 = stoi(gs->ai2_id.getText());

        gs->game_parameters.ip = gs->ip_box.getText();
        string port = gs->port_box.getText();
        if(port.size() > 0){
            gs->game_parameters.port = stoi(gs->port_box.getText());
        }
        else{
            gs->game_parameters.port = -1;
        }

        gs->game_parameters.config = GROUPED;
        gs->game_parameters.name_j1 = gs->p1_name.getText();
        gs->game_parameters.name_j2 = gs->p2_name.getText();
        gs->game_parameters.ninja_server = false;
        container.close();
    }
}

void GameSelector::StartGameButton::updateButton(){
    if(hovered){
        this->setTextureRect(IntRect(1 * (game_selector_bt_width + game_selector_bt_state_offset), start_pos, game_selector_bt_width + 5, game_selector_bt_height + 5));
    }
    else{
        this->setTextureRect(IntRect(0 * (game_selector_bt_width + game_selector_bt_state_offset), start_pos, game_selector_bt_width + 5, game_selector_bt_height + 5));
    }
}
