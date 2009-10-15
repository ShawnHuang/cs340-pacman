#include "player.h"
#include <Qt>
Player::Player()
{

}

Player::Player(int x,int y, QGraphicsScene *scene) : QGraphicsItem(0, scene)
{
    xCoord = x;
    yCoord = y;
    setFlag(ItemIsFocusable);

     actionmap.insert(Qt::Key_Up, Up);
     actionmap.insert(Qt::Key_Down, Down);
     actionmap.insert(Qt::Key_Right, Right);
     actionmap.insert(Qt::Key_Left, Left);
     setFocus();
     setPos(260, 300);

}

int Player::getTYpe()
{
    return 0;
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
   painter->setBrush(Qt::yellow);
   painter->setPen(Qt::yellow);
   painter->drawEllipse(xCoord,yCoord,30,30);
}

QRectF Player::boundingRect() const
{
    return QRectF(xCoord,yCoord,30,30);
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

void Player::keyPressEvent(QKeyEvent *event)
{
    Action a = actionmap.value(event->key());

     switch (a)
     {
         case Right:
            xCoord += 1;
            break;

          case Left:
            xCoord -= 1;
            break;

          case Down:
            yCoord += 1;
            break;

          case Up:
            yCoord -= 1;
            break;

          default:
            break;
     }
     this->setPos(xCoord, yCoord);
     //event->accept();
}














