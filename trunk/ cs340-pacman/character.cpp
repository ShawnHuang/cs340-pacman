#include "character.h"


Character::Character(int x, int y) {
    this->xCoor = x;
    this->yCoor = y;
}

int Character::getX() {
    return xCoor;
}

int Character::getY() {
    return yCoor;
}

void Character::moveUp() {
    yCoor++;
}

void Character::moveDown() {
    yCoor--;
}

void Character::moveRight() {
    xCoor++;
}

void Character::moveLeft() {
    xCoor--;
}

