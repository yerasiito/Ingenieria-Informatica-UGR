# include "AIPlayer.h"
# include "Parchis.h"

const double masinf = 9999999999.0, menosinf = -9999999999.0;
const double gana = masinf - 1, pierde = menosinf + 1;
const int num_pieces = 4;
const int PROFUNDIDAD_MINIMAX = 4;  // Umbral maximo de profundidad para el metodo MiniMax
const int PROFUNDIDAD_ALFABETA = 6; // Umbral maximo de profundidad para la poda Alfa_Beta

bool AIPlayer::move(){
    cout << "Realizo un movimiento automatico" << endl;
    
    color c_piece;
    int id_piece;
    int dice;
    think(c_piece, id_piece, dice);
    
    cout << "Movimiento elegido: " << str(c_piece) << " " << id_piece << " " << dice << endl;

    actual->movePiece(c_piece, id_piece, dice);
    return true;
}

void AIPlayer::think(color & c_piece, int & id_piece, int & dice) const{
    // OBJETIVO: Asignar a las variables c_piece, id_piece, dice (pasadas por referencia) los valores, 
    //respectivamente, de:
    // - color de ficha a mover
    // - identificador de la ficha que se va a mover
    // - valor del dado con el que se va a mover la ficha.

    double valor = menosinf; // Almacena el valor devuelto por el minimax y la poda AlfaBeta
    double alpha = menosinf, beta = masinf; // Umbrales de la poda AlfaBeta
    
    // Inicializar variables
    c_piece = none;
    
    switch(id){
        case 0: 
            valor = Poda_AlfaBeta(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, valoracionDefinitiva);
            cout << "Valor Poda Alfa Beta: " << valor << "  Accion: " << str(c_piece) << " " << id_piece << " " << dice << endl;
            break;
        case 1: 
            valor = Poda_AlfaBeta(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, ganaJ1);
            cout << "Valor Poda Alfa Beta: " << valor << "  Accion: " << str(c_piece) << " " << id_piece << " " << dice << endl;
            break;
        case 2: 
            valor = Poda_AlfaBeta(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, ganaJ2);
            cout << "Valor Poda Alfa Beta: " << valor << "  Accion: " << str(c_piece) << " " << id_piece << " " << dice << endl;
            break;
        case 3:
            valor = Poda_AlfaBeta(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, ValoracionTest);
            cout << "Valor Poda Alfa Beta: " << valor << "  Accion: " << str(c_piece) << " " << id_piece << " " << dice << endl;
            break;
        case 4:
            valor = MiniMax(*actual, jugador, 0, PROFUNDIDAD_MINIMAX, c_piece, id_piece, dice, valoracionDefinitiva);
            cout << "Valor MiniMax: " << valor << "  Accion: " << str(c_piece) << " " << id_piece << " " << dice << endl;
            break;
        case 5:
            valor = MiniMax(*actual, jugador, 0, PROFUNDIDAD_MINIMAX, c_piece, id_piece, dice, ganaJ1);
            cout << "Valor MiniMax: " << valor << "  Accion: " << str(c_piece) << " " << id_piece << " " << dice << endl;
            break;
        case 6:
            valor = MiniMax(*actual, jugador, 0, PROFUNDIDAD_MINIMAX, c_piece, id_piece, dice, ganaJ2);
            cout << "Valor MiniMax: " << valor << "  Accion: " << str(c_piece) << " " << id_piece << " " << dice << endl;
            break;
        case 7:
            valor = MiniMax(*actual, jugador, 0, PROFUNDIDAD_MINIMAX, c_piece, id_piece, dice, ValoracionTest);
            cout << "Valor MiniMax: " << valor << "  Accion: " << str(c_piece) << " " << id_piece << " " << dice << endl;
            break;
            
    }

}

