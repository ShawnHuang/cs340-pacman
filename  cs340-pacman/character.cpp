#include "character.h"


Character::Character(int x, int y, int dir) {
    this->xCoor = x;
    this->yCoor = y;
    this->direction = dir;
}

int Character::getX() {
    return xCoor;
}

int Character::getY() {
    return yCoor;
}

void Character::moveForward() {
    switch (direction) {
        case DIR_UP : yCoor--;
            break;
        case DIR_DOWN : yCoor++;
            break;
        case DIR_RIGHT : xCoor++;
            break;
        case DIR_LEFT : xCoor--;
            break;
    }
}

