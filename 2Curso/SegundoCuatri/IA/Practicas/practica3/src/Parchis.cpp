#include "Parchis.h"

//Definición de las casillas seguras
const vector<int> Parchis::safe_boxes = {4, 13, 17, 21, 30, 34, 38, 47, 51, 55, 64, 68};

//Definición de los colores del juego
const vector<color> Parchis::game_colors = vector<color>{yellow, blue, red, green};

//Definición de las casillas finales para cada color
const map<color, int> Parchis::final_boxes = {
    {yellow, final_yellow_box},
    {blue, final_blue_box},
    {red, final_red_box},
    {green, final_green_box}
};

//Definición de las casillas de inicio para cada jugador
const map<color, int> Parchis::init_boxes = {
    {yellow, init_yellow_box},
    {blue, init_blue_box},
    {red, init_red_box},
    {green, init_green_box}
};

/****************** MÉTODOS PRIVADOS ******************/

void Parchis::nextTurn(){
    //cout << "--------- CAMBIO DE TURNO ---------" << endl;
    if (last_dice != 6 && !eating_move && !goal_move && !remember_6){
        this->current_player = (current_player+1)%2;
        switch(this->current_color){
            case yellow:
                this->current_color = blue;
                break;
            case blue:
                this->current_color = red;
                break;
            case red:
                this->current_color = green;
                break;
            case green:
                this->current_color = yellow;
                break;
        }
    }
}


/****************** CONSTRUCTORES ******************/

void Parchis::initGame(){
    this->last_dice = -1;

    this->current_player = 0;
    this->current_color = yellow;

    this->illegal_move_player = -1;
    this->disconnected_player = -1;
    this->goal_move = false;
    this->eating_move = false;
    this->goal_bounce = false;
    this->remember_6 = false;

    this->turn = 1;

    bounces = {
        {yellow, 0},
        {blue, 0},
        {red, 0},
        {green, 0}
    };
    this->overbounce_player = -1;
}

Parchis::Parchis()
{
    this->board = Board();
    this->dice = Dice();
    initGame();

    players.push_back(make_shared<AIPlayer>("J1"));
    players.push_back(make_shared<AIPlayer>("J2"));
}

Parchis::Parchis(const BoardConfig & b){
    this->board = Board(b);
    this->dice = Dice();
    initGame();

    players.push_back(make_shared<AIPlayer>("J1"));
    players.push_back(make_shared<AIPlayer>("J2"));
}

Parchis::Parchis(const Board & b, const Dice & d){
    this->board = board;
    this->dice = dice;
    initGame();

    players.push_back(make_shared<AIPlayer>("J1"));
    players.push_back(make_shared<AIPlayer>("J2"));
}

Parchis::Parchis(const BoardConfig &b, const Dice &d)
{
    this->board = Board(b);
    this->dice = dice;
    initGame();

    players.push_back(make_shared<AIPlayer>("J1"));
    players.push_back(make_shared<AIPlayer>("J2"));
}

Parchis::Parchis(const Board & b, const Dice & d, Player & p1, Player & p2){
    this->board = board;
    this->dice = dice;
    initGame();

    players.push_back(shared_ptr<Player>(std::move(&p1)));
    players.push_back(shared_ptr<Player>(std::move(&p2)));
}

Parchis::Parchis(const BoardConfig &b, const Dice &d, shared_ptr<Player> p1,  shared_ptr<Player> p2)
{
    this->board = Board(b);
    this->dice = dice;
    initGame();

    players.push_back(shared_ptr<Player>(p1));
    players.push_back(shared_ptr<Player>(p2));
}

Parchis::Parchis(const BoardConfig &b, shared_ptr<Player> p1,  shared_ptr<Player> p2){
    this->board = Board(b);
    this->dice = Dice();
    initGame();

    players.push_back(shared_ptr<Player>(p1));
    players.push_back(shared_ptr<Player>(p2));
}

/****************** GETTERS ******************/

const Dice & Parchis::getDice() const{
    return this->dice;
}

const Board & Parchis::getBoard() const{
    return this->board;
}

int Parchis::getLastDice(){
    return this->last_dice;
}

const vector<tuple<color, int, Box, Box>> & Parchis::getLastMoves() const{
    return this->last_moves;
}

