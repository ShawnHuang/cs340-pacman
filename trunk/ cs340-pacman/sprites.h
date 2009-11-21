#ifndef SPRITES_H
#define SPRITES_H


#include <QPainter>
#include <QtGui>
#include <QPixMap>
#include <QGraphicsItem>
class sprites : public QGraphicsItem
{
public:

    //QGraphicsItem pacman;
    QPixmap pacman;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);


};


#endif // SPRITES_H
