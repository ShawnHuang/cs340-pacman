/*****************************************************
  File Name: wall.cpp
  Description: Creates, loads the scene and add items
  Created by: Riddhi Kapasi
  Modified by :
******************************************************/

#include "wall.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

//Constructor defining wall color as blue
Wall::Wall()
{
    color = QColor(0,0,255,255);
    pencolor = QColor(0,0,0,0);
}

int Wall::type() const
{
    return ID_WALL;
}

//Making bouding rect arnd wall which will aid in collision detection
QRectF Wall::boundingRect() const
{
    return QRectF(0,0,WIDTH,HEIGHT);
}

//Drawing a rectangle of dimensions (WIDTH, HEIGHT)
void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{   
   //painter->setBrush(scene()->collidingItems(this).isEmpty() ? color : Qt::red);
   painter->setBrush(color);
   painter->setPen (pencolor);
   painter->drawRect(0,0, WIDTH, HEIGHT);

}



