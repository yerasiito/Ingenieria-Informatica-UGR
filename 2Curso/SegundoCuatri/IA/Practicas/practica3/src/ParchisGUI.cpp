# include "ParchisGUI.h"
# include "GUIPlayer.h"

#define animation_time 500

const map<Box, vector<Vector2i>> ParchisGUI::box2position{
    // Definición de las casillas normales
    // Para cada casilla definimos 3 posiciones: (1) En el centro de la casilla, (2) y (3) a ambos lados de la casilla para poder colocar 2 fichas en la misma casilla.
    {{1, box_type::normal, color::none}, {Vector2i(746, 310), Vector2i(746, 325), Vector2i(746, 290)}},
    {{2, box_type::normal, color::none}, {Vector2i(708, 310), Vector2i(708, 325), Vector2i(708, 290)}},
    {{3, box_type::normal, color::none}, {Vector2i(670, 310), Vector2i(670, 325), Vector2i(670, 290)}},
    {{4, box_type::normal, color::none}, {Vector2i(632, 310), Vector2i(632, 325), Vector2i(632, 290)}},
    {{5, box_type::normal, color::none}, {Vector2i(594, 310), Vector2i(594, 325), Vector2i(594, 290)}},
    {{6, box_type::normal, color::none}, {Vector2i(556, 310), Vector2i(556, 325), Vector2i(556, 290)}},
    {{7, box_type::normal, color::none}, {Vector2i(518, 310), Vector2i(518, 325), Vector2i(518, 290)}},
    {{8, box_type::normal, color::none}, {Vector2i(482, 310), Vector2i(482, 325), Vector2i(482, 290)}},
    {{9, box_type::normal, color::none}, {Vector2i(462, 289), Vector2i(443, 289), Vector2i(477, 289)}},
    {{10, box_type::normal, color::none}, {Vector2i(462, 253), Vector2i(443, 253), Vector2i(477, 253)}},
    {{11, box_type::normal, color::none}, {Vector2i(462, 215), Vector2i(443, 215), Vector2i(477, 215)}},
    {{12, box_type::normal, color::none}, {Vector2i(462, 177), Vector2i(443, 177), Vector2i(477, 177)}},
    {{13, box_type::normal, color::none}, {Vector2i(462, 139), Vector2i(443, 139), Vector2i(477, 139)}},
    {{14, box_type::normal, color::none}, {Vector2i(462, 100), Vector2i(443, 100), Vector2i(477, 100)}},
    {{15, box_type::normal, color::none}, {Vector2i(462, 63), Vector2i(443, 63), Vector2i(477, 63)}},
    {{16, box_type::normal, color::none}, {Vector2i(462, 25), Vector2i(443, 25), Vector2i(477, 25)}},
    {{17, box_type::normal, color::none}, {Vector2i(384, 25), Vector2i(403, 25), Vector2i(366, 25)}},
    {{18, box_type::normal, color::none}, {Vector2i(310, 25), Vector2i(328, 25), Vector2i(294, 25)}},
    {{19, box_type::normal, color::none}, {Vector2i(310, 63), Vector2i(328, 63), Vector2i(294, 63)}},
    {{20, box_type::normal, color::none}, {Vector2i(310, 100), Vector2i(328, 100), Vector2i(294, 100)}},
    {{21, box_type::normal, color::none}, {Vector2i(310, 139), Vector2i(328, 139), Vector2i(294, 139)}},
    {{22, box_type::normal, color::none}, {Vector2i(310, 177), Vector2i(328, 177), Vector2i(294, 177)}},
    {{23, box_type::normal, color::none}, {Vector2i(310, 215), Vector2i(328, 215), Vector2i(294, 215)}},
    {{24, box_type::normal, color::none}, {Vector2i(310, 253), Vector2i(328, 253), Vector2i(294, 253)}},
    {{25, box_type::normal, color::none}, {Vector2i(310, 289), Vector2i(328, 289), Vector2i(294, 289)}},
    {{26, box_type::normal, color::none}, {Vector2i(288, 310), Vector2i(288, 325), Vector2i(288, 290)}},
    {{27, box_type::normal, color::none}, {Vector2i(253, 310), Vector2i(253, 325), Vector2i(253, 290)}},
    {{28, box_type::normal, color::none}, {Vector2i(216, 310), Vector2i(216, 325), Vector2i(216, 290)}},
    {{29, box_type::normal, color::none}, {Vector2i(178, 310), Vector2i(178, 325), Vector2i(178, 290)}},
    {{30, box_type::normal, color::none}, {Vector2i(139, 310), Vector2i(139, 325), Vector2i(139, 290)}},
    {{31, box_type::normal, color::none}, {Vector2i(101, 310), Vector2i(101, 325), Vector2i(101, 290)}},
    {{32, box_type::normal, color::none}, {Vector2i(64, 310), Vector2i(64, 325), Vector2i(64, 290)}},
    {{33, box_type::normal, color::none}, {Vector2i(25, 310), Vector2i(25, 325), Vector2i(25, 290)}},
    {{34, box_type::normal, color::none}, {Vector2i(25, 385), Vector2i(25, 366), Vector2i(25, 403)}},
    {{35, box_type::normal, color::none}, {Vector2i(25, 462), Vector2i(25, 444), Vector2i(25, 478)}},
    {{36, box_type::normal, color::none}, {Vector2i(64, 462), Vector2i(64, 444), Vector2i(64, 478)}},
    {{37, box_type::normal, color::none}, {Vector2i(101, 462), Vector2i(101, 444), Vector2i(101, 478)}},
    {{38, box_type::normal, color::none}, {Vector2i(139, 462), Vector2i(139, 444), Vector2i(139, 478)}},
    {{39, box_type::normal, color::none}, {Vector2i(178, 462), Vector2i(178, 444), Vector2i(178, 478)}},
    {{40, box_type::normal, color::none}, {Vector2i(216, 462), Vector2i(216, 444), Vector2i(216, 478)}},
    {{41, box_type::normal, color::none}, {Vector2i(253, 462), Vector2i(253, 444), Vector2i(253, 478)}},
    {{42, box_type::normal, color::none}, {Vector2i(288, 462), Vector2i(288, 444), Vector2i(288, 478)}},
    {{43, box_type::normal, color::none}, {Vector2i(310, 480), Vector2i(328, 480), Vector2i(294, 480)}},
    {{44, box_type::normal, color::none}, {Vector2i(310, 517), Vector2i(328, 517), Vector2i(294, 517)}},
    {{45, box_type::normal, color::none}, {Vector2i(310, 555), Vector2i(328, 555), Vector2i(294, 555)}},
    {{46, box_type::normal, color::none}, {Vector2i(310, 593), Vector2i(328, 593), Vector2i(294, 593)}},
    {{47, box_type::normal, color::none}, {Vector2i(310, 632), Vector2i(328, 632), Vector2i(294, 632)}},
    {{48, box_type::normal, color::none}, {Vector2i(310, 669), Vector2i(328, 669), Vector2i(294, 669)}},
    {{49, box_type::normal, color::none}, {Vector2i(310, 707), Vector2i(328, 707), Vector2i(294, 707)}},
    {{50, box_type::normal, color::none}, {Vector2i(310, 746), Vector2i(328, 746), Vector2i(294, 746)}},
    {{51, box_type::normal, color::none}, {Vector2i(384, 746), Vector2i(366, 746), Vector2i(403, 746)}},
    {{52, box_type::normal, color::none}, {Vector2i(462, 746), Vector2i(443, 746), Vector2i(477, 746)}},
    {{53, box_type::normal, color::none}, {Vector2i(462, 707), Vector2i(443, 707), Vector2i(477, 707)}},
    {{54, box_type::normal, color::none}, {Vector2i(462, 669), Vector2i(443, 669), Vector2i(477, 669)}},
    {{55, box_type::normal, color::none}, {Vector2i(462, 632), Vector2i(443, 632), Vector2i(477, 632)}},
    {{56, box_type::normal, color::none}, {Vector2i(462, 593), Vector2i(443, 593), Vector2i(477, 593)}},
    {{57, box_type::normal, color::none}, {Vector2i(462, 555), Vector2i(443, 555), Vector2i(477, 555)}},
    {{58, box_type::normal, color::none}, {Vector2i(462, 517), Vector2i(443, 517), Vector2i(477, 517)}},
    {{59, box_type::normal, color::none}, {Vector2i(462, 480), Vector2i(443, 480), Vector2i(477, 480)}},
    {{60, box_type::normal, color::none}, {Vector2i(482, 462), Vector2i(482, 444), Vector2i(482, 478)}},
    {{61, box_type::normal, color::none}, {Vector2i(518, 462), Vector2i(518, 444), Vector2i(518, 478)}},
    {{62, box_type::normal, color::none}, {Vector2i(556, 462), Vector2i(556, 444), Vector2i(556, 478)}},
    {{63, box_type::normal, color::none}, {Vector2i(594, 462), Vector2i(594, 444), Vector2i(594, 478)}},
    {{64, box_type::normal, color::none}, {Vector2i(632, 462), Vector2i(632, 444), Vector2i(632, 478)}},
    {{65, box_type::normal, color::none}, {Vector2i(670, 462), Vector2i(670, 444), Vector2i(670, 478)}},
    {{66, box_type::normal, color::none}, {Vector2i(708, 462), Vector2i(708, 444), Vector2i(708, 478)}},
    {{67, box_type::normal, color::none}, {Vector2i(746, 462), Vector2i(746, 444), Vector2i(746, 478)}},
    {{68, box_type::normal, color::none}, {Vector2i(746, 385), Vector2i(746, 366), Vector2i(746, 403)}},

    // Definición de los pasillos de colores hacia la meta
    // Para cada casilla definimos 3 posiciones: (1) En el centro de la casilla, (2) y (3) a ambos lados de la casilla para poder colocar 2 fichas en la misma casilla.
    // Pasillo rojo
    {{1, box_type::final_queue, color::red}, {Vector2i(63, 385), Vector2i(63, 366), Vector2i(63, 403)}},
    {{2, box_type::final_queue, color::red}, {Vector2i(101, 385), Vector2i(101, 366), Vector2i(101, 403)}},
    {{3, box_type::final_queue, color::red}, {Vector2i(139, 385), Vector2i(139, 366), Vector2i(139, 403)}},
    {{4, box_type::final_queue, color::red}, {Vector2i(177, 385), Vector2i(177, 366), Vector2i(177, 403)}},
    {{5, box_type::final_queue, color::red}, {Vector2i(215, 385), Vector2i(215, 366), Vector2i(215, 403)}},
    {{6, box_type::final_queue, color::red}, {Vector2i(253, 385), Vector2i(253, 366), Vector2i(253, 403)}},
    {{7, box_type::final_queue, color::red}, {Vector2i(291, 385), Vector2i(291, 366), Vector2i(291, 403)}},

    // Pasillo amarillo
    {{7, box_type::final_queue, color::yellow}, {Vector2i(480, 385), Vector2i(480, 366), Vector2i(480, 403)}},
    {{6, box_type::final_queue, color::yellow}, {Vector2i(518, 385), Vector2i(518, 366), Vector2i(518, 403)}},
    {{5, box_type::final_queue, color::yellow}, {Vector2i(556, 385), Vector2i(556, 366), Vector2i(556, 403)}},
    {{4, box_type::final_queue, color::yellow}, {Vector2i(594, 385), Vector2i(594, 366), Vector2i(594, 403)}},
    {{3, box_type::final_queue, color::yellow}, {Vector2i(632, 385), Vector2i(632, 366), Vector2i(632, 403)}},
    {{2, box_type::final_queue, color::yellow}, {Vector2i(670, 385), Vector2i(670, 366), Vector2i(670, 403)}},
    {{1, box_type::final_queue, color::yellow}, {Vector2i(708, 385), Vector2i(708, 366), Vector2i(708, 403)}},

    // Pasillo verde
    {{1, box_type::final_queue, color::green}, {Vector2i(384, 707), Vector2i(366, 707), Vector2i(403, 707)}},
    {{2, box_type::final_queue, color::green}, {Vector2i(384, 669), Vector2i(366, 669), Vector2i(403, 669)}},
    {{3, box_type::final_queue, color::green}, {Vector2i(384, 632), Vector2i(366, 632), Vector2i(403, 632)}},
    {{4, box_type::final_queue, color::green}, {Vector2i(384, 593), Vector2i(366, 593), Vector2i(403, 593)}},
    {{5, box_type::final_queue, color::green}, {Vector2i(384, 555), Vector2i(366, 555), Vector2i(403, 555)}},
    {{6, box_type::final_queue, color::green}, {Vector2i(384, 517), Vector2i(366, 517), Vector2i(403, 517)}},
    {{7, box_type::final_queue, color::green}, {Vector2i(384, 480), Vector2i(366, 480), Vector2i(403, 480)}},

    // Pasillo azul
    {{7, box_type::final_queue, color::blue}, {Vector2i(384, 289), Vector2i(366, 289), Vector2i(403, 289)}},
    {{6, box_type::final_queue, color::blue}, {Vector2i(384, 253), Vector2i(366, 253), Vector2i(403, 253)}},
    {{5, box_type::final_queue, color::blue}, {Vector2i(384, 215), Vector2i(366, 215), Vector2i(403, 215)}},
    {{4, box_type::final_queue, color::blue}, {Vector2i(384, 177), Vector2i(366, 177), Vector2i(403, 177)}},
    {{3, box_type::final_queue, color::blue}, {Vector2i(384, 139), Vector2i(366, 139), Vector2i(403, 139)}},
    {{2, box_type::final_queue, color::blue}, {Vector2i(384, 100), Vector2i(366, 100), Vector2i(403, 100)}},
    {{1, box_type::final_queue, color::blue}, {Vector2i(384, 63), Vector2i(366, 63), Vector2i(403, 63)}},

    // Casillas destino
    // Ponemos 4 posiciones, correspondientes a las 4 fichas
    // Verdes
    {{0, box_type::goal, color::green}, {Vector2i(384, 440), Vector2i(384, 408), Vector2i(415, 440), Vector2i(350, 440)}},
    // Azules
    {{0, box_type::goal, color::blue}, {Vector2i(384, 326), Vector2i(384, 354), Vector2i(415, 326), Vector2i(350, 326)}},
    // Rojas
    {{0, box_type::goal, color::red}, {Vector2i(329, 385), Vector2i(360, 385), Vector2i(329, 350), Vector2i(329, 420)}},
    // Amarillas
    {{0, box_type::goal, color::yellow}, {Vector2i(445, 385), Vector2i(412, 385), Vector2i(445, 350), Vector2i(445, 420)}},

    // Casillas home
    // Ponemos 4 posiciones, correspondientes a las 4 fichas
    // Verdes
    {{0, box_type::home, color::green}, {Vector2i(632, 594), Vector2i(594, 632), Vector2i(632, 670), Vector2i(670, 632)}},
    // Azules
    {{0, box_type::home, color::blue}, {Vector2i(139, 101), Vector2i(101, 139), Vector2i(139, 177), Vector2i(177, 139)}},
    // Rojas
    {{0, box_type::home, color::red}, {Vector2i(139, 594), Vector2i(101, 632), Vector2i(139, 670), Vector2i(177, 632)}},
    // Amarillas
    {{0, box_type::home, color::yellow}, {Vector2i(632, 101), Vector2i(594, 139), Vector2i(632, 177), Vector2i(670, 139)}},
};

