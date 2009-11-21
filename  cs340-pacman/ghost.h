#ifndef GHOST_H
#define GHOST_H


#include <QPainter>
#include <QtGui>
#include <QPixMap>
#include <QGraphicsItem>
class ghost : public QGraphicsItem
{
public:

    //QGraphicsItem pacman;
    QPixmap ghost;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);


};


#endif // GHOST_H
