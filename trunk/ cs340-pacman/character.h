#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsItem>
#include <QPainter>
#include <QRectF>
#include <Qt>

class Character : public QGraphicsItem
{
private:
    int xCoor;
    int yCoor;
    int direction;
protected:
    static const int CHARACTER_WIDTH = 10;
    static const int CHARACTER_HEIGHT = 10;
    static const int X_WIDTH = 3;
    static const int Y_HEIGHT = 3;
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
    QRectF boundingRect() const;
};



#endif // CHARACTER_H
