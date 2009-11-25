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
    initXCoord = x;
    initYCoord = y;

    //init_timer = new QTimer( this );
    //connect( init_timer, SIGNAL(timeout()), this, SLOT(setTimeOut()) );

    loadAnimations();

    currentAnim = RIGHT_ANIM;
    currentFrame = 0;
    
    step = 10;

    keySetFlag = false;

    this->ml = ml;

    setFlag(ItemIsFocusable);

    actionmap.insert(Qt::Key_Up, Up);
    actionmap.insert(Qt::Key_Down, Down);
    actionmap.insert(Qt::Key_Right, Right);
    actionmap.insert(Qt::Key_Left, Left);
    setFocus();

    setAndAddStates();
    pacmanfsm.setInitialState("PACMAN_INIT");

//    eatSound.setLoops(2);

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

    prevDir = 4;
    dir = 4;
    whichDot = 0;
    isTimeOut = false;
}

void Player::setTimeOut()
{
    isTimeOut = !isTimeOut;;
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
   painter->drawPixmap(0, 0, pacmanAnim[currentAnim].at(currentFrame%3));
}

QRectF Player::boundingRect() const
{
    return QRectF(0,0,30,30);
}

void Player::setAndAddStates()
{
    State initState("PACMAN_INIT", PACMAN_INIT);
    initState.addEventAndNextState("init_timeout", "PACMAN_PLAY");
    initState.setProperty("steady");
    pacmanfsm.addState(initState);

    State playState("PACMAN_PLAY", PACMAN_PLAY); // creating play state
    playState.addEventAndNextState("ghost_hits_pacman","PACMAN_DYING");
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
            init();
            //this->setPos(xCoord, yCoord);
            pacmanfsm.handleEvent("init_timeout");
        break;

        case PACMAN_PLAY:
            prevDirCol = checkCollWithPrevDir();

            if(xNext != 0 || yNext != 0)
            {
                xdir = xNext;
                ydir = yNext;
                dir = nextDir;
            }
            checkCollWithNextDir(prevDirCol);
            colWithOtherItems();
            if(enemyCollision)
            {
                pacmanfsm.handleEvent("ghost_hits_pacman");
            }
            xCoord += xdir;
            yCoord += ydir;

            changeCurrentAnim();
            enterTunnel();
            keySetFlag = false;
        break;

        case PACMAN_DYING:
            pacmanfsm.handleEvent("dying_timeout");
        break;
    }
    pacmanfsm.update();
    currentFrame++;
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

    QList<QGraphicsItem *> list;
    list = scene()->items(xCoord+10 , yCoord+10, 10,10);
    for(int i = 0; i < list.size(); i++)
    {
        switch(list.at(i)->type())
        {
        case ID_DOT:
            scene()->removeItem(list.at(i));
            //if(eatSound.isFinished())
                eatSound.play();
            whichDot = ID_DOT;
            break;

        case ID_BIGDOT:
            scene()->removeItem(list.at(i));
            eatSound.play();
            whichDot = ID_BIGDOT;
            powerdot = true;
            break;

        case Enemy::ID_ENEMY:
            enemyCollision = true;
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

         switch (a)
         {
             case Up:
                ydir = -step;
                xdir = 0;
                dir = 1;
                break;

             case Down:
                ydir = step;
                xdir = 0;
                dir = 2;
                break;

             case Left:
                xdir = -step;
                ydir = 0;
                dir = 3;
                break;

             case Right:
                xdir = step;
                ydir = 0;
                dir = 4;
                break;

             default:
                xdir = 0;
                ydir = 0;
                dir = 0;
                break;
         }
         keySetFlag = true;

         xNext = xdir; // Storing new keypress values in yNext n xNext
         yNext = ydir;
         nextDir = dir;
         }
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
                     dir = 0;
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

bool Player::eatenPowerDot()
{
    bool pd = powerdot;
    powerdot = false;
    return pd;
}

void Player::changeCurrentAnim()
{
    if(dir == 1)
        currentAnim = UP_ANIM;
    if(dir == 2)
        currentAnim = DOWN_ANIM;
    if(dir == 3)
        currentAnim = LEFT_ANIM;
    if(dir == 4)
        currentAnim = RIGHT_ANIM;
    if(dir == 0)
        currentFrame = 0;
}

void Player::loadAnimations()
{
    QString path = QString("/Users/usha/Documents/workspace/pacman/ cs340-pacman/images/pacman/pacman*.png");
    AnimatedSprites *pacmanSprite = new AnimatedSprites(path);

    QList<QPixmap> spriteList= pacmanSprite->getSpriteList();

    for(int i = 0; i < 4; i++)
    {
        pacmanAnim[i] << spriteList[3*i];
        pacmanAnim[i] << spriteList[3*i+1];
        pacmanAnim[i] << spriteList[3*i+2];
    }
}



