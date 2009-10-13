#ifndef BIGDOT_H
#define BIGDOT_H
#include <QGraphicsItem>



class BigDot : public QGraphicsItem //Class Wall
{
public:
    BigDot();
    BigDot(int width, int height);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

private:
    QColor colorOfBigDot;
    int WIDTH_OF_BIG_DOT;
    int HEIGHT_OF_BIG_DOT;
};


#endif // BIGDOT_H
