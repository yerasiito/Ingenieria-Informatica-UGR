#ifndef __PARCHIS_H__
#define __PARCHIS_H__

# include <tuple>
# include "Dice.h"
# include "Board.h"
# include "GUIPlayer.h"
# include "Player.h"
# include "AIPlayer.h"
#include <iostream>
#include <algorithm>
#include <memory>

// Macro que define el parámetro para indicar que no se mueve ficha.
#define SKIP_TURN -9999

using namespace std;

class Player;

class Parchis{
    private:
        //Tablero
        Board board;
        //Dados
        Dice dice;

        //Variables para almacenar los últimos movimientos
        //Últimos movimientos identificados por el color.
        vector<tuple <color, int, Box, Box>> last_moves;
        //Última acción identificada por el color.
        tuple <color, int, int> last_action;
        //Último dado utilizado.
        int last_dice;

        //Turno actual
        int turn;
        
        //Jugadores y colorores actuales
        //0: yellow & red, 1: blue and green.
        int current_player;
        color current_color;
        //Vector de jugadores en juego.
        vector <shared_ptr<Player>> players;
        //Vector de viewers (pueden observar la partida pero no intervenir en ella).
        vector <shared_ptr<Player>> viewers;

        //Variables para controlar acciones de los jugadores
        int illegal_move_player;
        int disconnected_player;

        //Booleanos para recordar movimientos especiales
        bool eating_move;
        pair <color, int> eaten_piece;
        bool goal_move;
        bool goal_bounce;
        bool remember_6;

        //Definición de casillas especiales
        static const int final_red_box = 34;
        static const int final_blue_box = 17;
        static const int final_green_box = 51;
        static const int final_yellow_box = 68;

        static const int init_red_box = 38;
        static const int init_blue_box = 21;
        static const int init_green_box = 55;
        static const int init_yellow_box = 4;

        //Vector de casillas seguras.
        static const vector<int> safe_boxes;

        //Vectores de casillas finales e iniciales identificadas por cada color.
        static const map<color, int> final_boxes;
        static const map<color, int> init_boxes;

        // Contro de rebotes (para evitar partidas infinitas)
        map<color, int> bounces;
        int overbounce_player;

        /**
         * @brief Método que gestiona el cambio de turno modificando las variables
         * current_player y current_color.
         *
         */
        void nextTurn();

        /**
         * @brief Método que inicializa las partes comunes en los constructores del juego.
         * 
         */
        void initGame();

    public:
        /**
         * @brief Vector constante de los colores del juego.
         * 
         */
        static const vector<color> game_colors;
        
        /****************** CONSTRUCTORES ******************/


        /**
         * @brief Constructor por defecto de un nuevo objeto de Parchis.
         * @deprecated Los jugadores se deben pasar desde fuera.
         * 
         */
        Parchis();

        /**
         * @brief Constructor de un nuevo objeto de Parchis.
         * @deprecated Los jugadores se deben pasar desde fuera.
         *
         * @param b
         */
        Parchis(const BoardConfig &b);

        /**
         * @brief Constructor de un nuevo objeto de Parchis.
         * @deprecated Los jugadores se deben pasar desde fuera.
         * 
         * @param b 
         * @param d 
         */
        Parchis(const Board & b, const Dice & d);

        /**
         * @brief Constructor de un nuevo objeto de Parchis.
         * @deprecated Los jugadores se deben pasar desde fuera.
         * 
         * @param b 
         * @param d 
         */
        Parchis(const BoardConfig & b, const Dice & d);

        /**
         * @brief Constructor de un nuevo objeto de Parchis.
         * 
         * @param b 
         * @param d 
         * @param p1 
         * @param p2 
         */
        Parchis(const Board & b, const Dice & d, Player & p1, Player & p2);

        /**
         * @brief Constructor de un nuevo objeto de Parchis.
         * 
         * @param b 
         * @param d 
         * @param p1 
         * @param p2 
         */
        Parchis(const BoardConfig &b, const Dice &d, shared_ptr<Player> p1,  shared_ptr<Player> p2);

        /**
         * @brief Constructor de un nuevo objeto de Parchis.
         *
         * @param b
         * @param p1
         * @param p2
         */
        Parchis(const BoardConfig &b, shared_ptr<Player> p1,  shared_ptr<Player> p2);

        /****************** GETTERS ******************/

        /**
         * @brief Función que devuelve el atribute dice.
         * 
         * @param player 
         * @return const vector<int>& 
         */
        const Dice & getDice () const;