const string ParchisGUI::background_theme_file = "data/music/background_theme";

const string ParchisGUI::background_theme_hurryup_file = "data/music/background_theme_hurryup";

const string ParchisGUI::icon_file = "data/textures/icon_parchis.png";

const IntRect ParchisGUI::turns_arrow_rect = IntRect(0, 280, 112, 112);

const map<color, int> ParchisGUI::color2turns_arrow_pos = 
{
    {yellow, 50},
    {blue, 130},
    {red, 210},
    {green, 290}
};

const string ParchisGUI::sound_move_file = "data/music/teleport";

const string ParchisGUI::sound_boing_file = "data/music/boing";

const string ParchisGUI::sound_forbidden_file = "data/music/nope";

const string ParchisGUI::sound_eaten_file = "data/music/bad_news";

const string ParchisGUI::sound_applause_file = "data/music/applause";

const float ParchisGUI::ASPECT_RATIO = 2.0f;

const int ParchisGUI::getInitialWindowWidth(){
    return ParchisGUI::getInitialWindowHeight() * ASPECT_RATIO;
}

const int ParchisGUI::getInitialWindowHeight(){
    int screen_height = VideoMode::getDesktopMode().height;
    int screen_width = VideoMode::getDesktopMode().width;
    cout << "Screen dimension: " << screen_width << "x" << screen_height << endl;
    // Check if the quotient is larger than 2*16:9
    if ((float)screen_width / screen_height > 16.0f / 9.0f){
        screen_width /= 2; // Quizás dos monitores
    }
    // Compare with the standard monitor resolutions.
    if(screen_width <= 1366 && screen_height <= 768){
        return 600;
    }
    else if(screen_width <= 1600 && screen_height <= 900){
        return 750;
    }
    else if(screen_width <= 1920 && screen_height <= 1080){
        return 800;
    }
    else if(screen_width <= 2304 && screen_height <= 1440){
        cout << "Así que estás usando un MAC eh? :)" << endl;
        return 1000;
    }
    else if(screen_width <= 2560 && screen_height <= 1440){
        return 1100;
    }
    else if(screen_width <= 2560 && screen_height <= 1600){
        if(screen_width == 2560 && screen_height == 1600) cout << "Así que estás usando un MAC eh? :)" << endl;
        return 1200;
    }
    else if(screen_width <= 2880 && screen_height <= 1800){
        if (screen_width == 2880 && screen_height == 1800) cout << "Así que estás usando un MAC eh? :)" << endl;
        return 1300;
    }
    else if(screen_width <= 3000 && screen_height <= 2000){
        return 1400;
    }
    else if(screen_width <= 3200 && screen_height <= 1800){
        return 1400;
    }
    else if(screen_width <= 3840 && screen_height <= 2160){
        return 1600;
    }
    else{
        cout << "MADRE MÍA, QUÉ PEDAZO DE PANTALLA ESTAS USANDO?" << endl;
        cout << min(screen_height, (int)(screen_width / ASPECT_RATIO)) - 200 << endl;
        return min(screen_height, (int)(screen_width / ASPECT_RATIO))- 700;
    }
}

