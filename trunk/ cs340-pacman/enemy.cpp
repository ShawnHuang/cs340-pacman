#include "enemy.h"

Enemy::Enemy(int x,int y) : Character::Character(x,y)
{

}

 int Enemy::getType() {
    return TYPE_ENEMY;
}



