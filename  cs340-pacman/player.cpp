#include "player.h"

Player::Player()
{
}

Player::Player(int x,int y, int dir) : Character::Character(x,y,dir)
{
}

int Player::getTYpe()
{
    return TYPE_PLAYER;
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
   painter->setBrush(Qt::yellow);
   painter->setPen(Qt::yellow);
   painter->drawEllipse(0,0,30,30);
}

QRectF Player::boundingRect() const
{
    return QRectF(0,0,30,30);
}

void Player::setAndAddStates()
{
    State initState("INIT");//creating INIT state
    State playState("PLAY"); // creating play state
    State dyingState("DYING"); // creeating a Dying state

    initState.addEventAndNextState("init_timeout", "PLAY");
    initState.setProperty("steady");

    playState.addEventAndNextState("ghost_hits_pacman","DYING");
    playState.setProperty("moving");

    dyingState.addEventAndNextState("dying_timeout" , "INIT");
}

void Player::update()
{

}



