ParchisGUI::ParchisGUI(Parchis &model)
    : RenderWindow(VideoMode(getInitialWindowWidth(), getInitialWindowHeight(), VideoMode::getDesktopMode().bitsPerPixel), L"Parchís", Style::Titlebar | Style::Close | Style::Resize),
    game_thread(&ParchisGUI::gameLoop, this)
    // L"string" parece que permite representar caraceteres unicode. Útil para acentos y demás.
{
    this->model = &model;

    this->clicked = false;

    this->last_dice = -1;
    this->gui_turn = 1;

    //Cargamos las texturas
    this->tBackground.loadFromFile("data/textures/background.png");
    this->tPieces.loadFromFile("data/textures/fichas_parchis_extended.png");
    this->tPieces.setSmooth(true);
    this->tBoard.loadFromFile("data/textures/parchis_board_resized.png");
    this->tBoard.setSmooth(true);
    this->tDices.loadFromFile("data/textures/dice_extended.png");
    this->tDices.setSmooth(true);
    this->tSkipBt.loadFromFile("data/textures/skip_buttons.png");
    this->tSkipBt.setSmooth(true);
    this->tButtons.loadFromFile("data/textures/buttons.png");
    this->tButtons.setSmooth(true);

    //Definimos los sprites
    this->background = Sprite(tBackground);
    this->background.setPosition(1000, 1000);
    //this->boards.push_back(BoardSprite(tBoard));
    this->board = BoardSprite(tBoard);

    // Vector de colores (ver cómo se podría obtener directamente del enumerado)
    vector<color> colors = {yellow, blue, red, green};

    // Creación de las fichas
    for(int i = 0; i < colors.size(); i++){
        color col = colors[i];
        vector<PieceSprite> col_pieces_sprites;
        for(int j = 0; j < model.getBoard().getPieces(color::red).size(); j++){
            col_pieces_sprites.push_back(PieceSprite(tPieces, j, col));
            //col_pieces_sprites[j].setPosition((Vector2f)box2position.at(model.getBoard().getPiece(col, j))[j]);
            col_pieces_sprites[j].setPosition(box3position(col, j, 0));
        }
        pieces.insert({col, col_pieces_sprites});
    }

    //Creación de los dados
    Vector2i ini_pos(900, 50);
    Vector2i offset(70,80);

    for (int i = 0; i < colors.size(); i++){
        for (int j = 1; j <= 6; j++){
            dices[colors[i]].push_back(DiceSprite(tDices, j, colors[i]));
            Vector2i pos = ini_pos + Vector2i((j-1)*offset.x, i*offset.y);
            dices[colors[i]][j-1].setPosition(pos.x, pos.y);
        } 
        //special_10_20_dice[colors[i]].setNumber(20);
        //special_10_20_dice[colors[i]].setModelColor(colors[i]);
        special_10_20_dice[colors[i]].push_back(DiceSprite(tDices, -1, colors[i]));
        special_10_20_dice[colors[i]][0].setPosition(ini_pos.x + offset.x*6, ini_pos.y + offset.y*i);
    }

    

    // Creación de los botones
    this->skip_turn_button = SkipTurnButton(tSkipBt);
    this->skip_turn_button.setPosition(Vector2f(850, 400));
    this->skip_turn_button.setScale(Vector2f(0.55, 0.55));

    this->move_heuristic_button = MoveHeuristicButton(tButtons);
    this->move_heuristic_button.setPosition(Vector2f(1050, 400));

    this->auto_heuristic_button = AutoHeuristicButton(tButtons);
    this->auto_heuristic_button.setPosition(Vector2f(1050, 464));

    this->music_on_off_button = MusicOnOffButton(tButtons);
    this->music_on_off_button.setPosition(Vector2f(850, 550));

    this->sound_on_off_button = SoundOnOffButton(tButtons);
    this->sound_on_off_button.setPosition(Vector2f(960, 550));

    // Flecha de turnos.
    this->turns_arrow = Sprite(tButtons);
    this->turns_arrow.setTextureRect(turns_arrow_rect);
    this->turns_arrow.setPosition(Vector2f(850, 50));
    this->turns_arrow.setScale(Vector2f(0.5, 0.5));
    this->turns_arrow.setColor(Color::Yellow);

    // Agrupación de los canales de animación.
    this->all_animators.push_back(&this->animations_ch1);
    this->all_animators.push_back(&this->animations_ch2);
    this->all_animators.push_back(&this->animations_ch3);
    this->all_animators.push_back(&this->animations_ch4);

    //Creación de las vistas
    general_view = View(FloatRect(1000, 1000, 1600, 800));
    general_view.setViewport(FloatRect(0.f, 0.f, 1.f, 1.f));

    board_view = View(FloatRect(0.f, 0.f, 800.f, 800.f));
    board_view.setViewport(FloatRect(0.f, 0.f, 0.5f, 1.f));

    dice_view = View(FloatRect(800.f, 50.f, 720.f, 320.f));
    dice_view.setViewport(FloatRect(800.f / 1600.f, 50.f / 800.f, 720.f / 1600.f, 320.f / 800.f));

    bt_panel_view = View(FloatRect(850.f, 400.f, 600.f, 600.f));
    bt_panel_view.setViewport(FloatRect(850.f / 1600.f, 400.f / 800.f, 600.f / 1600.f, 600.f / 800.f));

    rotate_board = false;
    rotate_angle0 = 0.0;


    collectSprites();

    this->animation_lock = false;
    this->not_playable_lock = false;
    this->updateSprites();

    //Música
    this->initializeBackgroundMusic();
    this->setBackgroundMusic(false);
    //Sonidos
    this->initializeSoundEffects();
    this->setSoundEffects(false);

    //Icono de la ventana.
    if(icon.loadFromFile(icon_file)){
        this->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }else{
        cout << "Icon could not be loaded" << endl;
    }

    this->avg_fps = 0.0;
    this->total_frames = 0;
    this->setFramerateLimit(60);

    // Inicialización de la hebra.
    // this->call_thread_start = false;

    this->startGameLoop();


}

