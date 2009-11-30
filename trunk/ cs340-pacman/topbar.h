#ifndef TOPBAR_H
#define TOPBAR_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>
#include <QStyleOption>
#include <QLCDNumber>
#include <QLabel>
#include <QPushButton>
#include <QLCDNumber>

static QLCDNumber *score;

class TopBar : public QWidget
{
         Q_OBJECT
public:
    TopBar( QWidget *parent=0);
    //virtual ~TopBar();

    static void updateScore(int);

private:
    QGraphicsScene scene;
    QGraphicsView view;
    void decrementLife();
    void addScorePoint();
    QLabel lifeLabel;
    QLabel scoreLabel;
    QLabel levelLabel;
    QPushButton quitButton;
    QLCDNumber *life;
    QLCDNumber *level;

};



#endif



