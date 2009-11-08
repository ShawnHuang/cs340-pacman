#include "player.h"

#include <iostream>
#include <QGraphicsScene>
#include <QDebug>

using namespace std;

Player::Player()
{

}

Player::Player(int x,int y, MapLoader* ml, QGraphicsScene *scene) : QGraphicsItem(0, scene)
{
    xCoord = x;
    yCoord = y;

    initXCoord = x;
    initYCoord = y;

    xdir = 1;
    ydir = 0;
    xNext = 0;
    yNext = 0;
    xPrev = 0;
    yPrev = 0;

    prevDir = 4;
    dir = 4;
    this->ml = ml;

    whichDot = 0;

    setFlag(ItemIsFocusable);

    actionmap.insert(Qt::Key_Up, Up);
    actionmap.insert(Qt::Key_Down, Down);
    actionmap.insert(Qt::Key_Right, Right);
    actionmap.insert(Qt::Key_Left, Left);
    setFocus();

    setAndAddStates();
    pacmanfsm.setInitialState("INIT");
}

int Player::type() const
{
    return ID_PLAYER;
}

int Player::getDotType()
{
    return whichDot;
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
    State dyingState("DYING"); // creating a Dying state

    initState.addEventAndNextState("init_timeout", "PLAY");
    initState.setProperty("steady");

    playState.addEventAndNextState("ghost_hits_pacman","DYING");
    playState.setProperty("moving");

    dyingState.addEventAndNextState("dying_timeout" , "INIT");
    pacmanfsm.addState(initState);
    pacmanfsm.addState(playState);
    pacmanfsm.addState(dyingState);
}

void Player::advance(int phase)
{
    if(pacmanfsm.getState() == "INIT")
    {
        this->setPos(xCoord, yCoord);
        pacmanfsm.handleEvent("init_timeout");
        QString a = pacmanfsm.getState();
        //qDebug() << a;
    }

    if(pacmanfsm.getState() == "PLAY")
    {
        bool prevDirCol = checkCollWithPrevDir();

        if(xNext != 0 || yNext != 0)
        {
            xdir = xNext;
            ydir = yNext;
            dir = nextDir;
        }
        checkCollWithNextDir(prevDirCol);
        eatDots();
        QString a = pacmanfsm.getState();
        //qDebug() << a;

        xCoord += xdir;
        yCoord += ydir;

        enterTunnel();
        this->setPos(xCoord, yCoord);
    }
    pacmanfsm.update();
}

//tunnel movements
void Player::enterTunnel()
{
    if( xCoord < -20)
    {
        xCoord = 560;
    }
     if(xCoord > 560)
    {
        xCoord = -20;
    }
}

// Checking Dot/BigDot collision
void Player::eatDots()
{
    QMap<QString, CoordChar>::const_iterator it;
    switch(dir)
    {
        case 1://up
            key = new QString(QChar(xCoord+10));
            key->append(QChar('_')).append(QChar(yCoord+5));
            break;
        case 2://down
            key = new QString(QChar(xCoord+10));
            key->append(QChar('_')).append(QChar(yCoord+25));
            break;
        case 3://left
            key = new QString(QChar(xCoord+5));
            key->append(QChar('_')).append(QChar(yCoord+10));
            break;
        case 4://right
            key = new QString(QChar(xCoord+25));
            key->append(QChar('_')).append(QChar(yCoord+10));
            break;
    }
    it = ml->sceneItemsMap.find(*key);//checking for dots
    QList<QGraphicsItem *> list;
    switch(it.value().symbol)
    {
        case 46:

            list = scene()->items(it.value().xcoord , it.value().ycoord, 5, 5);
            for(int i = 0; i < list.size(); i++)
            {
                if(list.at(i)->type() == ID_DOT)
                {
                    scene()->removeItem(list.at(i));
                    whichDot = ID_DOT;
                    break;
                }
            }
            qDebug() << whichDot;
            ml->sceneItemsMap.remove(*key);
            break;

        case 79:
            list = scene()->items(it.value().xcoord , it.value().ycoord,15,15);
            for(int i = 0; i < list.size(); i++)
            {
                if(list.at(i)->type() == ID_BIGDOT)
                {
                    scene()->removeItem(list.at(i));
                    whichDot = ID_BIGDOT;
                    break;
                }
            }
            qDebug() << whichDot;
            ml->sceneItemsMap.remove(*key);
            break;
        }
}
//Handling key press event
void Player::keyPressEvent(QKeyEvent *event)//Handles key press event
{
     Action a = actionmap.value(event->key());
     xPrev = xdir;   //Storing prev xdir and ydir before getting new keypress values
     yPrev = ydir;   //Storing prev xdir and ydir before getting new keypress values
     prevDir = dir;

         switch (a)
         {
             case Up:
                ydir = -1;
                xdir = 0;
                dir = 1;
                break;

             case Down:
                ydir = 1;
                xdir = 0;
                dir = 2;
                break;

             case Left:
                xdir = -1;
                ydir = 0;
                dir = 3;
                break;

             case Right:
                xdir = 1;
                ydir = 0;
                dir =4;
                break;

             default:
                xdir = 0;
                ydir = 0;
                dir = 0;
                break;
         }

         xNext = xdir; // Storing new keypress values in yNext n xNext
         yNext = ydir;
         nextDir = dir;
}

