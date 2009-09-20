#include "enemy.h"

Enemy::Enemy(int x,int y, int dir) : Character::Character(x,y,dir)
{

}

 int Enemy::getType() {
    return TYPE_ENEMY;
}