vector<color> Parchis::getPlayerColors(int player) const{
    if (player == 0){
        return {yellow, red};
    }
    else{
        return {blue, green};
    }
}

/**************************************************/


bool Parchis::operator==(const Parchis & parchis) const{
    return this->board == parchis.board && this->turn == parchis.turn;
}

const vector<int> Parchis::getAvailablePieces(color player, int dice_number) const{
    vector<Box> player_pieces = board.getPieces(player);
    vector<int> available_pieces;

    //Para cada ficha del jugador
    for(int i = 0; i < player_pieces.size(); i++){
        //Compruebo si el movimiento es legal
        if(isLegalMove(player, player_pieces[i], dice_number)){
            available_pieces.push_back(i);
        }
    }

    return available_pieces;

}

void Parchis::movePiece(color player, int piece, int dice_number){
    if(!gameOver()){
        // Si elijo pasar turno compruebo que efectivamente puedo hacerlo. 
        // Si sí, pongo el turno en el siguiente jugador. Si no, el jugador ha hecho un movimiento ilegal.
        if(piece == SKIP_TURN){
            if(canSkipTurn(player, dice_number)){
                eating_move = false;
                goal_move = false;

                remember_6 = (dice_number==6 or (remember_6 and (dice_number == 10 or dice_number == 20)));
                
                this->last_dice = dice_number;
                this->last_moves.clear();
                this->dice.removeNumber(player, dice_number);
                this->nextTurn();

                turn++;
                last_action = tuple<color, int, int>(player, piece, dice_number);
            }else{
                turn++;
                illegal_move_player = current_player;
                cout << "ILLEGALLY TRIED TO SKIP TURN" << endl;
            }
            return;
        }
        // Switch por colores
        Box piece_box = board.getPiece(player, piece);
        if(isLegalMove(player, piece_box, dice_number)){
            goal_bounce = false;
            Box final_box = computeMove(player, piece_box, dice_number, &goal_bounce);
            
            /* Gestión de las "comidas"*/
            eating_move = false;
            goal_move = false;

            remember_6 = (dice_number==6 or (remember_6 and (dice_number == 10 or dice_number == 20)));


            //Comprobar si hay una ficha de otro color en la casilla destino
            vector<pair <color, int>> box_states = boxState(final_box);

            if (!box_states.empty() && box_states[0].first != player){
                //Comprobar que la casilla no es segura
                vector<int>::const_iterator ci; 
                if (final_box.type == normal && count(safe_boxes.begin(), safe_boxes.end(), final_box.num) == 0){
                    //Ficha comida
                    eating_move = true;
                    eaten_piece = box_states.at(0);
                    
                }   
            }


            board.movePiece(player, piece, final_box);

            this->last_dice = dice_number;
            this->last_moves.clear();

            if(!goal_bounce)
                this->last_moves.push_back(tuple<color, int, Box, Box>(player, piece, piece_box, final_box));
            else{
                this->last_moves.push_back(tuple<color, int, Box, Box>(player, piece, piece_box, Box(0, goal, player)));
                this->last_moves.push_back(tuple<color, int, Box, Box>(player, piece, Box(0, goal, player), final_box));
                bounces[player]++;
                if(bounces[player] > 30){
                    overbounce_player = current_player;
                }
            }

            // Controlar si se come alguna ficha. En ese caso se actualiza también la ficha comida.
            // La ficha comida se añadiría también al vector last_moves.
            if(eating_move){
                Box origen_comida = board.getPiece(box_states[0].first, box_states[0].second);
                board.movePiece(box_states[0].first, box_states[0].second, Box(0, home, box_states[0].first));
                this->last_moves.push_back(tuple<color, int, Box, Box>(box_states[0].first, box_states[0].second, origen_comida, Box(0, home, box_states[0].first)));
            }

            // Controlar si la ficha ha llegado a la meta. En ese caso el jugador se cuenta 10 con otra ficha (salvo que sea la última)
            if(final_box.type == goal && !gameOver()){
                goal_move = true;
            }


            this->dice.removeNumber(player, dice_number);

            if(eating_move){
                // Añadir al dado de player el valor 20
                dice.forceNumber(player, 20);
            }
            if(goal_move){
                // Añadir al dado de player el valor 10
                dice.forceNumber(player, 10);
            }

            nextTurn();
            turn++;
            last_action = tuple<color, int, int>(player, piece, dice_number);
        }
        else{
            illegal_move_player = current_player;
        }

        
    }
}

