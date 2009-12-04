/*****************************
  Fiel Name : enemy.cpp
  Created and Modified By : Usha Sanaga
 *****************************/

#include "enemy.h"

Enemy::Enemy(int x,int y, int dir, MapLoader *ml) : Character(x, y, dir)
{
    INIT = "INIT";
    PLAY = "PLAY";
    DYING = "DYING";
    ZOMBIE = "ZOMBIE";
    DEAD = "DEAD";

    initX = x;
    initY = y;

    this->ml = ml;

    setAndAddStates();
    fsm.setInitialState(INIT);

    spritesImage = new QPixmap("../images/sprites.png");

    myId = ENEMY_COUNT++;
    move = true;
    SUPER_PLAYER_TIME = QTime();

    if (!GO_INIT.contains(myId)) {
        GO_INIT.append(myId);
    }
}

int Enemy::getType() const {
    return TYPE_ENEMY;
}

int Enemy::type() const
{
    return ID_ENEMY;
}

// Obtaining different cloured images and updating the different images in different states

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    int width = CHARACTER_WIDTH*X_WIDTH;
    int height = CHARACTER_HEIGHT*Y_HEIGHT;

    int x = 96 + (myId*(width+2)*2);
    x+= (move) ? 0 : (width+2);

    switch (fsm.getStateIndex()) {
        case INIT_STATE:
        case PLAY_STATE:
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
            break;

       case DYING_STATE:
                x = 96 + (5*(width+2)*2);
                x+= (move) ? 0 : (width+2);
                painter->drawPixmap(0, 0, *spritesImage, x, 0, width, height);
            break;

       case ZOMBIE_STATE:
                x = 96 + (5*(width+2)*2);
                x+= (move) ? 0 : (width+2);
                painter->drawPixmap(0, 0, *spritesImage, x, 30, width, height);
            break;

       case DEAD_STATE:
                x = 96 + (4*(width+2)*2);

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
            break;
        }
    }

    if (move)
        move = false;
    else
        move = true;
}

// Accesses difefrent states of Enemy

void Enemy::update() {
    QList<int> optionsList;
    float rand_max = RAND_MAX + 1.0;
    long selectedOption = 2;

   if (GO_INIT.contains(myId) && fsm.getStateIndex() != INIT_STATE) {
        fsm.handleEvent("init");
        fsm.update();
    }


    switch (fsm.getStateIndex()) {

        case INIT_STATE:
                         xCoor = initX;
                         yCoor = initY;
                         fsm.handleEvent("init_timeout");
                         fsm.update();
                         GO_INIT.removeOne(myId);
                         break;
        case PLAY_STATE:
        case DYING_STATE:
        case ZOMBIE_STATE:
                         dyingCheck();

                         // appending hard coded values to the options list

                         if (!isWallPresent(TURN_FRONT)) {
                             optionsList.append(0);
                         }

                         if (!isWallPresent(TURN_LEFT)) {
                             optionsList.append(-1);
                         }

                         if (!isWallPresent(TURN_RIGHT)) {
                             optionsList.append(1);
                         }

                        if (fsm.getStateIndex() == PLAY_STATE) {
                         removeOddOption(&optionsList);
                        }

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
         case DEAD_STATE:
                         xCoor = initX;
                         yCoor = initY;
                         if(deadTime.elapsed() >= DEAD_TIMEOUT) {
                             fsm.handleEvent("dead_timeout");
                             fsm.update();
                         }
    }

    //playSound();
 }

// Playing different Sounds at different states of Enemy

void Enemy::playSound() {
    switch (fsm.getStateIndex()) {
        case INIT_STATE:
        case PLAY_STATE:
            if (moveSound.isFinished()) {
                moveSound.setLoops(20);
                moveSound.play();
            }
            break;
        case DYING_STATE:
            if (blueSound.isFinished()) {
                blueSound.setLoops(2);
                blueSound.play();
            }
            break;
        case ZOMBIE_STATE:
            if (whiteSound.isFinished()) {
                whiteSound.setLoops(2);
                whiteSound.play();
            }
            break;
        case DEAD_STATE:
            deadSound.play();
            break;
    }

}

