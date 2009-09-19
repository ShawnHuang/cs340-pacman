/*****************************************************
  File Name: wall.h
  Created by: Riddhi Kapasi
 ******************************************************/

#ifndef WALL_H
#define WALL_H

#include <QGraphicsItem>

#define WIDTH  20
#define HEIGHT 20

class Wall : public QGraphicsItem //Class Wall
{
public:
    Wall();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

private:
    QColor color;
};

#endif // WALL_H
