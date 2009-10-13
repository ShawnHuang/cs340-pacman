

#ifndef TOPBAR_H
#define TOPBAR_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>
#include <QStyleOption>
#include <QLCDNumber>
#include <QApplication.h>
#include <QLabel>
#include <QPushButton>
#include <QLCDNumber>



class TopBar : public QWidget
{
         Q_OBJECT
public:
    TopBar( QWidget *parent=0);
    //virtual ~TopBar();

private:
    QGraphicsScene scene;
    QGraphicsView view;
    void decrementLife();
    void addScorePoint();
    QLabel lifeLabel;
    QLabel scoreLabel;
    QLabel levelLabel;
    QPushButton quitButton;
    QLCDNumber *score;
    QLCDNumber *life;
    QLCDNumber *level;

};



#endif



