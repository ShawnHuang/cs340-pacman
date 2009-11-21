#include "ghost.h"


    QRectF ghost::boundingRect() const
    {
        return QRectF();
    }


    void ghost::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
    {

     ghost.load("C:/Users/Sohaib/Desktop/ghost.jpg");
     painter->drawPixmap(0,0,ghost);

    }


