#ifndef CHARACTER_H
#define CHARACTER_H

class Character
{
private:
    int xCoor;
    int yCoor;
    int direction;
public:
    Character(int,int,int);
    static const int TYPE_PLAYER =  1;
    static const int TYPE_ENEMY = 2;
    static const int DIR_UP = 1;
    static const int DIR_DOWN = 2;
    static const int DIR_RIGHT = 3;
    static const int DIR_LEFT = 4;
    int getX();
    int getY();
    virtual int getType() const = 0;
    void moveForward();
};



#endif // CHARACTER_H