void ParchisGUI::collectSprites(){
    // Tablero como sprite dibujable (IMPORTANTE: Añadir a all_drawable_sprites en el orden en que se dibujan)
    all_drawable_sprites.push_back(&background);
    general_drawable_sprites.push_back(&background);

    all_drawable_sprites.push_back(&board);
    board_drawable_sprites.push_back(&board);
    all_clickable_sprites.push_back(&board);
    board_clickable_sprites.push_back(&board);

    // Vector de colores (ver cómo se podría obtener directamente del enumerado)
    vector<color> colors = {red, blue, green, yellow};

    for (int i = 0; i < colors.size(); i++)
    {
        color col = colors[i];
        // Añadir fichas como dibujables y clickables.
        for(int j = 0; j < pieces[col].size(); j++){
            all_drawable_sprites.push_back(&pieces[col][j]);
            all_clickable_sprites.push_back(&pieces[col][j]);
            board_drawable_sprites.push_back(&pieces[col][j]);
            board_clickable_sprites.push_back(&pieces[col][j]);
        }

        // Añadir dados como dibujables y clickables.
        for(int j = 0; j < dices[col].size(); j++){
            all_drawable_sprites.push_back(&dices[col][j]);
            all_clickable_sprites.push_back(&dices[col][j]);
            dice_drawable_sprites.push_back(&dices[col][j]);
            dice_clickable_sprites.push_back(&dices[col][j]);
        }

        // Añadir dados especiales como dibujables y clickables.
        all_drawable_sprites.push_back(&special_10_20_dice[col][0]);
        all_clickable_sprites.push_back(&special_10_20_dice[col][0]);
        dice_drawable_sprites.push_back(&special_10_20_dice[col][0]);
        dice_clickable_sprites.push_back(&special_10_20_dice[col][0]);
    }

    // Añadir flecha de turnos como dibujable.
    all_drawable_sprites.push_back(&turns_arrow);
    dice_drawable_sprites.push_back(&turns_arrow);

    // Añadir botones como dibujables y clickables.
    vector<ClickableSprite*> buttons = {&skip_turn_button, &move_heuristic_button, &auto_heuristic_button, &music_on_off_button, &sound_on_off_button};

    for(int i = 0; i < buttons.size(); i++){
        all_drawable_sprites.push_back(buttons[i]);
        all_clickable_sprites.push_back(buttons[i]);
        bt_panel_drawable_sprites.push_back(buttons[i]);
        bt_panel_clickable_sprites.push_back(buttons[i]);
    }
}

void ParchisGUI::mainLoop(){
    processSettings();
    processMouse();
    processEvents();
    processAnimations();
    paint();

    //if(this->call_thread_start){
    //    this->startGameLoop();
    //}

    current_time = game_clock.restart().asSeconds();
    fps = 1.f / (current_time);
    avg_fps = (avg_fps * total_frames + fps) / (total_frames + 1);
    total_frames++;
    //last_time = current_time;
    //cout << "Current FPS: " << fps << "\tAverage FPS: " << avg_fps << endl; //"\tTotal frames: " << total_frames << endl;
}

