/*****************************
  Fiel Name : enemy.cpp
  Created By : Usha Sanaga
  Description : Created a garphical representation of enemy
  ****************************/

#include "enemy.h"


Enemy::Enemy(int x,int y, int dir, MapLoader *ml) : Character::Character(x,y,dir)
{
    this->ml = ml;

    // set the graphics item position
    setPos(this->xCoor*CHARACTER_WIDTH,this->yCoor*CHARACTER_HEIGHT);

    setAndAddStates();
    fsm.setInitialState("INIT");
}

 int Enemy::getType() const {
    return TYPE_ENEMY;
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
   painter->setBrush(Qt::Dense7Pattern);
   painter->setPen (Qt::yellow);
   painter->fillRect(0,0,
                     Character::X_WIDTH*Character::CHARACTER_WIDTH,
                     Character::Y_HEIGHT*Character::CHARACTER_HEIGHT,
                     Qt::red);
}

void Enemy::advance(int step) {

    if (!step)
    return;

//    switch (fsm.getState()) {
//
//        case "INIT": fsm.handleEvent("init_timeout");
//                     fsm.update();
//                     break;
//
//    }

    //get the position of the block infront of the enemy
    int x = this->xCoor;
    int y = this->yCoor;

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


    //using key
    QString *key = new QString(QChar(x+48));
    key->append(QChar('_')).append(QChar(y+48));

    //get the wall coordinates
    QMap<QString, CoordChar>::const_iterator i = ml->map.find(*key);

    if(i == ml->map.end()) { //thr is no wall in front of the enemy
        moveForward();

    }else {
        //make a random turn
         float rand_max = RAND_MAX + 1.0;
        long turnDir = lround((qrand()/rand_max)*2);
         this->makeTurn(turnDir);

    }
 }

void Enemy::setAndAddStates()
{
    State initState("INIT", 0); // creating init state
    State randomState("RANDOM", 1); // creating random play state
    State followState("FOLLOW", 2); // creating follow play state
    State dyingState("DYING", 3); // creating a dying state

    initState.addEventAndNextState("init_timeout", "RANDOM_PLAY");

    randomState.addEventAndNextState("follow_pacman","FOLLOW_PLAY");
    randomState.addEventAndNextState("super_player","DYING");

    followState.addEventAndNextState("randomize","RANDOM");
    followState.addEventAndNextState("super_player","DYING");

    dyingState.addEventAndNextState("dead" , "INIT");

    fsm.addState(initState);
    fsm.addState(randomState);
    fsm.addState(followState);
    fsm.addState(dyingState);
}
