#include "player.h"
#include "loadsound.h"
#include <iostream>
#include <QGraphicsScene>
#include <QDebug>
#include <QPixmap>

#include "animatedsprites.h"

using namespace std;

Player::Player()
{

}

Player::Player(int x,int y, MapLoader* ml, QGraphicsScene *scene) : QGraphicsItem(0, scene)
{    
    pacmanSprites = new QPixmap("../images/sprites.png");
    initXCoord = x;
    initYCoord = y;

    step = STEPS;
    keySetFlag = false;
    this->ml = ml;

    setFlag(ItemIsFocusable);

    actionmap.insert(Qt::Key_Up, Up);
    actionmap.insert(Qt::Key_Down, Down);
    actionmap.insert(Qt::Key_Right, Right);
    actionmap.insert(Qt::Key_Left, Left);
    setFocus();

    //dyingTimer = new QTimer( this );
    //connect(dyingTimer, SIGNAL(timeout()), this, SLOT(dyingTimeOut()));

    init();
    setAndAddStates();
    pacmanfsm.setInitialState("PACMAN_INIT");
    pacmanInit = true;
    animSteps = NORMAL_ANIM_STEPS;

    powerdot = false;
    imageSize = IMAGE_SIZE;
    eatenDot = 0;
    lives = 4;
    TopBar::updateLives(0);
}

int Player::eatenDot = 0;

bool Player::isPacmanInInit()
{
    return pacmanInit;
}

void Player::init()
{
    xCoord = initXCoord;
    yCoord = initYCoord;

    enemyCollision = false;

    xdir = step;
    ydir = 0;
    xNext = 0;
    yNext = 0;
    xPrev = 0;
    yPrev = 0;

    prevDir = RIGHT;
    dir = RIGHT;
    animDir = dir;
    isTimeOut = false;
    slowDownAnim = true;
    powerdot = false;
    pacmanInit = true;
    dyingAnimCount = 0;
    animSteps = NORMAL_ANIM_STEPS;
    currentFrame = 0;
}

int Player::type() const
{
    return ID_PLAYER;
}

int Player::getDotScore()
{
    return eatenDot;
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(0, 0, *pacmanSprites, ((imageSize)*(currentFrame%animSteps)+2), ((animDir-1)*imageSize +2), PACMAN_WIDTH,PACMAN_HEIGHT);
}

QRectF Player::boundingRect() const
{
    return QRectF(0,0,PACMAN_WIDTH,PACMAN_HEIGHT);
}

void Player::setAndAddStates()
{
    State initState("PACMAN_INIT", PACMAN_INIT);
    initState.addEventAndNextState("init_timeout", "PACMAN_PLAY");
    initState.addEventAndNextState("reset", "PACMAN_INIT");
    initState.setProperty("steady");
    pacmanfsm.addState(initState);

    State playState("PACMAN_PLAY", PACMAN_PLAY); // creating play state
    playState.addEventAndNextState("ghost_hits_pacman","PACMAN_DYING");
    playState.addEventAndNextState("reset", "PACMAN_INIT");
    playState.setProperty("moving");
    pacmanfsm.addState(playState);

    State dyingState("PACMAN_DYING", PACMAN_DYING); // creating a Dying state
    dyingState.addEventAndNextState("dying_timeout" , "PACMAN_INIT");
    pacmanfsm.addState(dyingState);
}

void Player::advance(int phase)
{
    this->setPos(xCoord, yCoord);
}

void Player::update()
{
    int state = pacmanfsm.getStateIndex();
    bool prevDirCol;

    switch(state)
    {
        case PACMAN_INIT:
            if(pacmanfsm.inENTRY())
                init();
            else
                pacmanfsm.handleEvent("init_timeout");

        break;

        case PACMAN_PLAY:
           pacmanInit = false;
           prevDirCol = checkCollWithPrevDir();

            if(xNext != 0 || yNext != 0)
            {
                xdir = xNext;
                ydir = yNext;
                dir = nextDir;
                animDir = dir;
            }
            checkCollWithNextDir(prevDirCol);
            colWithOtherItems();

            xCoord += xdir;
            yCoord += ydir;
            enterTunnel();
            keySetFlag = false;
        break;

        case PACMAN_DYING:
            if(pacmanfsm.inENTRY())
            {
                dyingFrame = -1;
                slowDownAnim = 0;
                dying->play();
                locFrame = 1;
            }

            animDir = 6;
            animSteps = DYING_ANIM_STEPS;
            if(slowDownAnim == 0)
            {
                dyingFrame++;
                currentFrame = dyingFrame-1;
                dyingAnimCount++;
                if(dyingFrame < 7)
                {
                    scene()->update(xCoord,yCoord,PACMAN_WIDTH,PACMAN_HEIGHT);
                }
            }

            slowDownAnim = locFrame%3;
            locFrame++;
            
            if(dyingAnimCount%16 == 0)
            {
                pacmanfsm.handleEvent("dying_timeout");
            }
        break;
    }
    pacmanfsm.update();
    currentFrame++;
}

