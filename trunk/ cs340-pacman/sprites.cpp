    #include "sprites.h"


    QRectF sprites::boundingRect() const
    {
        return QRectF();
    }


    void sprites::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
    {

     pacman.load("C:/Users/Sohaib/Desktop/pac.png");
     painter->drawPixmap(0,0,pacman);

    }


