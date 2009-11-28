/*****************************
  Fiel Name : enemy.cpp
  Created By : Usha Sanaga
  Description : Created a garphical representation of enemy
  ****************************/

#include "enemy.h"

Enemy::Enemy(int x,int y, int dir, MapLoader *ml) : Character(x, y, dir)
{
    INIT = "INIT";
    PLAY = "PLAY";
    DYING = "DYING";

    this->ml = ml;

    setAndAddStates();
    fsm.setInitialState(INIT);

    spritesImage = new QPixmap("../images/sprites.png");

    myId = ENEMY_COUNT++;
    move = true;
}

int Enemy::getType() const {
    return TYPE_ENEMY;
}

int Enemy::type() const
{
    return ID_ENEMY;
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    int width = CHARACTER_WIDTH*X_WIDTH;
    int height = CHARACTER_HEIGHT*Y_HEIGHT;

    int x = 100 + (myId*(width+2)*2);
    x+= (move) ? 0 : (width+2);

    if (move)
        move = false;
    else
        move = true;

    switch (getDirection()) {
        case DIR_UP :
            painter->drawPixmap(0, 0, *spritesImage, x, 65, width, height);
            break;
        case DIR_DOWN :
            painter->drawPixmap(0, 0, *spritesImage, x, 30, width, height);
            break;
        case DIR_RIGHT :
            painter->drawPixmap(0, 0, *spritesImage, x, 0, width, height);
            break;
        case DIR_LEFT :
            painter->drawPixmap(0, 0, *spritesImage, x, 95, width, height);
            break;
    }
}

void Enemy::update() {
    QList<int> optionsList;
    float rand_max = RAND_MAX + 1.0;
    long selectedOption = 2;

    switch (fsm.getStateIndex()) {

        case INIT_STATE: fsm.handleEvent("init_timeout");
                         fsm.update();
                         break;
        case PLAY_STATE:
        case DYING_STATE:
                         // appending hard coded values to the options list
                         // TODO: Remove hardcoding if possible
                         if (!isWallPresent(TURN_FRONT)) {
                             optionsList.append(0);
                         }

                         if (!isWallPresent(TURN_LEFT)) {
                             optionsList.append(-1);
                         }

                         if (!isWallPresent(TURN_RIGHT)) {
                             optionsList.append(1);
                         }

                        removeOddOption(&optionsList);

                         // if no options present that means there are walls on
                         // all three sides and we might need to turn back
                         // that can be achieved by turning in either left or right
                         if (optionsList.size() == 0) {
                            optionsList.append(1);
                            optionsList.append(-1);
                         }

                         selectedOption = optionsList.at(lround((qrand()/rand_max)*(optionsList.size()-1)));

                         if (selectedOption == TURN_FRONT) {
                             moveForward();
                         } else {
                             makeTurn(selectedOption);
                         }

                         break;
    }

 }

