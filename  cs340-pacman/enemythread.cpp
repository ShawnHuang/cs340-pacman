#include "enemythread.h"
#include <math.h>
#include "character.h"
#include <stdlib.h>


using namespace std;

EnemyThread::EnemyThread(MapLoader *ml)
{
    this->ml = ml;
    this->e = new Enemy(0,0,Character::DIR_UP);

}

void EnemyThread ::run() {
    //get the position of the enemy
    int xCoord = e->getX();
    int yCoord = e->getY();

    //get the position of the block infront of the enemy
    switch (e->getDirection()) {
        case Character::DIR_UP : yCoord -= Character::Y_HEIGHT;
            break;
        case Character::DIR_DOWN : yCoord += Character::Y_HEIGHT;
            break;
        case Character::DIR_RIGHT : xCoord += Character::X_WIDTH;
            break;
        case Character::DIR_LEFT : xCoord -= Character::X_WIDTH;
            break;
    }

    //using key
    QString *key = new QString(QChar(xCoord + 48));
    key->append(QChar('_')).append(QChar(yCoord + 48));

    //get the wall coordinates
    QMap<QString, CoordChar>::const_iterator i = ml->map.find(*key);

    if(i == ml->map.end()) { //thr is no wall in front of the enemy
        e->moveForward();
        } else {
        //make a random turn
        long range = lround((qrand()/RAND_MAX)*2);
        e->makeTurn(range);
        }
    }

