#include "player.h"

Player::Player(int x,int y, int dir) : Character::Character(x,y,dir)
{

}

int Player::getTYpe() {
    return TYPE_PLAYER;
}




