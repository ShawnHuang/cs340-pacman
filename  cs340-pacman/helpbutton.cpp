/*-------------------
Name:   Rafe "Ali" Choudhry
Course: CS 340
-------------------*/

#include "helpbutton.h"

helpbutton::helpbutton(QWidget *parent)
        :QWidget(parent)
{//start


    help_Button = new QPushButton (tr("Help"), this);
    help_Button->setFont(QFont("Lucida Handwriting",18,QFont::Bold));

    help_Button->setFixedHeight(50);
    help_Button->setFixedWidth(200);


}//end


