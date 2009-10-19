/*-------------------
Name:   Rafe Choudhry
Course: CS 340
-------------------*/

#include "displayMap.h"
#include "QGraphicsScene"
displayMap::displayMap(QWidget *parent)
        :QWidget(parent)
{


    TopLevel *display = new TopLevel(&scene);
    display->show();
    display->start(100);
    //display->hide();


    //TopLevel display(scene);
    //display.show();
    //display.start(100);

    //TopLevel *display = new TopLevel(scene);
    //display->show();
    //display->start(100);

}