         /**
         * @brief Función que devuelve el attributo board.
         * 
         * @param player 
         * @return const vector<int>& 
         */
        const Board & getBoard () const;

        /**
         * @brief Función que devuelve el atibuto last_action.
         * 
         * @return int 
         */
        inline const tuple <color, int, int> & getLastAction() const{
            return last_action;
        }

        /**
         * @brief Función que devuelve el atributo turn
         * 
         * @return const int 
         */
        inline const int getTurn() const{
            return turn;
        }

        /**
         * @brief Función que devuelve el atributo last_dice.
         * 
         * @return int 
         */
        int getLastDice();

        /**
         * @brief Función que devuelve el valor del atributo eating_move
         * 
         * @return true 
         * @return false 
         */
        inline const bool isEatingMove() const {
            return eating_move;
        }

        /**
         * @brief Función que devuelve el valor del atributo goal_move
         * 
         * @return true 
         * @return false 
         */
        inline const bool isGoalMove() const {
            return goal_move;
        }

        /**
         * @brief Función que devuelve el valor del atributo goal_bounce
         * 
         * @return true 
         * @return false 
         */
        inline const bool goalBounce() const{
            return goal_bounce;
        }

        /**
         * @brief Función que devuelve el id del jugador actual.
         * 
         * @return int 
         */
        inline int getCurrentPlayerId() const{
            return current_player;
        }

        /**
         * @brief Función que devuelve una referencia al jugador actual.
         * 
         * @return Player& 
         */
        inline Player & getCurrentPlayer(){
            return *players[current_player];
        }

        /**
         * @brief Función que devuelve el vector de jugadores.
         * 
         * @return vector<shared_ptr<Player>>& 
         */
        inline vector<shared_ptr<Player>> & getPlayers(){
            return players;
        }

        /**
         * @brief Función que devuelve el atributo current_color.
         * 
         * @return color 
         */
        inline color getCurrentColor() const{
            return this->current_color;
        }

        /**
         * @brief Función que devuelve el atributo last_moves.
         * 
         * @return const vector<tuple <color, int, Box>>& 
         */
        const vector<tuple <color, int, Box, Box>> & getLastMoves() const;


        /****************************************************************/

        /**
         * @brief Sobrecarga del operador == de un parchis pasado como argumento y el actual.
         * Se verifica que se de la igualdad entre el tablero (board) y el turno.
         * 
         * @param parchis 
         * @return true 
         * @return false 
         */
        bool operator==(const Parchis & parchis) const;

        /**
         * @brief Función que añade al jugador identificado por p como un nuevo viewer
         * a la lista de viewers.
         * 
         * @param p 
         */
        inline void addViewer(shared_ptr<Player> p){viewers.push_back(shared_ptr<Player>(p));}
        
        /**
         * @brief Función que devuelve todas las fichas de player que pueden 
         * hacer un movimiento según el valor del dado dice_number.
         * 
         * Por ejemplo, si dice_number = 3, las fichas que se encuentran en home
         * no aparecerán como disponibles.
         * 
         * También se gestionan las barreras y otros casos particulares. 
         * 
         * @param player 
         * @param dice_number 
         * @return const vector<int>& 
         */
        const vector<int> getAvailablePieces (color player, int dice_number) const;

        /**
         * @brief Obtener los números del dado disponibles para el jugador de color player.
         * 
         * @param player 
         * @param dice_number 
         * @return const vector<int>& 
         */
        inline const vector<int> getAvailableDices (color player) const{
            return dice.getDice(player);
        }

        /**
         * @brief Mover la pieza número "piece" del jugador "player" "dice_number" posiciones.
         * 
         * @param player 
         * @param piece 
         * @param dice_number 
         */
        void movePiece(color player, int piece, int dice_number);

        /**
         * @brief Función que comprueba si un movimiento es válido para las fichas de un determinado
         * color en una determinada casilla. Tiene en cuenta barreras y otras particularidades.
         * 
         * 
         * @param player 
         * @param box 
         * @param dice_number 
         * @return true 
         * @return false 
         */
        bool isLegalMove(color player, const Box & box, int dice_number) const;

        /**
         * @brief Comprobar si el jugador puede pasar turno con el dado seleccionado (si no tiene fichas para mover).
         * 
         * @param player 
         * @param dice_number 
         * @return true 
         * @return false 
         */
        bool canSkipTurn(color player, int dice_number) const;
        
