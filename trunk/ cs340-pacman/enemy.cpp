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
   painter->setBrush(Qt::Dense7Pattern);
   painter->fillRect(0,0,
                     Character::X_WIDTH*Character::CHARACTER_WIDTH,
                     Character::Y_HEIGHT*Character::CHARACTER_HEIGHT,
                     Qt::red);

   painter->setPen (Qt::yellow);

    switch (getDirection()) {
        case DIR_UP :
            painter->fillRect(0,0,
                     Character::X_WIDTH*Character::CHARACTER_WIDTH,
                     Character::Y_HEIGHT*Character::CHARACTER_HEIGHT/5,
                     Qt::yellow);
            break;
        case DIR_DOWN :
            painter->fillRect(0,Character::Y_HEIGHT*Character::CHARACTER_HEIGHT - Character::Y_HEIGHT*Character::CHARACTER_HEIGHT/5,
                     Character::X_WIDTH*Character::CHARACTER_WIDTH,
                     Character::Y_HEIGHT*Character::CHARACTER_HEIGHT/5,
                     Qt::yellow);
            break;
        case DIR_RIGHT :
            painter->fillRect(Character::X_WIDTH*Character::CHARACTER_WIDTH-Character::X_WIDTH*Character::CHARACTER_WIDTH/5,0,
                     Character::X_WIDTH*Character::CHARACTER_WIDTH/5,
                     Character::Y_HEIGHT*Character::CHARACTER_HEIGHT,
                     Qt::yellow);
            break;
        case DIR_LEFT :
            painter->fillRect(0,0,
                     Character::X_WIDTH*Character::CHARACTER_WIDTH/5,
                     Character::Y_HEIGHT*Character::CHARACTER_HEIGHT,
                     Qt::yellow);
            break;
    }


}

void Enemy::update() {

//    if (!step)
//    return;

    QList<int> optionsList;
    float rand_max = RAND_MAX + 1.0;
    long selectedOption = 2;

    switch (fsm.getStateIndex()) {

        case INIT_STATE: // set the graphics item position
                         //setPos(this->xCoor*CHARACTER_WIDTH,this->yCoor*CHARACTER_HEIGHT);
                         fsm.handleEvent("init_timeout");
                         fsm.update();
                         break;
        case PLAY_STATE:

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
        case DYING_STATE:
                         break;
    }
 }

bool Enemy::isWallPresent(int direction)
{
    bool ret = false;
    int x = this->xCoor;
    int y = this->yCoor;
    
    QList<CoordChar> wallPositions;
    CoordChar wallCoord, wallCoord1, wallCoord2, wallCoord3;

    switch (direction)
    {
        case TURN_FRONT:
                    switch (this->direction) {
                        case Character::DIR_UP : y -=1;
                            break;
                        case Character::DIR_DOWN : y += Y_HEIGHT;
                            break;
                        case Character::DIR_RIGHT : x +=X_WIDTH;
                            break;
                        case Character::DIR_LEFT : x -= 1;
                            break;
                        }

                        wallCoord.xcoord = x;
                        wallCoord.ycoord = y;

                        wallPositions.append(wallCoord);
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
   int vicinity = 10;
   QList<QGraphicsItem *> list = scene()->items(
                    (xCoor-vicinity)*CHARACTER_WIDTH,
                    (yCoor-vicinity)*CHARACTER_HEIGHT,
                    vicinity*2*CHARACTER_WIDTH,
                    vicinity*2*CHARACTER_HEIGHT);

   QList<QGraphicsItem *>::iterator it;
   for (it = list.begin(); it != list.end(); it++ )
   {
       if ((*it)->type() == Player::ID_PLAYER) {
//           qDebug() << "Found Player in Vicinity at " << (*it)->pos();
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

void Enemy::setAndAddStates()
{
    State initState(INIT, INIT_STATE); // creating init state
    State randomState(PLAY, PLAY_STATE); // creating play state
    State dyingState(DYING, DYING_STATE); // creating dying state

    initState.addEventAndNextState("init_timeout", PLAY);
    randomState.addEventAndNextState("super_player", DYING);
    dyingState.addEventAndNextState("dead" , INIT);

    fsm.addState(initState);
    fsm.addState(randomState);
    fsm.addState(dyingState);
}
