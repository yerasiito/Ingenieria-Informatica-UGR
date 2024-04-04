# include "Player.h"
# include "Parchis.h"

void Player::perceive(Parchis & p){
    actual = &p;
    jugador = actual->getCurrentPlayerId();
}