bool Parchis::isLegalMove(color player, const Box & box, int dice_number) const{
    if(gameOver())
        return false;
    // Controlar si intento mover una ficha que no es del color del jugador actual.
    if(player != current_color)
        return false;
    // Controlar si intento mover un número que no está disponible en mis dados.
    if(!dice.isAvailable(player, dice_number))
        return false;
    // Controlar si intento contar un número distinto de 20 cuando me he comido una ficha.
    if(isEatingMove() && dice_number != 20)
        return false;
    // Controlar si intento contar un número distinto de 10 cuando he llevado una ficha a la meta.
    if(isGoalMove() && dice_number != 10)
        return false;
    // Control de movimientos
    Box final_box = computeMove(player, box, dice_number);
    // Controlar si barreras, si está en la casa el movimiento solo sería legal si dice_number == 5, ...
    if (box.type == home && dice_number != 5){
        return false;
    //Controlar que ya estés en la meta
    }else if(box.type == goal){
        return false;
    // Comprobar que no haya ya dos fichas en la casilla (a menos que la casilla de destino sea home, meta o la misma que la de partida).
    }
    else if (final_box.type != goal && final_box.type != home && !(final_box == box) && boxState(final_box).size() == 2)
    {
        return false;
    //Controlar los muros
    }
    else{
        // Comprobar que en el camino del movimiento no hay barreras
        vector<color> walls = anyWall(box, final_box);
        for (int i = 0; i < walls.size(); i++){
            if (walls.at(i) != player){
                return false;
            }
        }
        // Comprobar que si he sacado un 6 y tengo barreras de mi color he elegido una de las fichas en la barrera.
        if(dice_number == 6){
            bool hay_walls = false;
            for(int i = 0; i < board.getPieces(player).size() && !hay_walls; i++){
                hay_walls = (isWall(board.getPiece(player, i)) == player);
            }

            if(hay_walls && isWall(box) != player){
                return false;
            }
        }
    } // TODO: falta (al menos) un caso: que salga un 6, haya alguna barrera de ese color y se elija una ficha fuera de la barrera.
    return true;
}

bool Parchis::canSkipTurn(color player, int dice_number) const{
    return dice.isAvailable(player, dice_number) and getAvailablePieces(player, dice_number).size() == 0;
}

const vector<pair <color, int>> Parchis::boxState(const Box & box) const{
    vector<pair <color, int>> occupation;

    for (int c = color::blue; c < color::none; c++){
        color col = (color)c;
        for (int i = 0; i < board.getPieces(col).size(); i++){
            if (board.getPiece(col, i) == box ){
                occupation.push_back(pair<color, int>(col, i));
            }
        }
    }

    return occupation;
}

const Box Parchis::computeMove(color player, const Box & piece_box, int dice_number, bool * goal_bounce) const{
    Box final_box;

    if(goal_bounce != NULL) *goal_bounce = false;

    //Si sale un 6, comprobar si se da condición para avanzar 7 o 6
    if(dice_number == 6){
        bool pieces_out = true;
        for (int i = 0; i < board.getPieces(player).size() && pieces_out; i++){
            if (board.getPieces(player).at(i).type == home){
                pieces_out = false;
            }
        }
        if (pieces_out){
            dice_number = 7;
        }
    }
    //Si sale de la casilla de home
    if (piece_box.type == home){
        switch (player){
            case red:
                final_box = Box(init_red_box, normal, none);
                break;
            case blue:
                final_box = Box(init_blue_box, normal, none);
                break;
            case yellow:
                final_box = Box(init_yellow_box, normal, none);
                break;
            case green:
                final_box = Box(init_green_box, normal, none);
                break;
        }
    }        
    //Condiciones para empezar a avanzar por pasillo de meta
    else if(piece_box.num <= final_boxes.at(player) && piece_box.num + dice_number > final_boxes.at(player) && piece_box.type == normal){
        int count = piece_box.num + dice_number - final_boxes.at(player);
        if (count <= 7){
            final_box = Box(count, final_queue, player);
        }else if (count == 8){
            final_box = Box(0, goal, player);
        }else{
            int diff = 16 - (count);
            if(diff > 0){
                final_box = Box(diff, final_queue, player);
            }else{
                final_box = Box(final_boxes.at(player) + diff, normal, none);
            }
            if(goal_bounce != NULL) *goal_bounce = true;
        }

    }else if(piece_box.num + dice_number > 68 && piece_box.num + dice_number - 68 > final_boxes.at(player) && piece_box.type == normal){
        int count = piece_box.num + dice_number - 68 - final_boxes.at(player);
        if (count <= 7){
            final_box = Box(count, final_queue, player);
        }else if (count == 8){
            final_box = Box(0, goal, player);
        }else{
            int diff = 16 - (count);
            if(diff > 0){
                final_box = Box(diff, final_queue, player);
            }else{
                final_box = Box(final_boxes.at(player) + diff, normal, none);
            }
            if(goal_bounce != NULL) *goal_bounce = true;
        }
    }
    //Si ya está en pasillo de meta
    else if(piece_box.type == final_queue){
        if (piece_box.num + dice_number <= 7){
            final_box = Box(piece_box.num + dice_number, final_queue, player);
        }else if (piece_box.num + dice_number == 8){
            final_box = Box(0, goal, player);
        }else{
            int diff = 16 - (piece_box.num + dice_number);
            if(diff > 0){
                final_box = Box(diff, final_queue, player);
            }else{
                final_box = Box(final_boxes.at(player) + diff, normal, none);
            }
            if(goal_bounce != NULL) *goal_bounce = true;
        }
    }
    //Por defecto
    else{
        final_box = Box(1 + (piece_box.num+ dice_number - 1) % 68, box_type::normal, color::none);
    }

    return final_box;
}