void ParchisGUI::gameLoop(){
    model->gameLoop();

    /*
    last_dice = -1;
    updateSprites();

    this->setThinkingCursor();
    // Para evitar que se anime todo de golpe (es un poco chapuza, pensar otra forma de hacerlo).
    while(!animations_ch1.empty()){
        sleep(milliseconds(10));
    }
    while (!model->gameOver() && model->gameStep())
    {
        // cout << "----ParchisGUI----" << endl;
        // cout << "Moved from agent: queuing moves" << endl;
        // cout << "Jugador actual: " << model->getCurrentPlayerId() << endl;
        // cout << "Color actual: " << str(model->getCurrentColor()) << endl;

        // Esta parte del código pordría realizarla el perceive del GUIPlayer (?)
        // Así se podría tener solo un gameLoop en Parchis y no tener que cambiar para la versión de GUI o de terminal.
        vector<tuple<color, int, Box, Box>> last_moves = model->getLastMoves();
        //last_dice = model->getLastDice();
        //updateSprites();
        
        for (int i = 0; i < last_moves.size(); i++){
            color col = get<0>(last_moves[i]);
            int id = get<1>(last_moves[i]);
            Box origin = get<2>(last_moves[i]);
            Box dest = get<3>(last_moves[i]);

            cout << col << " " << id << " " << origin.num << " " << dest.num << endl;

            queueMove(col, id, origin, dest);
            //cout << "HOLAAA" << endl;
        }

        last_dice = -1;
        updateSprites();

        while (!animations_ch1.empty()){
            sleep(milliseconds(10));
        }
    }

    this->setDefaultCursor();
    */
}

void ParchisGUI::startGameLoop(){
    this->game_thread.launch();
    //this->call_thread_start = true;
    //if(this->game_thread.joinable()){
    //this->game_thread = thread(&ParchisGUI::gameLoop, this);
    //this->call_thread_start = false;
    //}
    
}