double AIPlayer::MiniMax(const Parchis &actual, int jugador, int profundidad, int profundidad_max, color &c_piece, int &id_piece, 
        int &dice, double (*heuristic)(const Parchis &, int)) const
{
    bool MAX = (actual.getCurrentPlayerId() == jugador);
    int last_id_piece = -1, last_dice = -1;
    double valor, mejor = menosinf;     
    
    // Si es nodo terminal, devuelve el valor de la heuristica
    if(profundidad == profundidad_max or actual.gameOver())
        return heuristic(actual, jugador);
    
    if(MAX)
        valor = menosinf;
    else
        valor = masinf;

    // Para cada hijo del tablero
    Parchis hijo = actual.generateNextMove(c_piece, last_id_piece, last_dice);
    // Recorremos el arbol de juego
    while(!(hijo == actual)){
        if(MAX)
            valor = max(valor, MiniMax(hijo, jugador, profundidad+1, profundidad_max, c_piece, id_piece, dice, heuristic));
        else
            valor = min(valor, MiniMax(hijo, jugador, profundidad+1, profundidad_max, c_piece, id_piece, dice, heuristic));
        
        if(profundidad == 0 and valor > mejor){
            mejor = valor;
            id_piece = last_id_piece;
            dice = last_dice;
        }
        hijo = actual.generateNextMove(c_piece, last_id_piece, last_dice);
    }
    return valor;
}


double AIPlayer::Poda_AlfaBeta(const Parchis &actual, int jugador, int profundidad, int profundidad_max, color &c_piece, int &id_piece,
        int &dice, double alpha, double beta, double (*heuristic)(const Parchis &, int)) const
{
    bool MAX = (actual.getCurrentPlayerId() == jugador);
    int last_id_piece = -1, last_dice = -1;
    double valor = menosinf, mejor = menosinf;
    
    // Si es nodo terminal, devuelve el valor de la heuristica
    if(profundidad == profundidad_max or actual.gameOver())
        return heuristic(actual, jugador);
    
    // Para cada hijo del tablero
    Parchis hijo = actual.generateNextMoveDescending(c_piece, last_id_piece, last_dice);
    // Recorremos el arbol de juego
    while(!(hijo == actual)){
        valor = Poda_AlfaBeta(hijo, jugador, profundidad+1, profundidad_max, c_piece, id_piece, dice, alpha, beta, heuristic);
        
        if(MAX){
            alpha = max(alpha, valor);
            if(alpha >= beta)
                return beta;
        }
        else{
            beta = min(beta, valor);  
            if(beta <= alpha)
                return alpha;
        }

        // Guarda el mejor valor
        if(profundidad == 0 and alpha > mejor){
            mejor = alpha;
            id_piece = last_id_piece;
            dice = last_dice;                
        }

        hijo = actual.generateNextMoveDescending(c_piece, last_id_piece, last_dice);
    }
    
    if(MAX)
        return alpha;
    else
        return beta;
}

double AIPlayer::ValoracionTest(const Parchis &estado, int jugador)
{
    // Heurística de prueba proporcionada para validar el funcionamiento del algoritmo de búsqueda.


    int ganador = estado.getWinner();
    int oponente = (jugador + 1) % 2;

    // Si hay un ganador, devuelvo más/menos infinito, según si he ganado yo o el oponente.
    if (ganador == jugador)
    {
        return gana;
    }
    else if (ganador == oponente)
    {
        return pierde;
    }
    else
    {
        // Colores que juega mi jugador y colores del oponente
        vector<color> my_colors = estado.getPlayerColors(jugador);
        vector<color> op_colors = estado.getPlayerColors(oponente);

        // Recorro todas las fichas de mi jugador
        int puntuacion_jugador = 0;
        // Recorro colores de mi jugador.
        for (int i = 0; i < my_colors.size(); i++)
        {
            color c = my_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++)
            {
                // Valoro positivamente que la ficha esté en casilla segura o meta.
                if (estado.isSafePiece(c, j))
                {
                    puntuacion_jugador++;
                }
                else if (estado.getBoard().getPiece(c, j).type == goal)
                {
                    puntuacion_jugador += 5;
                }
            }
        }

        // Recorro todas las fichas del oponente
        int puntuacion_oponente = 0;
        // Recorro colores del oponente.
        for (int i = 0; i < op_colors.size(); i++)
        {
            color c = op_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++)
            {
                if (estado.isSafePiece(c, j))
                {
                    // Valoro negativamente que la ficha esté en casilla segura o meta.
                    puntuacion_oponente++;
                }
                else if (estado.getBoard().getPiece(c, j).type == goal)
                {
                    puntuacion_oponente += 5;
                }
            }
        }

        // Devuelvo la puntuación de mi jugador menos la puntuación del oponente.
        return puntuacion_jugador - puntuacion_oponente;
    }
}