bool Enemy::isWallPresent(int turnDir)
{
    bool ret = false;
    int x = this->xCoor;
    int y = this->yCoor;

//    qDebug() << "Coor: " << xCoor << " " << yCoor;

    QList<CoordChar> wallPositions;
    CoordChar wallCoord1, wallCoord2, wallCoord3;

    switch (turnDir)
    {
        case TURN_FRONT:
                        if ((int)(this->xCoor * CHARACTER_WIDTH) % CHARACTER_WIDTH > 5
                            ) {
                            x++;
                        }
                        if ((int)(this->yCoor * CHARACTER_HEIGHT) % CHARACTER_HEIGHT >= 5
                            ) {
                            y++;
                        }
                        switch (this->direction) {
                        case Character::DIR_UP : y -= 1;
                            wallCoord1.ycoord = wallCoord2.ycoord = wallCoord3.ycoord = y;
                            wallCoord1.xcoord = x;
                            wallCoord2.xcoord = x + 1;
                            wallCoord3.xcoord = x + 2;
                            break;
                        case Character::DIR_DOWN : y += Y_HEIGHT;
                            wallCoord1.ycoord = wallCoord2.ycoord = wallCoord3.ycoord = y;
                            wallCoord1.xcoord = x;
                            wallCoord2.xcoord = x + 1;
                            wallCoord3.xcoord = x + 2;
                            break;
                        case Character::DIR_RIGHT : x += X_WIDTH;
                            wallCoord1.xcoord = wallCoord2.xcoord = wallCoord3.xcoord = x;
                            wallCoord1.ycoord = y;
                            wallCoord2.ycoord = y+1;
                            wallCoord3.ycoord = y+2;
                            break;
                        case Character::DIR_LEFT : x -= 1;
                            wallCoord1.xcoord = wallCoord2.xcoord = wallCoord3.xcoord = x;
                            wallCoord1.ycoord = y;
                            wallCoord2.ycoord = y+1;
                            wallCoord3.ycoord = y+2;
                            break;
                        }

                        wallPositions.append(wallCoord1);
                        wallPositions.append(wallCoord2);
                        wallPositions.append(wallCoord3);

                        break;
        case TURN_RIGHT:
                    switch (this->direction) {
                        case Character::DIR_UP : x += X_WIDTH;
                            wallCoord1.xcoord = wallCoord2.xcoord = wallCoord3.xcoord = x;
                            wallCoord1.ycoord = y;
                            wallCoord2.ycoord = y + 1;
                            wallCoord3.ycoord = y + 2;
                            break;
                        case Character::DIR_DOWN : x -= 1;
                            wallCoord1.xcoord = wallCoord2.xcoord = wallCoord3.xcoord = x;
                            wallCoord1.ycoord = y;
                            wallCoord2.ycoord = y + 1;
                            wallCoord3.ycoord = y + 2;
                            break;
                        case Character::DIR_RIGHT : y += Y_HEIGHT;
                            wallCoord1.ycoord = wallCoord2.ycoord = wallCoord3.ycoord = y;
                            wallCoord1.xcoord = x;
                            wallCoord2.xcoord = x+1;
                            wallCoord3.xcoord = x+2;
                            break;
                        case Character::DIR_LEFT : y -= 1;
                            wallCoord1.ycoord = wallCoord2.ycoord = wallCoord3.ycoord = y;
                            wallCoord1.xcoord = x;
                            wallCoord2.xcoord = x+1;
                            wallCoord3.xcoord = x+2;
                            break;
                        }

                        wallPositions.append(wallCoord1);
                        wallPositions.append(wallCoord2);
                        wallPositions.append(wallCoord3);
                        break;
        case TURN_LEFT:
                    switch (this->direction) {
                        case Character::DIR_UP : x -=1;
                            wallCoord1.xcoord = wallCoord2.xcoord = wallCoord3.xcoord = x;
                            wallCoord1.ycoord = y;
                            wallCoord2.ycoord = y + 1;
                            wallCoord3.ycoord = y + 2;
                            break;
                        case Character::DIR_DOWN : x += X_WIDTH;
                            wallCoord1.xcoord = wallCoord2.xcoord = wallCoord3.xcoord = x;
                            wallCoord1.ycoord = y;
                            wallCoord2.ycoord = y + 1;
                            wallCoord3.ycoord = y + 2;
                            break;
                        case Character::DIR_RIGHT : y -= 1;
                            wallCoord1.ycoord = wallCoord2.ycoord = wallCoord3.ycoord = y;
                            wallCoord1.xcoord = x;
                            wallCoord2.xcoord = x+1;
                            wallCoord3.xcoord = x+2;
                            break;
                        case Character::DIR_LEFT : y += Y_HEIGHT;
                            wallCoord1.ycoord = wallCoord2.ycoord = wallCoord3.ycoord = y;
                            wallCoord1.xcoord = x;
                            wallCoord2.xcoord = x+1;
                            wallCoord3.xcoord = x+2;
                            break;
                        }

                    wallPositions.append(wallCoord1);
                    wallPositions.append(wallCoord2);
                    wallPositions.append(wallCoord3);
                    break;
        }

     QList<CoordChar>::iterator i;
     for (i = wallPositions.begin(); i != wallPositions.end(); ++i)
     {
        QString *key = new QString(QChar(((*i).xcoord)+48));
        key->append(QChar('_')).append(QChar(((*i).ycoord)+48));

        QMap<QString, CoordChar>::const_iterator wall = ml->map.find(*key);
        ret |= !(wall == ml->map.end());
     }

     return ret;
}

