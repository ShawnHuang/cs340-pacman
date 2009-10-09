#include "dot.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

//Constructor defining color of dot

Dot::Dot()
{
    colorOfDot = QColor(255,255,0,255);
    WIDTH_OF_DOT=5;
    HEIGHT_OF_DOT=5;
}


Dot::Dot(int width, int height)
{
   WIDTH_OF_DOT=width;
   HEIGHT_OF_DOT=height;
}


//Making bouding rect arnd wall which will aid in collision detection
QRectF Dot::boundingRect() const
{
    return QRectF(0,0,WIDTH_OF_DOT,WIDTH_OF_DOT);
}

//Drawing a rectangle of dimensions (WIDTH, HEIGHT)
void Dot::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
   QColor pencolor(0,0,0,255);
   painter->setBrush(colorOfDot);
   painter->setPen (pencolor);
   painter->drawEllipse(0,0,WIDTH_OF_DOT,HEIGHT_OF_DOT);
}