double AIPlayer::ganaJ1(const Parchis &estado, int jugador)
{
    int ganador = estado.getWinner();
    int oponente = (jugador + 1) % 2;

    // Devuelvo +/- infinito según si he ganado yo o el oponente.
    if (ganador == jugador)
    {
        return gana;
    }
    else if (ganador == oponente)
    {
        return pierde;
    }
    else
    {
        // Vectores de los colores con los que juego y los del oponente
        vector<color> my_colors = estado.getPlayerColors(jugador);
        vector<color> op_colors = estado.getPlayerColors(oponente);

        // Recorro todas mis fichas
        int puntuacion_jugador = 0;
        // Recorro mis colores
        for (int i = 0; i < my_colors.size(); i++)
        {
            color c = my_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++)
            {
                if(estado.getBoard().getPiece(c,j).type == final_queue)
                    puntuacion_jugador += 68 + estado.getBoard().getPiece(c,j).num;
                else
                    puntuacion_jugador += estado.getBoard().getPiece(c,j).num;
                
                // Valoro positivamente que la ficha esté en casilla segura
                if (estado.isSafePiece(c, j))
                    puntuacion_jugador++;
                
                //Interesa sacar fichas de casa
                if (estado.getBoard().getPiece(c, j).type == home)
                    puntuacion_jugador -= 100;
                
                //Favorece meter casillas a la meta
                if (estado.getBoard().getPiece(c, j).type == goal)
                    puntuacion_jugador += 100;
            }
        }

        // Recorro todas las fichas del oponente
        int puntuacion_oponente = 0;
        // Recorro colores del oponente.
        for (int i = 0; i < op_colors.size(); i++)
        {
            color c = op_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++)
            {
                if(estado.getBoard().getPiece(c,j).type == final_queue)
                    puntuacion_oponente += 68 + estado.getBoard().getPiece(c,j).num;
                else
                    puntuacion_oponente += estado.getBoard().getPiece(c,j).num;
                
                // Cuantas mas casillas en casa, mejor para nosotros
                if (estado.getBoard().getPiece(c, j).type == home)
                    puntuacion_oponente -= 100;

            }
        }

        // Devuelvo la puntuación de mi jugador menos la puntuación del oponente.
        return puntuacion_jugador - puntuacion_oponente;
    }
}

double AIPlayer::ganaJ2(const Parchis &estado, int jugador)
{
    int ganador = estado.getWinner();
    int oponente = (jugador + 1) % 2;

    // Devuelvo +/- infinito según si he ganado yo o el oponente.
    if (ganador == jugador)
    {
        return gana;
    }
    else if (ganador == oponente)
    {
        return pierde;
    }
    else
    {
        // Vectores de los colores con los que juego y los del oponente
        vector<color> my_colors = estado.getPlayerColors(jugador);
        vector<color> op_colors = estado.getPlayerColors(oponente);

        // Recorro todas mis fichas
        double puntuacion_jugador = 0;
        // Recorro colores de mi jugador.
        for (int i = 0; i < my_colors.size(); i++)
        {
            color c = my_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++)
            {
                // Favorecemos que las fichas estén en la cola de meta
                if(estado.getBoard().getPiece(c,j).type == final_queue)
                    puntuacion_jugador += 68 +  estado.getBoard().getPiece(c,j).num; // 68 es el tamaño del tablero

                
                // Valoro positivamente que la ficha esté en casilla segura o meta.
                if (estado.isSafePiece(c, j))
                    puntuacion_jugador++;
                
                // Interesa sacar fichas de casa
                if (estado.getBoard().getPiece(c, j).type == home)
                {
                    puntuacion_jugador -= 100;
                }
                
                // Favorece meter casillas a la meta
                if (estado.getBoard().getPiece(c, j).type == goal)
                    puntuacion_jugador += 100;
            }
        }

        // Recorro todas las fichas del oponente
        double puntuacion_oponente = 0;
        // Recorro colores del oponente.
        for (int i = 0; i < op_colors.size(); i++)
        {
            color c = op_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++)
            {
                if(estado.getBoard().getPiece(c,j).type == final_queue)
                    puntuacion_oponente += 68 + estado.getBoard().getPiece(c,j).num;
                
                // Cuantas mas casillas en casa, mejor para nosotros
                if (estado.getBoard().getPiece(c, j).type == home)
                {
                    puntuacion_oponente -= 100;
                }
            }
        }

        // Devuelvo la puntuación de mi jugador menos la puntuación del oponente.
        return puntuacion_jugador - puntuacion_oponente;
    }
}

