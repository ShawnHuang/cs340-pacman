#ifndef PLAYBUTTON_H
#define PLAYBUTTON_H
/*-------------------
Name:   Rafe "Ali" Choudhry
Course: CS 340
-------------------*/
#include<QWidget>
#include <QPushButton>
#include <QLabel>
//#include <QMessageBox>
//#include <QWidget>
//#include "displayMenu.h"


class playbutton : public QWidget
{//start header file
    Q_OBJECT
public:
    playbutton(QWidget *parent =0);

public:
    QPushButton *play_Button;
    //displayMenu *map11;
    //displayMenu *map11; //= new displayMenu;
//public slots:
    //void hideMap();
};//end header file



#endif // PLAYBUTTON_H