//Generating keys for checkin collision with walls
int Player::keyGeneration(int dir)//Generates key
{
    int xt = 0;
    int yt = 0;
    int mode = 0;
    switch(dir)//keys generation
    {
        case 1 : //UP
            if(xCoord%10 == 0)
            {
                key = new QString(QChar(xCoord));
                key->append(QChar('_')).append(QChar(yCoord-10));
                key1 = new QString(QChar(xCoord+10));
                key1->append(QChar('_')).append(QChar(yCoord-10));
                key2 = new QString(QChar(xCoord+20));
                key2->append(QChar('_')).append(QChar(yCoord-10));
                mode =0;
            }
            else
            {
                xt = xCoord/10;
                xt = xt*10;
                key = new QString(QChar(xt));
                key->append(QChar('_')).append(QChar(yCoord-10));
                key1 = new QString(QChar(xt+10));
                key1->append(QChar('_')).append(QChar(yCoord-10));
                key2 = new QString(QChar(xt+20));
                key2->append(QChar('_')).append(QChar(yCoord-10));
                key3 = new QString(QChar(xt+30));
                key3->append(QChar('_')).append(QChar(yCoord-10));
                mode = 1;
            }
            break;

         case 2: //down
             if(xCoord%10 == 0)
             {
                key = new QString(QChar(xCoord));
                key->append(QChar('_')).append(QChar(yCoord+30));
                key1 = new QString(QChar(xCoord+10));
                key1->append(QChar('_')).append(QChar(yCoord+30));
                key2 = new QString(QChar(xCoord+20));
                key2->append(QChar('_')).append(QChar(yCoord+30));
                mode = 0;
             }
             else
             {
                xt = xCoord/10;
                xt = xt*10;
                key = new QString(QChar(xt));
                key->append(QChar('_')).append(QChar(yCoord+30));
                key1 = new QString(QChar(xt+10));
                key1->append(QChar('_')).append(QChar(yCoord+30));
                key2 = new QString(QChar(xt+20));
                key2->append(QChar('_')).append(QChar(yCoord+30));
                key3 = new QString(QChar(xt+30));
                key3->append(QChar('_')).append(QChar(yCoord+30));
                mode = 1;
             }
             break;

         case 3: //left
             if(yCoord%10 == 0)
             {
                key = new QString(QChar(xCoord-10));
                key->append(QChar('_')).append(QChar(yCoord));
                key1 = new QString(QChar(xCoord-10));
                key1->append(QChar('_')).append(QChar(yCoord+10));
                key2 = new QString(QChar(xCoord-10));
                key2->append(QChar('_')).append(QChar(yCoord+20));
                mode = 0;
             }
             else
             {
                yt = yCoord/10;
                yt = yt*10;
                key = new QString(QChar(xCoord-10));
                key->append(QChar('_')).append(QChar(yt));
                key1 = new QString(QChar(xCoord-10));
                key1->append(QChar('_')).append(QChar(yt+10));
                key2 = new QString(QChar(xCoord-10));
                key2->append(QChar('_')).append(QChar(yt+20));
                key3 = new QString(QChar(xCoord-10));
                key3->append(QChar('_')).append(QChar(yt+30));
                mode = 1;
             }
             break;

         case 4 : //right

             if(yCoord%10 == 0)
             {
                key = new QString(QChar(xCoord+30));
                key->append(QChar('_')).append(QChar(yCoord));
                key1 = new QString(QChar(xCoord+30));
                key1->append(QChar('_')).append(QChar(yCoord+10));
                key2 = new QString(QChar(xCoord+30));
                key2->append(QChar('_')).append(QChar(yCoord+20));
                mode = 0;
              }
             else
             {
                yt = yCoord/10;
                yt = yt*10;
                key = new QString(QChar(xCoord+30));
                key->append(QChar('_')).append(QChar(yt));
                key1 = new QString(QChar(xCoord+30));
                key1->append(QChar('_')).append(QChar(yt+10));
                key2 = new QString(QChar(xCoord+30));
                key2->append(QChar('_')).append(QChar(yt+20));
                key3 = new QString(QChar(xCoord+30));
                key3->append(QChar('_')).append(QChar(yt+30));
                mode = 1;
             }
             break;
    }
    return mode;
}

