#ifndef PLAYER_H
#define PLAYER_H

#include "state.h"
#include "fsm.h"
#include "maploader.h"
#include "dot.h"
#include "bigdot.h"

#include<QGraphicsItem>
#include <QPainter>
#include <QRectF>
#include <QKeyEvent>

#define ID_PLAYER 4

class Player: public QGraphicsItem
{
private:
    int xCoord;
    int yCoord;
    int initXCoord;
    int initYCoord;
    int xdir;
    int ydir;
    int xPrev;
    int yPrev;
    int xNext;
    int yNext;

    FSM pacmanfsm;
    void setAndAddStates();
    MapLoader* ml;
    int dir;
    int prevDir;
    int nextDir;
    int mode;
    int whichDot;

    QString *key;
    QString *key1;
    QString *key2;
    QString *key3;

    int keyGeneration(int);

public:
    Player();
    Player(int ,int, MapLoader*, QGraphicsScene *scene = 0);
    virtual int type() const;
    int getDotType();
    void advance(int phase);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int getTYpe();
    QRectF boundingRect() const;
    void keyPressEvent(QKeyEvent * event );
    void enterTunnel();
    void eatDots();
    bool checkCollWithPrevDir();
    void checkCollWithNextDir(bool);

    enum Action {Up = 1, Down, Left, Right};
    QMap< int, Action > actionmap;

};

#endif // PLAYER_H


