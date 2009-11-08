#include "bigdot.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

//Constructor defining color of dot

BigDot::BigDot()
{
    colorOfBigDot = QColor(255,255,0,255);
    WIDTH_OF_BIG_DOT=15;
    HEIGHT_OF_BIG_DOT=15;
}


BigDot::BigDot(int width, int height)
{
   WIDTH_OF_BIG_DOT=width;
   HEIGHT_OF_BIG_DOT=height;
}

int BigDot::type() const
{
    return ID_BIGDOT;
}

//Making bouding rect arnd wall which will aid in collision detection
QRectF BigDot::boundingRect() const
{
    return QRectF(-WIDTH_OF_BIG_DOT/2,-HEIGHT_OF_BIG_DOT/2,WIDTH_OF_BIG_DOT,HEIGHT_OF_BIG_DOT);
}

//Drawing a rectangle of dimensions (WIDTH, HEIGHT)
void BigDot::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
   QColor pencolor(0,0,0,255);
   painter->setBrush(colorOfBigDot);
   painter->setPen (pencolor);
   painter->drawEllipse(0,0,WIDTH_OF_BIG_DOT,HEIGHT_OF_BIG_DOT);
}




