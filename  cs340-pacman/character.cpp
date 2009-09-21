/**************************
File Name : Character.cpp
Created By : Usha Sanaga
Description : Abstarct Class from which the player and the enemy classes derived
***************************/



#include "character.h"


Character::Character(int x, int y, int dir) {
    this->xCoor = x;
    this->yCoor = y;
    this->direction = dir;

    // set the graphics item position
    this->setPos(this->xCoor*CHARACTER_WIDTH,this->yCoor*CHARACTER_HEIGHT);
}

int Character::getX() {
    return xCoor;
}

int Character::getY() {
    return yCoor;
}

void Character::moveForward() {
    switch (direction) {
        case DIR_UP : yCoor -= Y_HEIGHT;
            break;
        case DIR_DOWN : yCoor += Y_HEIGHT;
            break;
        case DIR_RIGHT : xCoor += X_WIDTH;
            break;
        case DIR_LEFT : xCoor -= X_WIDTH;
            break;
    }

    // update the graphics item position
    this->setPos(this->xCoor*CHARACTER_WIDTH,this->yCoor*CHARACTER_HEIGHT);
}

QRectF Character::boundingRect() const
{
    return QRectF(-X_WIDTH*CHARACTER_WIDTH,-Y_HEIGHT*CHARACTER_HEIGHT,
                  X_WIDTH*CHARACTER_WIDTH, Y_HEIGHT*CHARACTER_HEIGHT);
}



