/*****************************
  Fiel Name : enemy.cpp
  Created By : Usha Sanaga
  Description : Created a garphical representation of enemy
  ****************************/


#include "enemy.h"

Enemy::Enemy(int x,int y, int dir) : Character::Character(x,y,dir)
{

}

 int Enemy::getType() const {
    return TYPE_ENEMY;
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
   painter->setBrush(Qt::Dense7Pattern);
   painter->setPen (Qt::yellow);
   painter->fillRect(0, 0,
                     Character::X_WIDTH*Character::CHARACTER_WIDTH,
                     Character::Y_HEIGHT*Character::CHARACTER_HEIGHT,
                     Qt::darkYellow);

//   painter->setBrush(Qt::Dense6Pattern);
//   painter->setPen (Qt::darkCyan);
//   int startAngle = 30 * 16;
//   int spanAngle = 120 * 16;
//   painter->drawArc(0, 0, X_WIDTH*CHARACTER_WIDTH, Y_HEIGHT*CHARACTER_HEIGHT/2, startAngle, spanAngle);

}




