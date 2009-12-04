#include "topbar.h"

#include <QGraphicsScene>
 #include <QApplication>
 #include <QFont>
 #include <QFrame>
 #include <QGridLayout>
 #include <QLCDNumber>
 #include <QPushButton>
 #include <QSlider>
 #include <QVBoxLayout>
 #include <QWidget>

TopBar::TopBar(QWidget *parent) : QWidget(parent)
{

    QHBoxLayout *hb = new QHBoxLayout;
    levelLabel.setText("Level: ");
    level = new QLCDNumber();
    level->setFrameStyle( QFrame::NoFrame );
    level->setSegmentStyle( QLCDNumber::Flat );
    level->setFixedWidth( 100 );
    hb->addWidget(&levelLabel);
    hb->addWidget(level);
//--------------------------------------------------
    lifeLabel.setText("Lives: ");
    life = new QLCDNumber();
    life->setFrameStyle( QFrame::NoFrame );
    life->setSegmentStyle( QLCDNumber::Flat );
    life->setFixedWidth( 150);
    hb->addWidget(&lifeLabel);
    hb->addWidget(life);
//--------------------------------------------------
    scoreLabel.setText("Score: ");
    score = new QLCDNumber();
    score->setFrameStyle( QFrame::NoFrame );
    score->setSegmentStyle( QLCDNumber::Flat );
    score->setFixedWidth( 150 );
    hb->addWidget(&scoreLabel);
    hb->addWidget(score);
    //hb->addStretch( 10 );
    setLayout(hb);
 }

void TopBar::updateScore(int newScore) {
    score->display(newScore);
}

void TopBar::updateLevel(int newLevel) {
    level->display(newLevel);
}

