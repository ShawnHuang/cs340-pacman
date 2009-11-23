/***************************
  File Name : enemy.h
  Cretaed By : Usha Sanaga
  **************************/


#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"
#include "player.h"
#include "maploader.h"
#include <math.h>
#include "state.h"
#include "fsm.h"
#include <QList>
#include <QString>

class Enemy : public Character {
    private:
        MapLoader* ml;

        static const int INIT_STATE = 0;
        static const int PLAY_STATE = 1;
        static const int FOLLOW_STATE = 2;
        static const int DYING_STATE = 3;

        QString INIT; //= "INIT";
        QString PLAY; //= "RANDOM_PLAY";
        QString FOLLOW; //= "FOLLOW_PLAYER";
        QString DYING; //= "DYING";

        bool isWallPresent(int);
        void removeOddOption(QList<int> *);

    public:
        Enemy(int, int, int, MapLoader*);
        static const int ID_ENEMY  = 10;
        int getType() const;
        virtual int type() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
        void update();
        FSM fsm;
        void setAndAddStates();
};

#endif // ENEMY_H
