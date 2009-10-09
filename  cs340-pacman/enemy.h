/***************************
  File Name : enemy.h
  Cretaed By : Usha Sanaga
  **************************/


#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"
#include "maploader.h"
#include <math.h>
#include <iostream>

class Enemy : public Character {
    private:
        MapLoader* ml;
    public:
        Enemy(int, int, int, MapLoader*);
        int getType() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget);
        void advance(int);

};

#endif // ENEMY_H