void Parchis::gameLoop(){
    // Incializar el juego para los jugadores por primera vez
    for (int i = 0; i < players.size(); i++)
    {
        players.at(i)->perceive(*this);
    }

    cout << "++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "¡COMIENZA LA PARTIDA!" << endl;
    cout << "Jugador 1: " << players.at(0)->getName() << endl;
    cout << "Jugador 2: " << players.at(1)->getName() << endl;
    cout << "++++++++++++++++++++++++++++++++++++++" << endl;

    // Bucle principal del juego.
    while (!gameOver()){
        // :)
        gameStep();
    }

    // Gestionar final de la partida.
    if (gameOver())
    {
        cout << "++++++++++++++++++++++++" << endl;
        cout << "La partida ha terminado" << endl;
        int winner = getWinner();
        color winner_color = getColorWinner();

        cout << "Ha ganado el jugador " << winner << " (" << str(winner_color) << ")" << endl;
        cout << "Nombre del jugador: " << players.at(winner)->getName() << endl;
        if (illegalMove())
        {
            cout << "El jugador " << (winner == 1 ? 0 : 1) << " ha hecho un movimiento ilegal" << endl;
        }
        if(overBounce())
        {
            cout << "El jugador " << (winner == 1 ? 0 : 1) << " ha excedido el límite de rebotes." << endl;
        }
        cout << "++++++++++++++++++++++++" << endl;
    }
}

bool Parchis::gameStep(){
    cout << "----------------" << endl;
    cout << "Turno: " << turn << endl;
    cout << "Jugador actual: " << this->current_player << " (" << this->players.at(current_player)->getName() << ")" << endl;
    cout << "Color actual: " << str(this->current_color) << endl;
    cout << "----------------" << endl;

    // El jugador actual hace su movimiento.
    bool move = players.at(current_player)->move();

    // Se notifica el movimiento a todos los jugadores.
    for (int i = 0; i < players.size(); i++)
    {
        players.at(i)->perceive(*this);
    }

    //Se notifica el movimiento a todos los viewers.
    for (int i = 0; i < viewers.size(); i++)
    {
        viewers.at(i)->perceive(*this);
    }

    // Se espera a que todos los jugadores estén listos para el siguiente turno.
    waitForPlayers();

    return true;
}

void Parchis::waitForPlayers() const{
    // Sleep 10 milliseconds mientras haya un jugador que aún no esté listo para
    // el siguiente turno.
    // Comprobamos tanto jugadores como viewers.
    vector<bool> ready_players(players.size(), false);
    vector<bool> ready_viewers(viewers.size(), false);
    bool ready = false;
    while (!ready){
        ready = true;
        for (int i = 0; i < players.size(); i++){
            if(!ready_players[i]){
                ready_players[i] = players.at(i)->readyForNextTurn();
                ready = ready && ready_players[i];
            }
        }
        for (int i = 0; i < viewers.size(); i++){
            if(!ready_viewers[i]){
                ready_viewers[i] = viewers.at(i)->readyForNextTurn();
                ready = ready && ready_viewers[i];
            }
        }
        if(!ready) sleep(milliseconds(10));
    }
}

