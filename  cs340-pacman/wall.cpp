/*****************************************************
  File Name: main.cpp
  Description: Creates, loads the scene and add items
  Created by: Riddhi Kapasi
  Modified by:
******************************************************/

#include "wall.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

//Constructor defining wall color as blue
Wall::Wall()
{
    color = QColor(170,100,150,255);
}

//Making bouding rect arnd wall which will aid in collision detection
QRectF Wall::boundingRect() const
{
    return QRectF(-WIDTH/2,-HEIGHT/2,WIDTH,HEIGHT);
}

//Drawing a rectangle of dimensions (WIDTH, HEIGHT)
void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
   painter->setBrush(color);
   painter->drawRect(0,0, WIDTH, HEIGHT);

}



