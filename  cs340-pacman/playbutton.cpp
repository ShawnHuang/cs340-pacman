/*-------------------
Name:   Rafe "Ali" Choudhry
Course: CS 340
-------------------*/
#include "playbutton.h"
#include <QtGui>
//#include "displayMenu.h"
//#include "playbutton.h"
playbutton::playbutton(QWidget *parent)
        :QWidget(parent)
{//start

    play_Button = new QPushButton (tr("Play"), this);
    play_Button->setFont(QFont("Lucida Handwriting",18,QFont::Bold));
    play_Button->setFixedHeight(50);
    play_Button->setFixedWidth(200);

//QObject:: connect(play_Button,SIGNAL(clicked()),map11,SLOT(hideMap()));
}//end

/*
void playbutton::hideMap()
{//start method
    //displayMenu

    displayMenu *map111 = new displayMenu;
    map111->hide();

    //QMessageBox trybox;
    //trybox.setText("Display Map");
    //trybox.exec();
}//end method
*/