void Enemy::removeOddOption(QList<int> *options)
{
   int vicinity = 15;
   QList<QGraphicsItem *> list = scene()->items(
                    (xCoor-vicinity)*CHARACTER_WIDTH,
                    (yCoor-vicinity)*CHARACTER_HEIGHT,
                    vicinity*2*CHARACTER_WIDTH,
                    vicinity*2*CHARACTER_HEIGHT);

   QList<QGraphicsItem *>::iterator it;
   for (it = list.begin(); it != list.end(); it++ )
   {
       if ((*it)->type() == Player::ID_PLAYER) {
           int playerX = (*it)->x()/CHARACTER_WIDTH;
           int playerY = (*it)->y()/CHARACTER_HEIGHT;

           switch(getDirection())
           {
               case DIR_UP :
                    if (options->contains(0) && playerY > yCoor) {
                        options->removeOne(0);
                    }

                    if (options->contains(1) && playerX < xCoor) {
                        options->removeOne(1);
                    }

                    if (options->contains(-1) && playerX > xCoor) {
                        options->removeOne(-1);
                    }

                    break;
                case DIR_DOWN :
                    if (options->contains(0) && playerY < yCoor) {
                        options->removeOne(0);
                    }

                    if (options->contains(1) && playerX > xCoor) {
                        options->removeOne(1);
                    }

                    if (options->contains(-1) && playerX < xCoor) {
                        options->removeOne(-1);
                    }
                    break;
                case DIR_RIGHT :
                    if (options->contains(0) && playerX < xCoor) {
                        options->removeOne(0);
                    }

                    if (options->contains(1) && playerY < yCoor) {
                        options->removeOne(1);
                    }

                    if (options->contains(-1) && playerY > yCoor) {
                        options->removeOne(-1);
                    }

                    break;
                case DIR_LEFT :
                    if (options->contains(0) && playerX > xCoor) {
                        options->removeOne(0);
                    }

                    if (options->contains(1) && playerY > yCoor) {
                        options->removeOne(1);
                    }

                    if (options->contains(-1) && playerY < yCoor) {
                        options->removeOne(-1);
                    }
                    break;
           }
       }
   }
}

void Enemy::dyingCheck()
{
   QList<QGraphicsItem *> list = scene()->items();

   QList<QGraphicsItem *>::iterator it;
   for (it = list.begin(); it != list.end(); it++ )
   {
       if ((*it)->type() == Player::ID_PLAYER) {
           if (((Player*) *it)->eatenPowerDot()) {
               fsm.handleEvent("super_player");
               fsm.update();
           } else {
               fsm.handleEvent("normal_player");
               fsm.update();
           }
       }
   }
}

void Enemy::setAndAddStates()
{
    State initState(INIT, INIT_STATE); // creating init state
    State randomState(PLAY, PLAY_STATE); // creating play state
    State dyingState(DYING, DYING_STATE); // creating dying state

    initState.addEventAndNextState("init_timeout", PLAY);
    randomState.addEventAndNextState("super_player", DYING);
    randomState.addEventAndNextState("normal_player", PLAY);
    dyingState.addEventAndNextState("dead" , INIT);
    dyingState.addEventAndNextState("normal_player" , PLAY);
    dyingState.addEventAndNextState("super_player" , DYING);

    fsm.addState(initState);
    fsm.addState(randomState);
    fsm.addState(dyingState);
}
