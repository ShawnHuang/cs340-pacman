/*-------------------
Name:   Rafe "Ali" Choudhry
Course: CS 340
-------------------*/


#ifndef DISPLAYMAP_H
#define DISPLAYMAP_H

#include "toplevel.h"

class displayMap : public QWidget
{//start header file
    Q_OBJECT
public:
    displayMap(QWidget *parent =0);
    //displayMap();
public:
    QGraphicsScene scene;
    //scenes *display1;
    //QPushButton *play_Button;
//public slots:
  //  void displayMap();
};//end header file





#endif // DISPLAYMAP_H
