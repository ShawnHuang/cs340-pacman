#ifndef PACMAN_H
#define PACMAN_H
#include <QtGui>
#include<QGraphicsScene>
#include<QPainter>
#include<QStyleOption>

#define width 10;
#define height 10;
class Pacman:public QGraphicsItem
{
  public:
    Pacman();
    QRectF boundingRect() const;  //Used for detecting collision between walls,dots, and ghosts
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setState(bool someState);
    void moveXdirection(int newX);
    void moveYdirection(int newY);
    int getX();
    int getY();
    bool checkMove(int newX, int newY);

  private:
    QColor colorOfPacman;
    bool playState;
    bool deadState;
    bool powerfulState;
    int health;
    int x;
    int y;
};
#endif // PACMAN_H