bool Enemy::isWallPresent(int turnDir)
{
    bool ret = false;
    int x = round(this->xCoor*((double)CHARACTER_WIDTH));
    int y = round(this->yCoor*((double)CHARACTER_HEIGHT));

    // soft wall check to make enemy come out of lair easily
    if (!(turnDir == TURN_FRONT && direction == DIR_UP)
        && (x > 260 &&  x < 280)
        && (y > 200 && y <= 240)) {
        ret = true;
    }

    //Checking for wall Coordinates at front,right,and left positions of enemy in different directions

    QList<CoordChar> wallPositions;
    CoordChar wallCoord1, wallCoord2, wallCoord3, wallCoord4;

    switch (turnDir)
    {
        case TURN_FRONT:
                  switch (this->direction) {
                        case Character::DIR_UP :
                            if (((int)y%CHARACTER_HEIGHT > 0 && ((int)(y%CHARACTER_HEIGHT - (int)(CHARACTER_HEIGHT*POSITION_OFFSET)) < 0))
                                || ((int)y%CHARACTER_HEIGHT == 0)) {
                                y -= CHARACTER_HEIGHT;
                            }
                            wallCoord1.ycoord = wallCoord2.ycoord = wallCoord3.ycoord = y;
                            wallCoord1.xcoord = x;
                            wallCoord2.xcoord = x + CHARACTER_WIDTH;
                            wallCoord3.xcoord = x + 2*CHARACTER_WIDTH;

                            if ((int)x%CHARACTER_WIDTH > 0) {
                                wallCoord4.xcoord = x + 3*CHARACTER_WIDTH;
                                wallCoord4.ycoord = y;
                                wallPositions.append(wallCoord4);
                            }

                            break;
                        case Character::DIR_DOWN :
                            if ((y%CHARACTER_HEIGHT > 0 && ((int)(y%CHARACTER_HEIGHT + (CHARACTER_HEIGHT*POSITION_OFFSET)) > CHARACTER_HEIGHT))
                                || ((int)y%CHARACTER_HEIGHT == 0)) {
                                y += Y_HEIGHT*CHARACTER_HEIGHT;
                            }
                            wallCoord1.ycoord = wallCoord2.ycoord = wallCoord3.ycoord = y;
                            wallCoord1.xcoord = x;
                            wallCoord2.xcoord = x + CHARACTER_WIDTH;
                            wallCoord3.xcoord = x + 2*CHARACTER_WIDTH;

                            if ((int)x%CHARACTER_WIDTH > 0) {
                                wallCoord4.xcoord = x + 3*CHARACTER_WIDTH;
                                wallCoord4.ycoord = y;
                                wallPositions.append(wallCoord4);
                            }

                            break;
                        case Character::DIR_RIGHT :
                            if ((x%CHARACTER_WIDTH > 0 && ((int)(x%CHARACTER_WIDTH + CHARACTER_WIDTH*POSITION_OFFSET) > CHARACTER_WIDTH))
                                || ((int)x%CHARACTER_WIDTH == 0)) {
                                x += X_WIDTH*CHARACTER_WIDTH;
                            }
                            wallCoord1.xcoord = wallCoord2.xcoord = wallCoord3.xcoord = x;
                            wallCoord1.ycoord = y;
                            wallCoord2.ycoord = y+CHARACTER_HEIGHT;
                            wallCoord3.ycoord = y+2*CHARACTER_HEIGHT;

                            if ((int)y%CHARACTER_HEIGHT > 0) {
                                wallCoord4.xcoord = x;
                                wallCoord4.ycoord = y + 3*CHARACTER_HEIGHT;
                                wallPositions.append(wallCoord4);
                            }

                            break;
                        case Character::DIR_LEFT :
                            if (((int)x%CHARACTER_WIDTH > 0 && ((int)(x%CHARACTER_WIDTH - CHARACTER_WIDTH*POSITION_OFFSET) < 0))
                                || ((int)x%CHARACTER_WIDTH == 0)) {
                                x -= CHARACTER_WIDTH;
                            }
                            wallCoord1.xcoord = wallCoord2.xcoord = wallCoord3.xcoord = x;
                            wallCoord1.ycoord = y;
                            wallCoord2.ycoord = y+CHARACTER_HEIGHT;
                            wallCoord3.ycoord = y+2*CHARACTER_HEIGHT;

                            if ((int)y%CHARACTER_HEIGHT > 0) {
                                wallCoord4.xcoord = x;
                                wallCoord4.ycoord = y + 3*CHARACTER_HEIGHT;
                                wallPositions.append(wallCoord4);
                            }
                            break;
                        }

                        wallPositions.append(wallCoord1);
                        wallPositions.append(wallCoord2);
                        wallPositions.append(wallCoord3);

                        break;
        case TURN_RIGHT:
                    switch (this->direction) {
                        case Character::DIR_UP : x += X_WIDTH*CHARACTER_WIDTH;
                            wallCoord1.xcoord = wallCoord2.xcoord = wallCoord3.xcoord = x;
                            wallCoord1.ycoord = y;
                            wallCoord2.ycoord = y + CHARACTER_HEIGHT;
                            wallCoord3.ycoord = y + 2*CHARACTER_HEIGHT;

                            // offset compensation required as walls are block level
                            // while enemy can be made to move at pixel level
                            // if enemy is at y = 20.8 block then he needs to
                            // check for 4 walls in vertical direction
                            if (y%CHARACTER_HEIGHT > 0) {
                                wallCoord4.xcoord = x;
                                wallCoord4.ycoord = y + 3*CHARACTER_HEIGHT;
                                wallPositions.append(wallCoord4);
                            }

                            break;
                        case Character::DIR_DOWN : x -= CHARACTER_WIDTH;
                            wallCoord1.xcoord = wallCoord2.xcoord = wallCoord3.xcoord = x;
                            wallCoord1.ycoord = y;
                            wallCoord2.ycoord = y + CHARACTER_HEIGHT;
                            wallCoord3.ycoord = y + 2*CHARACTER_HEIGHT;

                            if (y%CHARACTER_HEIGHT > 0) {
                                wallCoord4.xcoord = x;
                                wallCoord4.ycoord = y + 3*CHARACTER_HEIGHT;
                                wallPositions.append(wallCoord4);
                            }

                            break;
                        case Character::DIR_RIGHT : y += Y_HEIGHT*CHARACTER_HEIGHT;
                            wallCoord1.ycoord = wallCoord2.ycoord = wallCoord3.ycoord = y;
                            wallCoord1.xcoord = x;
                            wallCoord2.xcoord = x+CHARACTER_WIDTH;
                            wallCoord3.xcoord = x+2*CHARACTER_WIDTH;

                            if (x%CHARACTER_WIDTH > 0) {
                                wallCoord4.xcoord = x + 3*CHARACTER_WIDTH;
                                wallCoord4.ycoord = y;
                                wallPositions.append(wallCoord4);
                            }

                            break;
                        case Character::DIR_LEFT : y -= CHARACTER_HEIGHT;
                            wallCoord1.ycoord = wallCoord2.ycoord = wallCoord3.ycoord = y;
                            wallCoord1.xcoord = x;
                            wallCoord2.xcoord = x+CHARACTER_WIDTH;
                            wallCoord3.xcoord = x+2*CHARACTER_WIDTH;

                            if (x%CHARACTER_WIDTH > 0) {
                                wallCoord4.xcoord = x + 3*CHARACTER_WIDTH;
                                wallCoord4.ycoord = y;
                                wallPositions.append(wallCoord4);
                            }

                            break;
                        }

                        wallPositions.append(wallCoord1);
                        wallPositions.append(wallCoord2);
                        wallPositions.append(wallCoord3);
                        break;
        case TURN_LEFT:
                    switch (this->direction) {
                        case Character::DIR_UP : x -=CHARACTER_WIDTH;
                            wallCoord1.xcoord = wallCoord2.xcoord = wallCoord3.xcoord = x;
                            wallCoord1.ycoord = y;
                            wallCoord2.ycoord = y + CHARACTER_HEIGHT;
                            wallCoord3.ycoord = y + 2*CHARACTER_HEIGHT;

                            if (y%CHARACTER_HEIGHT > 0) {
                                wallCoord4.xcoord = x;
                                wallCoord4.ycoord = y + 3*CHARACTER_HEIGHT;
                                wallPositions.append(wallCoord4);
                            }

                            break;
                        case Character::DIR_DOWN : x += X_WIDTH*CHARACTER_WIDTH;
                            wallCoord1.xcoord = wallCoord2.xcoord = wallCoord3.xcoord = x;
                            wallCoord1.ycoord = y;
                            wallCoord2.ycoord = y + CHARACTER_HEIGHT;
                            wallCoord3.ycoord = y + 2*CHARACTER_HEIGHT;

                            if (y%CHARACTER_HEIGHT > 0) {
                                wallCoord4.xcoord = x;
                                wallCoord4.ycoord = y + 3*CHARACTER_HEIGHT;
                                wallPositions.append(wallCoord4);
                            }
                            break;
                        case Character::DIR_RIGHT : y -= CHARACTER_HEIGHT;
                            wallCoord1.ycoord = wallCoord2.ycoord = wallCoord3.ycoord = y;
                            wallCoord1.xcoord = x;
                            wallCoord2.xcoord = x+CHARACTER_WIDTH;
                            wallCoord3.xcoord = x+2*CHARACTER_WIDTH;

                            if (x%CHARACTER_WIDTH > 0) {
                                wallCoord4.xcoord = x + 3*CHARACTER_WIDTH;
                                wallCoord4.ycoord = y;
                                wallPositions.append(wallCoord4);
                            }

                            break;
                        case Character::DIR_LEFT : y += Y_HEIGHT*CHARACTER_HEIGHT;
                            wallCoord1.ycoord = wallCoord2.ycoord = wallCoord3.ycoord = y;
                            wallCoord1.xcoord = x;
                            wallCoord2.xcoord = x+CHARACTER_WIDTH;
                            wallCoord3.xcoord = x+2*CHARACTER_WIDTH;

                            if (x%CHARACTER_WIDTH > 0) {
                                wallCoord4.xcoord = x + 3*CHARACTER_WIDTH;
                                wallCoord4.ycoord = y;
                                wallPositions.append(wallCoord4);
                            }

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
        int x = (*i).xcoord / CHARACTER_WIDTH;
        int y = (*i).ycoord / CHARACTER_HEIGHT;
        QString key = QString::number(x).append(QChar('_')).append(QString::number(y));

        QMap<QString, CoordChar>::const_iterator wall = ml->map.find(key);
        ret |= !(wall == ml->map.end());
     }

     return ret;
}

//At every instance eliminating the odd options to reach the player position

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
   if(SUPER_PLAYER_TIME.isValid() && SUPER_PLAYER_TIME.elapsed() < DYING_STATE_LIMIT) {
       fsm.handleEvent("super_player");
       fsm.update();
   } else if(SUPER_PLAYER_TIME.isValid() && (SUPER_PLAYER_TIME.elapsed() - DYING_STATE_LIMIT) < ZOMBIE_STATE_LIMIT ) {
       fsm.handleEvent("average_player");
       fsm.update();
   } else {
       fsm.handleEvent("normal_player");
       fsm.update();
   }
}