double AIPlayer::valoracionDefinitiva(const Parchis &estado, int jugador){
    int ganador = estado.getWinner();
    int oponente = (jugador + 1) % 2;

    // Devuelvo +/- infinito según si he ganado yo o el oponente.
    if (ganador == jugador)
        return gana;
    else if (ganador == oponente)
        return pierde;
    else
    {
        // Vectores de los colores con los que juego y los del oponente
        vector<color> my_colors = estado.getPlayerColors(jugador);
        vector<color> op_colors = estado.getPlayerColors(oponente);
        vector<int> my_pos, op_pos;
        
        // Recorro todas mis fichas
        double puntuacion_jugador = 0;
        int posicion_tablero = 0;
        // Recorro colores de mi jugador.
        for (int i = 0; i < my_colors.size(); i++)
        {
            color c = my_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++)
            {   
                // Favorecemos que las fichas estén en la cola de meta
                if(estado.getBoard().getPiece(c,j).type == final_queue){
                    posicion_tablero = 68 +  estado.getBoard().getPiece(c,j).num; // 68 es el tamaño del tablero
                    puntuacion_jugador += posicion_tablero;
                }
                else
                    posicion_tablero = estado.getBoard().getPiece(c,j).num;
                    
                
                // Valoro positivamente que la ficha esté segura
                if (estado.isSafePiece(c, j))
                    puntuacion_jugador+=10;
                else
                    my_pos.push_back(posicion_tablero);

                
                // Interesa sacar fichas de casa
                if (estado.getBoard().getPiece(c, j).type == home)
                {
                    puntuacion_jugador -= 100;
                }
                
                // Favorece meter casillas a la meta
                if (estado.getBoard().getPiece(c, j).type == goal)
                    puntuacion_jugador += 100;
            }
        }

        // Recorro todas las fichas del oponente
        double puntuacion_oponente = 0;
        // Recorro colores del oponente.
        for (int i = 0; i < op_colors.size(); i++)
        {
            color c = op_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++)
            {
                // Favorecemos que las fichas estén en la cola de meta
                if(estado.getBoard().getPiece(c,j).type == final_queue){
                    posicion_tablero = 68 +  estado.getBoard().getPiece(c,j).num; // 68 es el tamaño del tablero
                    puntuacion_oponente += posicion_tablero;
                }
                else
                    posicion_tablero = estado.getBoard().getPiece(c,j).num;
                    
                op_pos.push_back(posicion_tablero);

                
                //Cuantas mas casillas en casa, mejor para nosotros
                if (estado.getBoard().getPiece(c, j).type == home)
                {
                    puntuacion_oponente -= 100;
                }
            }
        }
        
        for(int i = 0; i < my_pos.size(); i++){
            for(int j = 0; j < op_pos.size(); j++){
                if(my_pos[i]-7 <= op_pos[j] and op_pos[j] <= my_pos[i]) //Si tengo una pieza enemiga detrás mia en un rango de 7
                    puntuacion_oponente+=9;
                else if(op_pos[j] >= my_pos[i] and op_pos[j] <= my_pos[i]+7) //Si tengo una pieza enemiga delante mia en un rango de 7
                    puntuacion_jugador+=9;
            }
        }

        // Devuelvo la puntuación de mi jugador menos la puntuación del oponente.
        return puntuacion_jugador - puntuacion_oponente;
    }
}
