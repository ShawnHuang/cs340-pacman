/********************************
File Name : Character.h
Cretaed and Modified by : Usha Sanaga
*********************************/

#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QRectF>
#include <Qt>
#include <QDebug>
#include "loadsound.h"

static int ENEMY_COUNT  = 0;

static double POSITION_OFFSET = .5;

class Character : public QGraphicsItem
{
protected:
    double xCoor;
    double yCoor;
    int direction;
    int turnDir;


public:
    Character();
    Character(int, int, int);
    static const int CHARACTER_WIDTH = 10;
    static const int CHARACTER_HEIGHT = 10;
    static const int X_WIDTH = 3;
    static const int Y_HEIGHT = 3;

    static const int TYPE_PLAYER = 1;
    static const int TYPE_ENEMY = 2;
    static const int DIR_UP = 1;
    static const int DIR_DOWN = 2;
    static const int DIR_RIGHT = 3;
    static const int DIR_LEFT = 4;

    static const int TURN_FRONT = 0;
    static const int TURN_RIGHT = 1;
    static const int TURN_LEFT = -1;

    int getX();
    int getY();

    virtual int type() const = 0;
    void advance(int);
    int getDirection();
    virtual int getType() const = 0;
    void moveForward();
    virtual QRectF boundingRect() const;
    void makeTurn(long);
};



#endif // CHARACTER_H
