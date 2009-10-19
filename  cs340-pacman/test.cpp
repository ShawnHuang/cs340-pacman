
/*-------------------
Name:   Rafe "Ali" Choudhry
Course: CS 340
//-------------------*/

#include "test.h"
#include "playbutton.h"
#include "msgBox.h"
#include <QtGui>
#include <QApplication>
test::test()
{//start

   playbutton *object = new playbutton;

object->show();
QObject:: connect(object,SIGNAL(clicked()),this,SLOT(displayMap()));

}//end


void test::displayMap()
{//start method
    QMessageBox trybox;
    trybox.setText("Display Map");
    trybox.exec();
}//end method




