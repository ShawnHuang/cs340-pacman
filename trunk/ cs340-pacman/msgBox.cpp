/*-------------------
Name:   Rafe "Ali" Choudhry
Course: CS 340
-------------------*/

#include "msgBox.h"

#include <QtGui>

msgBox::msgBox()
{//start

    displayBox = new QMessageBox;
    //QMessageBox trybox;
    displayBox->setText("Display Map");
    displayBox->exec();


}//end method



