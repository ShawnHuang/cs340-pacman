#ifndef DOT_H
#define DOT_H


#include <QGraphicsItem>
#define ID_DOT 1

class Dot : public QGraphicsItem //Class Wall
{
public:
    virtual int type() const;
    Dot();
    Dot(int width, int height);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

private:
    QColor colorOfDot;
    int WIDTH_OF_DOT;
    int HEIGHT_OF_DOT;
};

#endif // DOT_H
