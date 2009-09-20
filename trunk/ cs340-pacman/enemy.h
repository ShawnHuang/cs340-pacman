#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"

class Enemy : public Character {
    public:
        Enemy(int, int,int);
    public:
    int getType();
};

#endif // ENEMY_H
