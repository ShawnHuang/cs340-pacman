/*****************************************************
  File Name: wall.h
  Created by: Riddhi Kapasi
 ******************************************************/

#ifndef WALL_H
#define WALL_H

#include <QGraphicsItem>

#define WIDTH  10
#define HEIGHT 10
#define ID_WALL 0


class Wall : public QGraphicsItem //Class Wall
{
public:
    virtual int type() const;
    Wall();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

private:
    QColor color;
    QColor pencolor;
};

#endif // WALL_H