void Enemy::superPlayer()
{
    SUPER_PLAYER_TIME = QTime::currentTime();
    SUPER_PLAYER_TIME.start();
}

void Enemy::setAndAddStates()
{
    // Creating States

    State initState(INIT, INIT_STATE);
    State playState(PLAY, PLAY_STATE);
    State dyingState(DYING, DYING_STATE);
    State zombieState(ZOMBIE, ZOMBIE_STATE);
    State deadState(DEAD, DEAD_STATE);

    //Adding events and next state when that event takes place

    initState.addEventAndNextState("init_timeout", PLAY);

    playState.addEventAndNextState("super_player", DYING);
    playState.addEventAndNextState("normal_player", PLAY);
    playState.addEventAndNextState("average_player", ZOMBIE);
    playState.addEventAndNextState("init", INIT);

    dyingState.addEventAndNextState("dead" , INIT);
    dyingState.addEventAndNextState("normal_player" , PLAY);
    dyingState.addEventAndNextState("super_player" , DYING);
    dyingState.addEventAndNextState("average_player", ZOMBIE);
    dyingState.addEventAndNextState("enemy_killed", DEAD);
    dyingState.addEventAndNextState("init" , INIT);

    zombieState.addEventAndNextState("dead" , INIT);
    zombieState.addEventAndNextState("normal_player" , PLAY);
    zombieState.addEventAndNextState("super_player" , DYING);
    zombieState.addEventAndNextState("average_player", ZOMBIE);
    zombieState.addEventAndNextState("enemy_killed", DEAD);
    zombieState.addEventAndNextState("init" , INIT);

    deadState.addEventAndNextState("dead_timeout", PLAY);
    deadState.addEventAndNextState("normal_player" , DEAD);
    deadState.addEventAndNextState("super_player" , DEAD);
    deadState.addEventAndNextState("average_player", DEAD);
    deadState.addEventAndNextState("enemy_killed", DEAD);
    deadState.addEventAndNextState("init", INIT);

    //Adding all the States to enemy fsm

    fsm.addState(initState);
    fsm.addState(playState);
    fsm.addState(dyingState);
    fsm.addState(zombieState);
    fsm.addState(deadState);
}

void Enemy::resetEnemyCount()
{
    ENEMY_COUNT = 0;
}

void Enemy::killed() {
   if ((fsm.getStateIndex() == DYING_STATE || fsm.getStateIndex() == ZOMBIE_STATE)) {

        fsm.handleEvent("enemy_killed");
        fsm.update();

        deadTime = QTime::currentTime();
        deadTime.start();
    } else {
       GO_INIT.append(0);
       GO_INIT.append(1);
       GO_INIT.append(2);
       GO_INIT.append(3);
    }
}