void ParchisGUI::processMouse(){
    Vector2i pos = Mouse::getPosition(*this);
    Vector2f world_pos;

    this->setView(board_view);
    world_pos = this->mapPixelToCoords(pos);

    bool already_hovered = false;

    for(int i = board_clickable_sprites.size() - 1; i >= 0; i--){
        ClickableSprite *current_sprite = board_clickable_sprites[i];
        if(current_sprite->getGlobalBounds().contains(world_pos) && !already_hovered){
            current_sprite->setHovered(true, *this);
            already_hovered = true;
        }
        else{
            current_sprite->setHovered(false, *this);
        }
    }

    this->setView(dice_view);
    world_pos = this->mapPixelToCoords(pos);

    for (int i = dice_clickable_sprites.size() - 1; i >= 0; i--)
    {
        ClickableSprite *current_sprite = dice_clickable_sprites[i];
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

    this->setView(bt_panel_view);
    world_pos = this->mapPixelToCoords(pos);

    for (int i = bt_panel_clickable_sprites.size() - 1; i >= 0; i--)
    {
        ClickableSprite *current_sprite = bt_panel_clickable_sprites[i];
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

    if(!already_hovered){
        this->defaultHover();
    }

}

void ParchisGUI::defaultHover(){
    this->setDefaultCursor();
}

void ParchisGUI::processEvents(){
    // Gestión de eventos (processEvents())
    Event event;
    while (this->pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            this->close();
            cout << "Finalizando partida (por la fuerza)..." << endl;
            model->endGame();
            game_thread.wait();
        }

        if(event.type == Event::MouseButtonPressed || event.type == Event::MouseButtonReleased){ // Eventos de ratón.
            //cout << pos.x << " " << pos.y << " " << world_pos.x << " " << world_pos.y << endl;
            //cout << board.getGlobalBounds().top << " " << board.getGlobalBounds().left << endl;
            bool clicked;
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
                clicked = true;
            else
                clicked =false;

            //clicked = true;
            Vector2i pos = Mouse::getPosition(*this);
            Vector2f world_pos;

            cout << pos.x << " " << pos.y << endl;
            //world_pos = window.mapPixelToCoords(pos);
            vector<color> colors = {red, blue, green, yellow};

            // Eventos en la vista del tablero.
            this->setView(board_view);
            world_pos = this->mapPixelToCoords(pos);

            for(int i = board_clickable_sprites.size() - 1; i >= 0; i--){
                ClickableSprite *current_sprite = board_clickable_sprites[i];
                if(clicked && current_sprite->getGlobalBounds().contains(world_pos)){
                    current_sprite->setClicked(true, *this);
                }
                else{
                    current_sprite->setClicked(false, *this);
                }
                
            }


            // Eventos en la vista de los dados.
            this->setView(dice_view);
            world_pos = this->mapPixelToCoords(pos);

            for(int i = dice_clickable_sprites.size() - 1; i >= 0; i--){
                ClickableSprite *current_sprite = dice_clickable_sprites[i];
                if (clicked && current_sprite->getGlobalBounds().contains(world_pos)){
                    current_sprite->setClicked(true, *this);
                }
                else{
                    current_sprite->setClicked(false, *this);
                }
            }

            // Eventos en la vista del panel de botones.
            this->setView(bt_panel_view);
            world_pos = this->mapPixelToCoords(pos);

            for(int i = bt_panel_clickable_sprites.size() - 1; i >= 0; i--){
                ClickableSprite *current_sprite = bt_panel_clickable_sprites[i];
                if (clicked && current_sprite->getGlobalBounds().contains(world_pos)){
                    current_sprite->setClicked(true, *this);
                }
                else{
                    current_sprite->setClicked(false, *this);
                }
            }
            
        }

        if(event.type == Event::Resized){
            // resizing = true; // Variable deprecada.
            Vector2u preaspect_size = this->getSize();
            Vector2u realsize(preaspect_size.y * ASPECT_RATIO, preaspect_size.y);
            float ratio = (float)preaspect_size.x / (float)preaspect_size.y;
            float apply_ratio = ratio / 2.0f;
            float viewport_start = 0.5f - apply_ratio / 2.0f;
            float inv_ratio = 1.0f / apply_ratio;
            float inv_viewport_start = 0.5f - inv_ratio / 2.f;
            if(ratio < 2.0f){

                general_view.setViewport(FloatRect(0.f, viewport_start + apply_ratio * 0.f, 1.f, apply_ratio * 1.0f));
                board_view.setViewport(FloatRect(0.f, viewport_start + apply_ratio * 0.f, 0.5f, apply_ratio * 1.f));
                dice_view.setViewport(FloatRect(800.f / 1600.f, viewport_start + apply_ratio * 50.f / 800.f, 720.f / 1600.f, apply_ratio * 320.f / 800.f));
                bt_panel_view.setViewport(FloatRect(850.f / 1600.f, viewport_start + apply_ratio * 400.f / 800.f, 600.f / 1600.f, apply_ratio * 600.f / 800.f));
            }
            else{
                general_view.setViewport(FloatRect(inv_viewport_start + inv_ratio * 0.f, 0.f, inv_ratio * 1.f, 1.f));
                board_view.setViewport(FloatRect(inv_viewport_start + inv_ratio * 0.f, 0.f, inv_ratio * 0.5f, 1.f));
                dice_view.setViewport(FloatRect(inv_viewport_start + inv_ratio * 800.f / 1600.f, 50.f / 800.f, inv_ratio * 720.f / 1600.f, 320.f / 800.f));
                bt_panel_view.setViewport(FloatRect(inv_viewport_start + inv_ratio * 850.f / 1600.f, 400.f / 800.f, inv_ratio * 600.f / 1600.f, 600.f / 800.f));
            }

            //this->setSize(realsize);
        }
    }
}

void ParchisGUI::processAnimations()
{
    /*
    list<SpriteAnimator>::iterator it;
    for (it = animations.begin(); it != animations.end();)
    {
        it->update();
        if(it->hasEnded()){
            it = animations.erase(it);
        }
        else{
            ++it;
        }
    }
    */

   for(int i = 0; i < all_animators.size(); i++){
        queue<SpriteAnimator>* animations_ch_i = all_animators[i];
        if(!animations_ch_i->empty()){
            SpriteAnimator sa_i = animations_ch_i->front();
            sa_i.update();
            if(sa_i.hasEnded()){
                animations_ch_i->pop();
                if(!animations_ch_i->empty()){
                    animations_ch_i->front().setStartPosition();
                    animations_ch_i->front().restart();
                }
                if (i == 0)
                {
                    void (ParchisGUI::*callback)(void) = animation_ch1_callbacks.front();
                    if (callback != NULL)
                        (this->*callback)();
                    animation_ch1_callbacks.pop();
                }
            }
        }
    }

}

void ParchisGUI::processSettings(){
    if(rotate_board){
        Vector2i pos = Mouse::getPosition(*this);
        FloatRect board_box = board.getGlobalBounds();
        Vector2f board_center(board_box.left + board_box.width / 2, board_box.top + board_box.height / 2);

        float angle = atan2(pos.x - board_center.x, pos.y - board_center.y) * 180.f / PI;

        board_view.rotate(angle - rotate_angle0);
        rotate_angle0 = angle;
    }
    // Keep aspect ratio.
    //Vector2u preaspect_size = this->getSize();
    //Vector2u realsize(preaspect_size.y * ASPECT_RATIO, preaspect_size.y);
    //this->setSize(realsize);
}

void ParchisGUI::paint(){
    this->clear(Color::White);

    //Dibujamos elementos generales (sin vistas)
    this->setView(general_view);
    for(int i = 0; i < general_drawable_sprites.size(); i++){
        this->draw(*general_drawable_sprites[i]);
    }
    //Dibujamos elementos de la vista del tablero.
    this->setView(board_view);
    for(int i = 0; i < board_drawable_sprites.size(); i++){
        this->draw(*board_drawable_sprites[i]);
    }

    // Dibujamos elementos de la vista de los dados.
    this->setView(dice_view);
    for (int i = 0; i < dice_drawable_sprites.size(); i++)
    {
        this->draw(*dice_drawable_sprites[i]);
    }

    // Dibujamos elementos de la vista de los botones
    this->setView(bt_panel_view);
    for (int i = 0; i < bt_panel_drawable_sprites.size(); i++)
    {
        this->draw(*bt_panel_drawable_sprites[i]);
    }

    this->display();

}

void ParchisGUI::updateSprites(){
    vector<color> colors = Parchis::game_colors;
    if(model->isEatingMove()){
        cout << "TOCA CONTARSE 20" << endl;
        this->last_dice = 20;
    }
    if(model->isGoalMove()){
        cout << "TOCA CONTARSE 10" << endl;
        this->last_dice = 10;
        checkHurryUp();
        
    }

    cout << "last_dice: " << last_dice << endl;

    if(model->getCurrentPlayer().canUseGUI()){
        this->notPlayableLock(false);
    }
    else{
        this->notPlayableLock(true);
    }
    
    bool def_lock = animation_lock || not_playable_lock;

    for(int i = 0; i < colors.size(); i++){
        color c = colors[i];
        vector<Box> player_pieces = model->getBoard().getPieces(c);
        if(this->model->getCurrentColor() == c){
            for(int j = 0; j < player_pieces.size(); j++){
                this->pieces[c][j].setEnabled(model->isLegalMove(c, player_pieces[j], last_dice), *this);
                this->pieces[c][j].setLocked(!model->isLegalMove(c, player_pieces[j], last_dice) || def_lock, *this);
            }
        }
        else{
            for (int j = 0; j < player_pieces.size(); j++){
                this->pieces[c][j].setEnabled(true, *this);
                this->pieces[c][j].setLocked(true, *this);
            }
        }

        Dice dice = model->getDice();
        for(int j = 0; j < this->dices[c].size(); j++){
            DiceSprite* current = &this->dices[c][j];
            if(this->last_dice == 10 || this->last_dice == 20){
                current->setLocked(true, *this);
                current->setSelected(false, *this);
                current->setEnabled(dice.isAvailable(c, current->getNumber()), *this);
            }
            else{
                
                if(animation_lock){
                    current->setLocked(true, *this);
                    color last_col = get<0>(model->getLastAction());
                    int last_move_dice = get<2>(model->getLastAction());
                    current->setEnabled((c == last_col && current->getNumber() == last_move_dice) || dice.isAvailable(c, current->getNumber()), *this);
                    current->setSelected(c == last_col && current->getNumber() == last_move_dice, *this);
                }
                
                else{
                    current->setEnabled(dice.isAvailable(c, current->getNumber()), *this);
                    current->setLocked(this->model->getCurrentColor() != c || def_lock, *this);
                    current->setSelected(this->model->getCurrentColor() == c and last_dice == current->getNumber(), *this);
                }
            }
        }
        
        // Activar dados especiales para las comidas y las metas.
        if(model->isEatingMove() && c == model->getCurrentColor()){
            special_10_20_dice[c][0].setEnabled(true, *this);
            special_10_20_dice[c][0].setLocked(false || def_lock, *this);
            special_10_20_dice[c][0].setSelected(true, *this);
            special_10_20_dice[c][0].setNumber(20);
        }
        else if(model->isGoalMove() && c == model->getCurrentColor()){
            special_10_20_dice[c][0].setEnabled(true, *this);
            special_10_20_dice[c][0].setLocked(false || def_lock, *this);
            special_10_20_dice[c][0].setSelected(true, *this);
            special_10_20_dice[c][0].setNumber(10);
        }
        else{
            special_10_20_dice[c][0].setEnabled(false, *this);
            special_10_20_dice[c][0].setLocked(true, *this);
            special_10_20_dice[c][0].setSelected(false, *this);
            special_10_20_dice[c][0].setNumber(-1);
        }
    }

    // Actualizar color y disponibilidad del botón de pasar turno.
    this->skip_turn_button.setModelColor(model->getCurrentColor());
    this->skip_turn_button.setEnabled(model->canSkipTurn(model->getCurrentColor(), last_dice), *this);
    this->skip_turn_button.setLocked(!model->canSkipTurn(model->getCurrentColor(), last_dice) || def_lock, *this);
}

void ParchisGUI::updateSpritesLock(){
    
    if (animation_lock || not_playable_lock)
    {
        //Por algún motivo la aplicación a veces se cuelga cuando se cambian estos cursores.
        //this->setDefaultCursorThinking(); // Este cursor hace que el programa se rompa, pero solo cuando se pone aquí ???
        //this->setDefaultCursorForbidden();
        //this->setDefaultCursor();

        vector<color> colors = Parchis::game_colors;

        for (int i = 0; i < colors.size(); i++)
        {
            color c = colors[i];
            vector<Box> player_pieces = model->getBoard().getPieces(c);
            for (int j = 0; j < player_pieces.size(); j++)
            {
                this->pieces[c][j].setLocked(true, *this);
            }

            for (int j = 0; j < this->dices[c].size(); j++)
            {
                DiceSprite *current = &this->dices[c][j];
                current->setLocked(true, *this);
            }

            special_10_20_dice[c][0].setLocked(true, *this);
        }

        this->skip_turn_button.setLocked(true, *this);

        this->move_heuristic_button.setEnabled(false, *this);
        this->move_heuristic_button.setLocked(true, *this);
    }
    else
    {
        //this->setDefaultCursorNormal();
        //this->setDefaultCursor();

        this->move_heuristic_button.setEnabled(true, *this);
        this->move_heuristic_button.setLocked(false, *this);
        //if(not_playable_lock) updateSprites();
    }
}

/*
void ParchisGUI::selectAction(color col, int dice, bool b){
    this->dices.at(col).at(dice).setSelected(b, *this);
}*/


void ParchisGUI::animationLock(bool lock){
    mutex.lock();
    if(lock != animation_lock){
        this->animation_lock = lock;
        updateSpritesLock();    
    }
    mutex.unlock();
}

void ParchisGUI::notPlayableLock(bool lock){
    mutex.lock();
    if(lock != not_playable_lock){
        this->not_playable_lock = lock;
        updateSpritesLock();
    }
    mutex.unlock();
}

bool ParchisGUI::animationsRunning(){
    return !this->animations_ch1.empty() || !this->animations_ch2.empty() || !this->animations_ch3.empty() || !this->animations_ch4.empty();
}

void ParchisGUI::run(){
    while(this->isOpen()){
        mainLoop();
    }
}

//col_pieces_sprites[j].setPosition((Vector2f)box2position.at(model.getBoard().getPiece(col, j))[j]);


Vector2f ParchisGUI::box3position(color c, int id, int pos){
    Box piece = model->getBoard().getPiece(c, id);
    if (piece.type == home || piece.type == goal) {
        return (Vector2f)box2position.at(piece)[id];
    }else{
        return (Vector2f)box2position.at(piece)[pos];
    }
}

Vector2f ParchisGUI::box3position(Box piece, int id, int pos){
    if (piece.type == home || piece.type == goal){
        return (Vector2f)box2position.at(piece)[id];
    }else{
        return (Vector2f)box2position.at(piece)[pos];
    }
}


//Cursores
void ParchisGUI::setDefaultCursor()
{
    //if(cursor.loadFromSystem(Cursor::Arrow))
    //    this->setMouseCursor(cursor);
    mutex.lock();
    if(animation_lock || not_playable_lock)
        this->setThinkingCursor();
    else
        this->setNormalCursor();
    //this->setMouseCursor(default_cursor);
    mutex.unlock();
}

void ParchisGUI::setNormalCursor()
{
    mutex.lock();
    if (cursor.loadFromSystem(Cursor::Arrow))
        this->setMouseCursor(cursor);
    mutex.unlock();
}

void ParchisGUI::setForbiddenCursor()
{
    mutex.lock();
    if (cursor.loadFromSystem(Cursor::NotAllowed))
        this->setMouseCursor(cursor);
    mutex.unlock();
}

void ParchisGUI::setHandCursor()
{
    mutex.lock();
    if (cursor.loadFromSystem(Cursor::Hand))
        this->setMouseCursor(cursor);
    mutex.unlock();
}

void ParchisGUI::setThinkingCursor()
{
    //mutex.lock();
    //if (cursor.loadFromSystem(Cursor::Wait))
    //    this->setMouseCursor(cursor);
    //mutex.unlock();
}

void ParchisGUI::setDefaultCursorNormal(){
    mutex.lock();
    default_cursor.loadFromSystem(Cursor::Arrow);
    mutex.unlock();
}

void ParchisGUI::setDefaultCursorForbidden(){
    mutex.lock();
    default_cursor.loadFromSystem(Cursor::NotAllowed);
    mutex.unlock();
}

void ParchisGUI::setDefaultCursorHand(){
    mutex.lock();
    default_cursor.loadFromSystem(Cursor::Hand);
    mutex.unlock();
}

void ParchisGUI::setDefaultCursorThinking(){
    //mutex.lock();
    //default_cursor.loadFromSystem(Cursor::Wait);
    //mutex.unlock();
}



void ParchisGUI::queueMove(color col, int id, Box origin, Box dest, void (ParchisGUI::*callback)(void)){
    this->animationLock(true);
    animation_ch1_callbacks.push(callback);
    if(dest.type == home || dest.type == goal){
        // Si el destino es casa o meta cada ficha va a su puesto preasignado por id.
        Vector2f animate_pos = (Vector2f)box2position.at(dest)[id];

        Sprite *animate_sprite = &pieces[col][id];
        SpriteAnimator animator = SpriteAnimator(*animate_sprite, animate_pos, animation_time);
        animations_ch1.push(animator);
    }
    else{
        // Buscamos colisiones.
        vector<pair<color, int>> occupation = this->model->boxState(dest);
        if(occupation.size() == 1){
            // Si no había fichas en destino se mueve la ficha al sitio central.
            Vector2f animate_pos = (Vector2f)box2position.at(dest)[0];

            Sprite *animate_sprite = &pieces[col][id];
            SpriteAnimator animator = SpriteAnimator(*animate_sprite, animate_pos, animation_time);
            animations_ch1.push(animator);
        }
        else{
            // Si hay dos fichas en destino mandamos cada una a un lateral.
            int main_move = (occupation[0].first == col && occupation[0].second == id)?0:1;
            int collateral_move = (main_move == 0)?1:0;

            // Ficha principal (la que realmente se mueve) por el canal 1 por si hay que encadenar animaciones.
            Vector2f animate_pos = (Vector2f)box2position.at(dest)[1];
            Sprite *animate_sprite = &pieces[occupation[main_move].first][occupation[main_move].second];
            SpriteAnimator animator = SpriteAnimator(*animate_sprite, animate_pos, animation_time);
            animations_ch1.push(animator);

            // Ficha desplazada por el canal 2.
            Vector2f animate_pos2 = (Vector2f)box2position.at(dest)[2];
            Sprite *animate_sprite2 = &pieces[occupation[collateral_move].first][occupation[collateral_move].second];
            SpriteAnimator animator2 = SpriteAnimator(*animate_sprite2, animate_pos2, animation_time);
            animations_ch2.push(animator2);
        }
    }

    if(origin.type != goal && origin.type != home){
        vector<pair<color, int>> origin_occupation = this->model->boxState(origin);
        if(origin_occupation.size() == 1){
            // Si queda una ficha en el origen del movimiento tras haber hecho el movimiento, la devolvemos al centro (canal 3).
            // (Siempre que el origen no sea ni casa ni meta).
            Vector2f animate_pos = (Vector2f)box2position.at(origin)[0];
            Sprite *animate_sprite = &pieces[origin_occupation.at(0).first][origin_occupation.at(0).second];
            SpriteAnimator animator = SpriteAnimator(*animate_sprite, animate_pos, animation_time);
            animations_ch3.push(animator);
        }
    }
}

void ParchisGUI::queueTurnsArrow(color c){
    this->animationLock(true);
    // Actualizar posición y color de la flecha de turnos.
    int new_turn_pos = color2turns_arrow_pos.at(c);
    if (new_turn_pos != turns_arrow.getPosition().y)
    {
        SpriteAnimator s(turns_arrow, Vector2f(turns_arrow.getPosition().x, new_turn_pos), animation_time);
        animations_ch4.push(s);
    }
    Color turns_arrow_color = turns_arrow.getColor();
    if (turns_arrow_color != DiceSprite::color2Color.at(c))
    {
        turns_arrow.setColor(DiceSprite::color2Color.at(c));
    }
}

void ParchisGUI::setBackgroundMusic(bool on){
    music_on = on;
    if(on){
        current_background_theme->play();
    }
    else{
        current_background_theme->stop();
    }
}

void ParchisGUI::initializeBackgroundMusic(){
    // Main background theme.
    if (background_theme.openFromFile(background_theme_file + ".wav"))
    {
        background_theme.setLoop(true); // Para reproducir en bucle.

        ifstream loop_file((background_theme_file + ".loop").c_str());
        if (loop_file.good())
        {
            float loop_start, loop_end;
            loop_file >> loop_start;
            loop_file >> loop_end;
            background_theme.setLoopPoints(Music::TimeSpan(seconds(loop_start), seconds(loop_end - loop_start))); // Se puede elegir los puntos exactos en los que cicle la música de fondo.
            cout << "Added loop points for background theme: " << loop_start << " " << loop_end << endl;
        }
        else
            cout << "No loop points found for background theme." << endl;

        background_theme.setVolume(100.f);
    }
    // Hurry up background theme.
    if(background_theme_hurryup.openFromFile(background_theme_hurryup_file + ".wav")){
        background_theme_hurryup.setLoop(true);
        background_theme_hurryup.setVolume(100.f);

        ifstream loop_file((background_theme_hurryup_file + ".loop").c_str());
        if (loop_file.good())
        {
            float loop_start, loop_end;
            loop_file >> loop_start;
            loop_file >> loop_end;
            background_theme_hurryup.setLoopPoints(Music::TimeSpan(seconds(loop_start), seconds(loop_end - loop_start)));
            cout << "Added loop points for hurry up background theme: " << loop_start << " " << loop_end << endl;
        }
        else
            cout << "No loop points found for hurry up background theme." << endl;
    }

    current_background_theme = &background_theme;
}

void ParchisGUI::switchBackgroundMusic(){
    current_background_theme->stop();
    if(current_background_theme == &background_theme){
        current_background_theme = &background_theme_hurryup;
    }
    else{
        current_background_theme = &background_theme;
    }
    if(music_on){
        current_background_theme->play();
    }
    
}

void ParchisGUI::initializeSoundEffects(){
    if(sound_buffer_move.loadFromFile(sound_move_file + ".wav")){
        sound_move.setBuffer(sound_buffer_move);
        sound_move.setVolume(100.f);
        cout << "Loaded sound effect: " << sound_move_file << endl;
    }
    if(sound_buffer_boing.loadFromFile(sound_boing_file + ".wav")){
        sound_boing.setBuffer(sound_buffer_boing);
        sound_boing.setVolume(100.f);
        cout << "Loaded sound effect: " << sound_boing_file << endl;
    }
    if(sound_buffer_forbidden.loadFromFile(sound_forbidden_file + ".wav")){
        sound_forbidden.setBuffer(sound_buffer_forbidden);
        sound_forbidden.setVolume(100.f);
        cout << "Loaded sound effect: " << sound_forbidden_file << endl;
    }
    if(sound_buffer_eaten.loadFromFile(sound_eaten_file + ".wav")){
        sound_eaten.setBuffer(sound_buffer_eaten);
        sound_eaten.setVolume(100.f);
        cout << "Loaded sound effect: " << sound_eaten_file << endl;
    }
    if(sound_buffer_applause.loadFromFile(sound_applause_file + ".wav")){
        sound_applause.setBuffer(sound_buffer_applause);
        sound_applause.setVolume(100.f);
        cout << "Loaded sound effect: " << sound_applause_file << endl;
    }
}

void ParchisGUI::setSoundEffects(bool on){
    this->sound_on = on;
}

void ParchisGUI::playMoveSound(){
    if(sound_on){
        //Sound sound_move;
        //sound_move.setBuffer(sound_buffer_move);
        sound_move.play();
    }
}

void ParchisGUI::playBoingSound(){
    if(sound_on){
        //Sound sound_boing;
        //sound_boing.setBuffer(sound_buffer_boing);
        sound_boing.play();
    }
}

void ParchisGUI::playForbiddenSound(){
    if(sound_on){
        //Sound sound_forbidden;
        //sound_forbidden.setBuffer(sound_buffer_forbidden);
        sound_forbidden.play();
    }
}

void ParchisGUI::playEatenSound(){
    if(sound_on){
        //Sound sound_eaten;
        //sound_eaten.setBuffer(sound_buffer_eaten);
        sound_eaten.play();
    }
}

void ParchisGUI::playApplauseSound(){
    if(sound_on){
        //Sound sound_applause;
        //sound_applause.setBuffer(sound_buffer_applause);
        sound_applause.play();
    }
}

void ParchisGUI::checkHurryUp(){
    if(current_background_theme == &background_theme){
        bool hurry_up = false;
        vector<color> colors = Parchis::game_colors;

        for(int i = 0; i < colors.size() && !hurry_up; i++){
            if(model->piecesAtGoal(colors[i]) == 3){
                hurry_up = true;
            }
        }
        if(hurry_up){
            switchBackgroundMusic();
        }
    }
}