bool Player::isEnemyCollided()
{
    return enemyCollision;
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
void Player::colWithOtherItems()
{
    enemyCollision = false;
    QList<QGraphicsItem *> list;
    list = scene()->items(xCoord+10 , yCoord+10, 10,10);

    for(int i = 0; i < list.size(); i++)
    {
        switch(list.at(i)->type())
        {
        case ID_DOT:
            scene()->removeItem(list.at(i));
                eatSound->play();
            eatenDot += 10;
            break;

        case ID_BIGDOT:
            scene()->removeItem(list.at(i));
            eatSound->play();
            eatenDot += 50;
            powerdot = true;
            Enemy::superPlayer();
            break;

        case Enemy::ID_ENEMY:
            enemyCollision = true;
            ((Enemy*) list.at(i))->killed();
            break;
        }
    }
}

//Handling key press event
void Player::keyPressEvent(QKeyEvent *event)//Handles key press event
{
    if(!keySetFlag)
    {
         Action a = actionmap.value(event->key());
         xPrev = xdir;   //Storing prev xdir and ydir before getting new keypress values
         yPrev = ydir;   //Storing prev xdir and ydir before getting new keypress values
         prevDir = dir;
         //animDir = dir;

         switch (a)
         {
             case Up:
                ydir = -step;
                xdir = 0;
                dir = UP   ;
                break;

             case Down:
                ydir = step;
                xdir = 0;
                dir = DOWN;
                break;

             case Left:
                xdir = -step;
                ydir = 0;
                dir = LEFT;
                break;

             case Right:
                xdir = step;
                ydir = 0;
                dir = RIGHT;
                break;

             default:
                xdir = xPrev;
                ydir = yPrev;
                dir = prevDir;
                break;
         }
         keySetFlag = true;

         xNext = xdir; // Storing new keypress values in yNext n xNext
         yNext = ydir;
         nextDir = dir;
         //animDir = dir;
         }
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
                     animDir = dir;
                     //qDebug() << "A bug 1?";
                }
                else//if collision is detected for no keypress, thn stop
                {
                     xdir = 0 ;
                     ydir = 0 ;
                     //animDir = dir;
                     dir = prevDir;
                     animDir = dir;
                     currentFrame = 0;
                     //qDebug() << "A bug 2 ?" << "animDir: " << animDir << "dir: " << dir;
                }
            }
            else // no collision
            {
                xNext = 0;
                yNext = 0;
                prevDir = dir;
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
                     animDir = dir;
                }
                else//if collision is detected for 1st keypress, thn stop
                {
                     xdir = 0 ;
                     ydir = 0 ;
                     //animDir = dir;
                     dir = prevDir;
                     animDir = dir;
                     currentFrame = 0;
                }
            }
            else
            {
                xNext = 0;
                yNext = 0;
                prevDir = dir;
            }
            break;
    }
}

bool Player::eatenPowerDot()
{
    //qDebug() << "POWERDOT : " << powerdot;
    bool pd = powerdot;
    powerdot = false;
    return pd;
}

//Generating keys for checkin collision with walls
int Player::keyGeneration(int dir)//Generates key
{
    int xt = 0;
    int yt = 0;
    int mode = 0;
    switch(dir)//keys generation
    {
        case UP : //UP
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

         case DOWN: //down
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

         case LEFT: //left
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

         case RIGHT : //right

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

void Player::handleEvent(QString event)
{
    pacmanfsm.handleEvent(event);
}