        /**
         * @brief Función que devuelve la ocupación de una casilla.
         * 
         * Se proporciona en formato vector de parejas con identificador el color, y valor
         * el número de fichas de ese color en esa casilla.
         * 
         * Por ejemplo, si la  casilla tiene 1 ficha azul y otra amarilla, la función devolverá:
         * {{blue, 1}, {yellow, 1}}
         * 
         * @param box 
         * @return vector<pair <color, int>> 
         */
        const vector<pair <color, int>> boxState(const Box & box) const;

        /**
         * @brief Función auxiliar que calcula la casilla destino tras aplicar el movimiento.
         *          
         * @param player 
         * @param box 
         * @param dice_number 
         * @return const Box 
         */
        const Box computeMove(color player, const Box & box, int dice_number, bool * goal_bounce = NULL) const;


        /**
         * @brief Método que gestiona el bucle principal del juego, mientras este no haya terminado,
         * y de terminarlo en caso de que haya un ganador.
         * 
         * Se apoya en la función gameStep()
         * 
         */
        void gameLoop();


        /**
         * @brief Método que gestiona un turno de juego. Obtiene el movimiento del jugador actual y notifica
         * al resto de jugadores.
         * 
         */
        bool gameStep();

        /**
         * @brief Función para comprobar que todos los jugadores están listos para pasar el turno, y si no esperarlos.
         *
         */
        void waitForPlayers() const;

        
        /**
         * @brief Termina una partida por la fuerza. Da por ganador al jugador que no esté en el turno actual.
         * Para usar solo para gestionar desconexiones forzadas.
         * 
         */
        void endGame();

        /**
         * @brief Indica si la partida ha terminado.
         * 
         * @return true 
         * @return false 
         */
        bool gameOver() const;

        
        /**
         * @brief Si la partida ha terminado, devuelve el índice del jugador ganador (0 o 1).
         * 
         * @return int 
         */
        int getWinner() const;

        /**
         * @brief Si la partida ha terminado, devuelve el color del jugador ganador.
         * 
         * @return color 
         */
        color getColorWinner() const;

        /**
         * @brief Devuelve true si y solo si uno de los jugadores ha hecho un movimiento ilegal.
         * El jugador que ha hecho dicho movimiento pierde automáticamente.
         * 
         * @return true 
         * @return false 
         */
        bool illegalMove() const;

        /**
         * @brief Devuelve true si y solo si uno de los jugadores ha rebotado más de 30 veces con algún color.
         * El jugador que ha rebotado pierde automáticamente.
         * La finalidad de este límite es evitar que se produzcan partidas infinitas.
         * 
         * @return true 
         * @return false 
         */
        bool overBounce() const;

        /**
         * @brief Devuelve el número de veces que han rebotado en la meta las fichas del color indicado por player.
         * 
         * @return int
         */
        inline const int getBounces(color player) const{
            return bounces.at(player);
        }

        /**************************** MÉTODOS PARA LA HEURÍSTICA *********************/

        /**
         * @brief Devuelve el número de fichas de un color que han llegado a la meta.
         * 
         * @return int 
         */
        int piecesAtGoal(color player) const;

        /**
        * @brief Devuelve el número de fichas de un color que estan en casa.
        *
        * @return int
        */
        int piecesAtHome(color player) const;

        /**
         * @brief Función que devuelve la distancia a la meta del color "player" desde
         * la casilla "box". 
         * 
         * La distancia se entiende como el número de casillas que hay que avanzar hasta
         * la meta.
         * 
         * @param player 
         * @param box 
         * @return int 
         */
        int distanceToGoal(color player, const Box & box) const;

        /**
         * @brief Función que devuelve la distancia a la meta de la ficha identificada
         * por id_piece del jugador identificado por player.
         * 
         * La distancia se entiende como el número de casillas que hay que avanzar hasta
         * la meta.
         * 
         * @param player 
         * @param id_piece
         * @return int 
         */
        int distanceToGoal(color player, int id_piece) const;

        /**
         * @brief  Función que devuelve el número de casillas que hay que pasar para llegar desde
         * box1 hasta box2 para un determinado color especificado por el parámetro player.
         *
         * Devuelve -1 si la casilla box2 no es alcanzable desde box1 para una ficha del
         * color player.
         *
         * No se tienen en cuenta rebotes.
         * Para ver la distancia entre dos casillas teniendo en cuenta rebotes o no (para el color player), podría hacer:
         * distanceBoxtobox(player, box1, box2) (si no me devuelve -1 podré llegar a la casilla sin rebotar).
         * distanceToGoal(player, box1) + distanceToGoal(player, box2) (distancia entre las dos casillas con rebote).
         *
         * @param player
         * @param box1
         * @param box2
         * @return int
         */
        int distanceBoxtoBox(color player, const Box & box1, const Box & box2) const;

