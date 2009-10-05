#ifndef DOT_H
#define DOT_H


#include <QGraphicsItem>

#define WIDTH_OF_DOT 5
#define HEIGHT_OF_DOT 5

class Dot : public QGraphicsItem //Class Wall
{
public:
    Dot();
    Dot(int width, int height);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

private:
    QColor colorOfDot;
};

#endif // DOT_H
