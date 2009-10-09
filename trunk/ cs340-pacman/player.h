#ifndef PLAYER_H
#define PLAYER_H

#include "state.h"
#include "fsm.h"
#include "character.h"
class Player : public Character
{
private:
    FSM pacmanfsm;
    void setAndAddStates();

public:
    Player();
    Player(int ,int, int);
    void update();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    int getTYpe();
    QRectF boundingRect() const;

};

#endif // PLAYER_H