        /**
         * @brief Función que devuelve el número de casillas que tiene que avanzar la ficha del 
         * color player1 identificada con id_p1 para alcanzar la ficha del color player2 
         * identificada con id_p2. No se tienen en cuenta rebotes.
         * 
         * Devuelve -1 si la segunda pieza es inalcanzable por la primera.
         * 
         * @param player1 
         * @param id_p1 
         * @param player2 
         * @param id_p2 
         * @return int 
         */
        int distanceBoxtoBox(color player1, int id_p1, color player2, int id_p2) const;

        /**
         * @brief Función que genera el siguiente movimiento siguiendo un orden 
         * ascendente de los dados.
         * 
         * Estos métodos funcionan de la siguiente forma. Dado un estado del juego, a partir de los parámetros 
         * de color, id de ficha y dado que se le pasen por referencia, asociados a un determinado movimiento 
         * en el tablero, determinará el siguiente hijo que se expandirá en el árbol de búsqueda. 
         * Los parámetros se actualizarán de forma que se correspondan con el movimiento necesario para generar 
         * el nuevo hijo desarrollado. Inicialmente, para generar el primer hijo de una ramificación, se deben 
         * pasar los parámetros inicializados a -1.
         * 
         * @param c_piece 
         * @param id_piece 
         * @param dice 
         * @return Parchis 
         */
        Parchis generateNextMove(color & c_piece,  int & id_piece, int & dice) const;

        /**
         * @brief Función que genera el siguiente movimiento siguiendo un orden 
         * descendente de los dados.
         * 
         * Estos métodos funcionan de la siguiente forma. Dado un estado del juego, a partir de los parámetros 
         * de color, id de ficha y dado que se le pasen por referencia, asociados a un determinado movimiento 
         * en el tablero, determinará el siguiente hijo que se expandirá en el árbol de búsqueda. 
         * Los parámetros se actualizarán de forma que se correspondan con el movimiento necesario para generar 
         * el nuevo hijo desarrollado. Inicialmente, para generar el primer hijo de una ramificación, se deben 
         * pasar los parámetros inicializados a -1.
         * 
         * @param c_piece 
         * @param id_piece 
         * @param dice 
         * @return Parchis 
         */
        Parchis generateNextMoveDescending(color & c_piece,  int & id_piece, int & dice) const;

        /**
         * @brief Función que devuelve si una determinada casilla es segura o no.
         * 
         * @param box 
         * @return true 
         * @return false 
         */
        bool isSafeBox(const Box & box) const;

        /**
         * @brief Función que devuelve si una determinada ficha de un determinado está
         * en una casilla segura o no.
         * 
         * @param player 
         * @param piece 
         * @return true 
         * @return false 
         */
        bool isSafePiece(const color & player, const int & piece) const;

        /**
         * @brief Función que devuelve qué ficha ha sido comida, en caso de haberse producido una comida.
         *  En caso de no haberse comido una ficha en el último turno, devuelve {none, 0}
         * 
         */
        pair<color, int> eatenPiece() const;

        /**
         * @brief Función que devuelve el color de la barrera (en caso de haberla) en la casilla "b".
         * Es decir, si en la casilla "b" hay dos fichas de un mismo color devuelve este color.
         * 
         * @param b 
         * @return const color 
         */
        const color isWall(const Box & b) const;

        /**
         * @brief Función que devuelve el vector de colores de las barreras (en caso de haberlas) del
         * camino entre b1 y b2.
         * 
         * Esto es, se va recorriendo todas las casillas que habría que recorrer para ir de b1 y b2,
         * y siempre que se encuentran dos fichas de un mismo color en una misma casilla se añade ese
         * color al vector que se devuelve.
         * 
         * Por ejemplo: si en la casilla 2 hay una barrera amarilla y en la 4 una azul, el anywalls(1,6) 
         * devuelve {yellow, blue}
         * 
         * @param b1 
         * @param b2 
         * @return const vector<color> 
         */
        const vector<color> anyWall(const Box & b1, const Box & b2) const;

        /**
         * @brief Devuelve los colores asociados a cada jugador (amarillo y rojo para el 0 y verde y azul para el 1).
         * 
         * @param player 
         * @return vector<color> 
         */
        vector<color> getPlayerColors(int player) const;


};


#endif 