/*-------------------
Name:   Rafe "Ali" Choudhry
Course: CS 340
-------------------*/

#ifndef DISPLAYMENU_H
#define DISPLAYMENU_H
#include "scenes.h"
#include "playbutton.h"

class displayMenu : public QWidget
{//start header file
    Q_OBJECT
public:
    displayMenu(QWidget *parent =0);
public:
    QGraphicsScene scene1;
    //displayMenu();
//public slots:
    //void hideMenu();

    //playbutton *button;
    //QPushButton *play_Button;
//public slots:
  //  void hideMenu();
};//end header file









#endif // DISPLAYMENU_H