bool Parchis::gameOver() const{
    return getWinner() != -1;
}

void Parchis::endGame(){
    this->disconnected_player = current_player;
}

int Parchis::getWinner() const{
    if(illegal_move_player != -1){
        return (illegal_move_player == 0)?1:0;
    }
    if(disconnected_player != -1){
        return (disconnected_player == 0)?1:0;
    }
    if(overbounce_player != -1){
        return (overbounce_player == 0)?1:0;
    }
    color col = getColorWinner();
    switch(col){
        case yellow:
        case red:
            return 0;
        case blue:
        case green:
            return 1;

        default: 
            return -1;

        break;
    }
}

color Parchis::getColorWinner() const{
    // Recorro todos los colores. En principio da igual el orden, solo debería encontrarse como mucho un ganador.
    for(int i = 0; i < Parchis::game_colors.size(); i++){
        color col = Parchis::game_colors.at(i);
        Box goal(0, box_type::goal, col);

        if(boxState(goal).size() == board.getPieces(col).size()){
            return col;
        }
    }
    return none;
}

bool Parchis::illegalMove() const{
    return this->illegal_move_player != -1;
}

bool Parchis::overBounce() const{
    return this->overbounce_player != -1;
}

/**************************** MÉTODOS PARA LA HEURÍSTICA *********************/

int Parchis::piecesAtGoal(color col) const{
    Box goal(0, box_type::goal, col);
    return boxState(goal).size();
}

int Parchis::piecesAtHome(color col) const{
    Box home(0, box_type::home, col);
    return boxState(home).size();
}

int Parchis::distanceToGoal(color player, const Box & box) const{
    //Calculo número de casillas hasta llegar a la meta
    switch(box.type){
        case normal:
            //En caso de casilla normal, el número de casillas hasta la entrada
            //al pasillo final, + 8 casillas del pasillo.
            if (box.num > final_boxes.at(player)){
                return 68 - box.num + final_boxes.at(player) + 8;
            }else{
                return final_boxes.at(player) - box.num + 8;
            }
        case goal:
            //En caso de estar en la meta, 0.
            return 0;
        case final_queue:
            //En caso de estar en el pasillo final, el número de casillas que te
            //queden hasta el 8.
            return 8 - box.num;
        case home:
            //El máximo, cuando estás en home. 65 de moverte hasta la entrada al pasillo
            //final, + 8 casillas del pasillo, + 1 por tener que salir de la casa.
            return 1 + 65 + 8;                    
        default:
            return -1;
    }
}

int Parchis::distanceToGoal(color player, int id_piece) const{
    return distanceToGoal(player, this->board.getPiece(player, id_piece));
}

