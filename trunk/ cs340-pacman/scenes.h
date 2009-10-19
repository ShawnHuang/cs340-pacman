/*-------------------
Name:   Rafe "Ali" Choudhry
Course: CS 340
-------------------*/
#ifndef SCENES_H
#define SCENES_H




#include <QApplication>
//#include "scene.h"
#include "quitbutton.h"
#include "playbutton.h"
#include "helpbutton.h"
#include <QGraphicsScene>
#include <QGraphicsView>
//#include "enter.h"


class scenes : public QGraphicsView
{
    Q_OBJECT

    public:
        scenes(QGraphicsScene *scene);
        //QTimer *timer;
        //void start(int);

};



#endif // SCENES_H
