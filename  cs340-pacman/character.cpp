/**************************
File Name : Character.cpp
Created By : Usha Sanaga
Description : Abstarct Class from which the player and the enemy classes derived
***************************/

#include "character.h"

Character::Character()
{
}

Character::Character(int x, int y, int dir)
{
    this->xCoor = x;
    this->yCoor = y;
    this->direction = dir;
}

int Character::getX()
{
    return xCoor;
}

int Character::getY()
{
    return yCoor;
}

int Character::getDirection()
{
    return direction;
}

void Character::moveForward() {
    switch (direction) {

        case DIR_UP : yCoor -= 1;
            break;
        case DIR_DOWN : yCoor += 1;
            break;
        case DIR_RIGHT : xCoor += 1;
            break;
        case DIR_LEFT : xCoor -= 1;
            break;
    }

    if (xCoor < 1) {
        xCoor = 56;
    } else if (xCoor > 56) {
        xCoor = 1;
    }

    // update the graphics item position
    update();
  }

void Character::update()
{
    switch (direction) {
        case DIR_UP :
                setPos(this->xCoor*CHARACTER_WIDTH,this->yCoor*CHARACTER_HEIGHT + CHARACTER_HEIGHT/2);
                break;
        case DIR_DOWN :
                setPos(this->xCoor*CHARACTER_WIDTH,this->yCoor*CHARACTER_HEIGHT - CHARACTER_HEIGHT/2);
                break;
        case DIR_RIGHT :
                setPos(this->xCoor*CHARACTER_WIDTH - CHARACTER_WIDTH/2,this->yCoor*CHARACTER_HEIGHT);
                break;
        case DIR_LEFT :
                setPos(this->xCoor*CHARACTER_WIDTH + CHARACTER_WIDTH/2,this->yCoor*CHARACTER_HEIGHT);
                break;
    }
}

void Character::makeTurn(long turnDir) {

    switch (direction) {
        case DIR_UP :
            if (turnDir == TURN_RIGHT) {
                direction = DIR_RIGHT;
            } else if (turnDir == TURN_LEFT) {
                    direction = DIR_LEFT;
            }
            break;
        case DIR_DOWN : 
            if (turnDir == TURN_RIGHT) {
                direction = DIR_LEFT;
            } else if (turnDir == TURN_LEFT){
                    direction = DIR_RIGHT;
                }
            break;
        case DIR_RIGHT :
            if (turnDir == TURN_RIGHT) {
                direction = DIR_DOWN;
            } else if (turnDir == TURN_LEFT){
                    direction = DIR_UP;
            }
            break;
        case DIR_LEFT : if (turnDir == TURN_RIGHT) {
                direction = DIR_UP;
            } else if (turnDir == TURN_LEFT) {
                    direction = DIR_DOWN;
            }
            break;
    }
    // update the graphics item position
//    setPos(this->xCoor*CHARACTER_WIDTH,this->yCoor*CHARACTER_HEIGHT);
}

QRectF Character::boundingRect() const
{
    return QRectF(0,0,X_WIDTH*CHARACTER_WIDTH, Y_HEIGHT*CHARACTER_HEIGHT);
}
