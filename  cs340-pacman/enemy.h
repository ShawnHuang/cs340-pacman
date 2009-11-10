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
#include "state.h"
#include "fsm.h"

class Enemy : public Character {
    private:
        MapLoader* ml;
        static const int INIT_STATE = 0;
        static const int RANDOM_STATE = 1;
        static const int FOLLOW_STATE = 2;
        static const int DYING_STATE = 3;
    public:
        Enemy(int, int, int, MapLoader*);
        int getType() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
        void advance(int);
        FSM fsm;
        void setAndAddStates();

};

#endif // ENEMY_H
