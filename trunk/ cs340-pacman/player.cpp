#include "player.h"

Player::Player(int x,int y) : Character::Character(x,y)
{

}

int Player::getTYpe() {
    return TYPE_PLAYER;
}




