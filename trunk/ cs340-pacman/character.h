#ifndef CHARACTER_H
#define CHARACTER_H

class Character
{
private:
    int xCoor;
    int yCoor;
public:
    Character(int,int);
    static const int TYPE_PLAYER =  1;
    static const int TYPE_ENEMY = 2;
    int getX();
    int getY();
    virtual int getType() const = 0;
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
};



#endif // CHARACTER_H
