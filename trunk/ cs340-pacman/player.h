#ifndef PLAYER_H
#define PLAYER_H

#include "state.h"
#include "fsm.h"

#include<QGraphicsItem>
#include <QPainter>
#include <QRectF>
#include <QKeyEvent>


class Player: public QGraphicsItem
{
private:
    int xCoord;
    int yCoord;
    FSM pacmanfsm;
    void setAndAddStates();

public:
    Player();
    Player(int ,int, QGraphicsScene *scene = 0);
    void update();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int getTYpe();
    QRectF boundingRect() const;
    void keyPressEvent(QKeyEvent * event );

    enum Action {Up, Down, Left, Right};
    QMap< int, Action > actionmap;

};

#endif // PLAYER_H