int Parchis::distanceBoxtoBox(color player, const Box & box1, const Box & box2) const{
    Box ref_box1 = box1;
    Box ref_box2 = box2;

    // Reducimos el problema a distancia entre casillas normales.
    switch(box2.type){
        case normal:
            ref_box2 = box2;
            break;
        case goal:
        case final_queue:
            ref_box2 = Box(final_boxes.at(box2.col), normal, none);
            break;
        case home:
            ref_box2 = Box(init_boxes.at(box2.col), normal, none);
            break;
    }
    switch(box1.type){
        case normal:
            ref_box1 = box1;
            break;
        case goal:
        case final_queue:
            ref_box1 = Box(final_boxes.at(box1.col), normal, none);
            break;
        case home:
            ref_box1 = Box(init_boxes.at(box1.col), normal, none);
            break;
    }
    
    // Casos inalcanzables (espacios de color único).
    if(box2.type != normal && player != box2.col){
        return -1;
    }

    // Para el resto de casos calculamos la distancia "normal" y luego añadimos los extras.
    int distance = 0;
    
    // Si mi pasillo está por medio es inalcanzable.
    if(ref_box1.num < final_boxes.at(player) && final_boxes.at(player) < ref_box2.num){
        return -1;
    }
    // Si mi pasillo está por delante, y la casilla destino después del 68, inalcanzable.
    if(ref_box1.num > ref_box2.num && ref_box1.num < final_boxes.at(player)){
        return -1;
    }
    // Si mi pasillo está antes de la casilla destino, y parto de algo mayor, inalcanzable.
    if(ref_box1.num > ref_box2.num && final_boxes.at(player) < ref_box2.num){
        return -1;
    }
    // En caso contrario, es alcanzable.
    // Si el destino está por encima, devuelvo la diferencia.
    if(ref_box2.num > ref_box1.num){
        distance = ref_box2.num - ref_box1.num;
    }
    // Si el destino está por debajo, devuelvo la distancia al 68 más lo que me queda hasta el destino.
    else{
        distance = 68 - ref_box1.num + ref_box2.num;
    }

    // Añadimos los "extras".
    switch(box1.type){
        case home:
            distance += 1;
            break;
        case final_queue:
            distance -= box1.num;
            break;
        case goal:
            distance -= 8;
            break;
    }
    switch(box2.type){
        case home:
            distance -= 1;
            break;
        case final_queue:
            distance += box2.num;
            break;
        case goal:
            distance += 8;
            break;
    }

    // Si ha salido negativo es por cosas como que ambas casillas son del pasillo final y la primera está adelantada
    // --> Inalcanzable (salvo rebote).
    if(distance < 0){
        return -1;
    }

    return distance;
}

int Parchis::distanceBoxtoBox(color player1, int id_p1, color player2, int p2) const{
    return distanceBoxtoBox(player1, this->board.getPiece(player1, id_p1), this->board.getPiece(player2, p2));
}

Parchis Parchis::generateNextMove(color & c_piece,  int & id_piece, int & dice) const{
    c_piece = this->getCurrentColor();
    bool change_dice = false;
    vector<int> current_dices;
    vector<int> current_pieces;

    //Si dice tiene valor por defecto, cojo el primero.
    if (dice == -1){
        dice = this->getAvailableDices(c_piece).at(0);
    }

    do{
        //Compruebo si quedan movimientos legales con dice
        current_pieces = this->getAvailablePieces(c_piece, dice);
        if (current_pieces.size() > 0){
            //Si id_piece tiene valor por defecto, cojo el primero.
            if(id_piece == -1){
                id_piece = current_pieces.at(0);
                change_dice = false;
            }
            else{
                //Siguiente pieza a id_piece
                for(int i = 0; i < current_pieces.size(); i++){
                    //Compruebo si hay más piezas disponibles
                    if(current_pieces.at(i) == id_piece){
                        //Si no los hay
                        if (i == current_pieces.size() - 1){
                            //Compruebo si puedo pasar de turno
                            if(this->canSkipTurn(c_piece, dice) && id_piece != SKIP_TURN){
                                id_piece = SKIP_TURN;
                                change_dice = false;
                            }
                            // Si no, cambio de dado
                            else{
                                change_dice = true;
                            }
                        }
                        // Si sí las hay, cojo la siguiente
                        else{
                            id_piece = current_pieces.at(i+1);
                            change_dice = false;
                        }
                        break;
                    }
                }
            }
        // Si no, compruebo si puedo pasar turno con ese dado.
        }else if(this->canSkipTurn(c_piece, dice) && id_piece != SKIP_TURN){
            id_piece = SKIP_TURN;
            change_dice = false;
        }
        // Si no, cambio de dado.
        else{
            //Siguiente dado
            change_dice = true;
        }

        //Si tengo que cambiar de dado
        if(change_dice){
            //Compruebo los disponibles
            current_dices = this->getAvailableDices(c_piece);
            //Los recorro en orden ASCENDENTE
            for(int j = 0; j < current_dices.size(); j++){
                if(current_dices.at(j) == dice){
                    //Si no hay más, me salgo
                    if(j == current_dices.size() -1){
                        return *this;
                    //Si sí hay, cojo el siguiente
                    }else{
                        dice = current_dices.at(j+1);
                        id_piece = -1;
                        break;
                    }
                }
            }
        }
    }while(change_dice);

    Parchis next_move(*this);
    next_move.movePiece(c_piece, id_piece, dice);
    return next_move;

}

