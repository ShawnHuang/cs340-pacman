/*-------------------
Name:   Rafe "Ali" Choudhry
Course: CS 340
-------------------*/
#include "quitbutton.h"

quitbutton::quitbutton(QWidget *parent)
        :QWidget(parent)
{//start


    quit_Button = new QPushButton (tr("Quit"), this);
    quit_Button->setFont(QFont("Lucida Handwriting",18,QFont::Bold));

    quit_Button->setFixedHeight(50);
    quit_Button->setFixedWidth(200);


}//end



