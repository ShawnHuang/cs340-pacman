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
#include <QTime>

static QTime SUPER_PLAYER_TIME;
static QList<int> GO_INIT;

class Enemy : public Character {
    private:
        MapLoader* ml;

        static const int INIT_STATE = 0;
        static const int PLAY_STATE = 1;
        static const int FOLLOW_STATE = 2;
        static const int DYING_STATE = 3;
        static const int ZOMBIE_STATE = 4;
        static const int DEAD_STATE = 5;
        static const int DYING_STATE_LIMIT = 4000;
        static const int ZOMBIE_STATE_LIMIT = 1000;
        static const int DEAD_TIMEOUT = 5000;

        int initX;
        int initY;

        QString INIT; //= "INIT";
        QString PLAY; //= "RANDOM_PLAY";
        QString FOLLOW; //= "FOLLOW_PLAYER";
        QString DYING; //= "DYING";
        QString ZOMBIE; //= "ZOMBIE";
        QString DEAD; //= "DEAD";

        bool isWallPresent(int);
        void removeOddOption(QList<int> *);

        QPixmap *spritesImage;

        int myId;
        bool move;

        void dyingCheck();
        QTime deadTime;
        bool doneInit;

    public:
        Enemy(int, int, int, MapLoader*);
        static const int ID_ENEMY  = 10;
        int getType() const;
        virtual int type() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
        void update();
        FSM fsm;
        void setAndAddStates();
        void killed();
        static void superPlayer();
};

#endif // ENEMY_H