//Checking collision in prev dir
bool Player::checkCollWithPrevDir()
{
    QMap<QString, CoordChar>::const_iterator it;
    QMap<QString, CoordChar>::const_iterator it1;
    QMap<QString, CoordChar>::const_iterator it2;
    QMap<QString, CoordChar>::const_iterator it3;

    bool prevDirCol = false;
    int mode = keyGeneration(prevDir);

    it = ml->sceneItemsMap.find(*key);
    it1 = ml->sceneItemsMap.find(*key1);
    it2 = ml->sceneItemsMap.find(*key2);

    switch(mode)//checking for collision
    {
        case 0:
            if(it.value().symbol == 43 || it1.value().symbol == 43 || it2.value().symbol == 43) //collision detected
            {
                prevDirCol = true;
            }
            break;

        case 1:
            it3 = ml->sceneItemsMap.find(*key3);
            if(it.value().symbol == 43 || it1.value().symbol == 43|| it2.value().symbol == 43 || it3.value().symbol == 43)
            {
                prevDirCol = true;
            }
            break;
    }
    return prevDirCol;
}

//checkin collision in new direction
void Player::checkCollWithNextDir(bool prevDirCol)
{
    QMap<QString, CoordChar>::const_iterator it;
    QMap<QString, CoordChar>::const_iterator it1;
    QMap<QString, CoordChar>::const_iterator it2;
    QMap<QString, CoordChar>::const_iterator it3;

    int mode = keyGeneration(dir);

    it = ml->sceneItemsMap.find(*key);
    it1 = ml->sceneItemsMap.find(*key1);
    it2 = ml->sceneItemsMap.find(*key2);

    switch(mode)//checking for collision
    {
        case 0:
            if(it.value().symbol == 43 || it1.value().symbol == 43 || it2.value().symbol == 43) //collision detected
            {
                if((xNext != 0 || yNext != 0) && prevDirCol == false)//if collision detected for xNext n yNext that is the key press,thn go back to first keypress
                {
                     xdir = xPrev ;
                     ydir = yPrev ;
                     dir = prevDir;
                }
                else//if collision is detected for no keypress, thn stop
                {
                     xdir = 0 ;
                     ydir = 0 ;
                }
            }
            else // no collision
            {
                xNext = 0;
                yNext =0;
            }
            break;

        case 1:
            it3 = ml->sceneItemsMap.find(*key3);
            if(it.value().symbol == 43 || it1.value().symbol == 43||
              it2.value().symbol == 43 || it3.value().symbol == 43)
            {
               if((xNext != 0 || yNext != 0) && prevDirCol == false)//if collision detected for xNext n yNext that is the second key press,thn go back to first keypress
                {
                     xdir = xPrev ;
                     ydir = yPrev ;
                     dir = prevDir;
                }
                else//if collision is detected for 1st keypress, thn stop
                {
                     xdir = 0 ;
                     ydir = 0 ;
                }
            }
            else
            {
                xNext = 0;
                yNext =0;
            }
            break;
    }
}