Parchis Parchis::generateNextMoveDescending(color & c_piece,  int & id_piece, int & dice) const{
    c_piece = this->getCurrentColor();
    bool change_dice = false;
    vector<int> current_dices;
    vector<int> current_pieces;

    //Si dice tiene valor por defecto, cojo el primero.
    if (dice == -1){
        dice = this->getAvailableDices(c_piece).back();
    }

    do{
        //Compruebo si quedan movimientos legales con dice
        current_pieces = this->getAvailablePieces(c_piece, dice);
        if (current_pieces.size() > 0){
            //Si id_piece tiene valor por defecto, cojo el primero.
            if(id_piece == -1){
                id_piece = current_pieces.at(0);
                change_dice = false;
            }
            else{
                //Siguiente pieza a id_piece
                for(int i = 0; i < current_pieces.size(); i++){
                    //Compruebo si hay más piezas disponibles
                    if(current_pieces.at(i) == id_piece){
                        //Si no las hay
                        if (i == current_pieces.size() - 1){
                            //Compruebo si puedo pasar de turno
                            if(this->canSkipTurn(c_piece, dice) && id_piece != SKIP_TURN){
                                id_piece = SKIP_TURN;
                                change_dice = false;
                            }
                            // Si no, cambio dado
                            else{
                                change_dice = true;
                            }
                        }
                        //Si sí las hay, cojo la siguiente
                        else{
                            id_piece = current_pieces.at(i+1);
                            change_dice = false;
                        }
                        break;
                    }
                }
            }

        // Si no, compruebo si puedo pasar turno con ese dado.
        }else if(this->canSkipTurn(c_piece, dice) && id_piece != SKIP_TURN){
            id_piece = SKIP_TURN;
            change_dice = false;
        }
        // Si no, cambio de dado
        else{
            //Siguiente dado
            change_dice = true;
        }

        //Si tengo que cambiar de dado
        if(change_dice){
            //Compruebo dados disponibles
            current_dices = this->getAvailableDices(c_piece);
            //Los recorro en orden DESCENDENTE
            for(int j = current_dices.size() - 1; j >= 0; j--){
                if(current_dices.at(j) == dice){
                    //Si no hay más, me salgo
                    if(j == 0){
                        return *this;
                    //Si sí hay, cojo el anterior
                    }else{
                        dice = current_dices.at(j-1);
                        id_piece = -1;
                        break;
                    }
                }
            }
        }
    }while(change_dice);

    Parchis next_move(*this);
    next_move.movePiece(c_piece, id_piece, dice);
    return next_move;
}

bool Parchis::isSafeBox(const Box & box) const{
    return (box.type == normal && find(safe_boxes.begin(), safe_boxes.end(), box.num) != safe_boxes.end());
}

bool Parchis::isSafePiece(const color & player, const int & piece) const{
    return isSafeBox(this->board.getPiece(player, piece));
}

pair<color, int>  Parchis::eatenPiece() const{
    if(eating_move){
        return eaten_piece;
    }else{
        return {none, 0};
    }
}


const color Parchis::isWall(const Box & b) const{
    if(b.type == home || b.type == goal) return none;

    const vector<pair <color, int>> occupation = boxState(b);
    if (occupation.size() == 2 && occupation.at(0).first == occupation.at(1).first){
        return  occupation.at(0).first;
    }else{
        return none;
    }
}

const vector<color> Parchis::anyWall(const Box & b1, const Box & b2) const{
    Box final_box;
    if (b2.type == final_queue || b2.type == goal){
        //Si el casilla destino es meta o pasillo final, la cambiamos por la última casilla
        //antes de entrar al pasillo final.
        switch (b2.col){
            case blue:
                final_box = Box(final_blue_box, normal, none);
            break;
            case red:
                final_box = Box(final_red_box, normal, none);
            break;
            case green:
                final_box = Box(final_green_box, normal, none);
            break;
            case yellow:
                final_box = Box(final_yellow_box, normal, none);
            break;
        }
    }else{
        final_box = b2;
    }
    vector<color> walls;
    bool reached_final_box = false;
    if (b1.type == normal && final_box.num != b1.num){
        for (int i = b1.num+1; !reached_final_box; i = i%68 + 1){ //Vamos recorriendo casillas intermedias
            reached_final_box = (final_box.num == i);
            //Si hay un muro, lo añadimos al vector de muros.
            color c = isWall(Box(i, normal, none));
            if(c != none){
                walls.push_back(c);
            }
        }
    }
    return walls;
}
