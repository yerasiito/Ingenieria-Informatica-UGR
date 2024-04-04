#include "RemotePlayer.h"
#include "Parchis.h"

void RemotePlayer::perceive(Parchis &p){
    //Call to super
    Player::perceive(p);

    if(actual->getTurn() > 1){
        int turn = actual->getTurn();
        tuple <color, int, int> last_action = actual->getLastAction();
        color c = get<0>(last_action);
        int id = get<1>(last_action);
        int dice = get<2>(last_action);
        controller->sendParchisMove(turn, c, id, dice);
    }
}

bool RemotePlayer::move(){
    bool moved = false;

    while(!moved){
        Packet packet;
        cout << "Esperando movimiento del oponente..." << endl;
        MessageKind msgkind = controller->receive(packet);
        
        switch(msgkind){
            case MOVED:
                int turn;
                color c_piece;
                int id_piece;
                int dice;
                controller->packet2move(packet, turn, c_piece, id_piece, dice);

                if(turn <= actual->getTurn()){
                    cout << "Old move received. Already up to date." << endl;
                    //controller->sendOKMoved();
                    break;
                }
                else if(turn > actual->getTurn() + 1){
                    cout << "WTF move too new. Some turns have been missed." << endl;
                    break;
                }
                else{
                    cout << "Current move received. Moving..." << endl;
                    actual->movePiece(c_piece, id_piece, dice);
                    moved = true;
                    //controller->sendOKMoved();
                    return true;
                }
                
            case TEST_ALIVE:
                cout << "102 TEST_ALIVE received. Still alive." << endl;
                break;
            case ERROR_DISCONNECTED:
                cout << "400 ERROR_DISCONNECTED received. Disconnected." << endl;
                actual->endGame();
                return false;
            default:
                cout << "Error: Unexpected " << msgkind << " received." << endl;
                return false;
        
        }
    }
    return true;
}

bool RemotePlayer::readyForNextTurn(){
    return true;
    /*
    Packet packet;
    MessageKind msgkind = controller->receive(packet);
    switch(msgkind){
        case TEST_ALIVE:
            cout << "102 TEST_ALIVE received. Still alive." << endl;
            return false;
        case ERROR_DISCONNECTED:
            cout << "400 ERROR_DISCONNECTED received. Disconnected." << endl;
            actual->endGame();
            return false;
        case OK_MOVED:
            cout << "201 OK_MOVED received. Ready for next turn." << endl;
            return true;
        default:
            cout << "Error: Unexpected " << msgkind << " received." << endl;
            return false;
    }
    */
}