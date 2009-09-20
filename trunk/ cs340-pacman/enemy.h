/***************************
  File Name : enemy.h
  Cretaed By : Usha Sanaga
  **************************/


#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"

class Enemy : public Character {
    public:
        Enemy(int, int,int);
    public:
    int getType() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

};

#endif // ENEMY_H
