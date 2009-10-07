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

int Character::getDirection() {
    return direction;
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

void Character::makeTurn(long turnDir) {

    switch (direction) {
        case DIR_UP :
            if (turnDir = RIGHT) {
                direction = DIR_RIGHT;
            } else {
                    direction = DIR_LEFT;
            }
            break;
        case DIR_DOWN : 
            if (turnDir = RIGHT) {
                direction = DIR_LEFT;
            } else {
                    direction = DIR_RIGHT;
                }
            break;
        case DIR_RIGHT : if (turnDir = RIGHT) {
                direction = DIR_DOWN;
            }
                else
                    direction = DIR_UP;
            break;
        case DIR_LEFT : if (turnDir = RIGHT) {
                direction = DIR_UP;
            }
                else
                    direction = DIR_DOWN;
                break;
    }
}

QRectF Character::boundingRect() const
{
    return QRectF(-X_WIDTH*CHARACTER_WIDTH,-Y_HEIGHT*CHARACTER_HEIGHT,
                  X_WIDTH*CHARACTER_WIDTH, Y_HEIGHT*CHARACTER_HEIGHT);
}



