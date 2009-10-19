#include "displayMenu.h"

#include "QGraphicsScene"
displayMenu::displayMenu(QWidget *parent)
        :QWidget(parent)
{
    //scene1  = new QGraphicsScene;
    //display1 = new scenes(&scene1);
    scenes *display1 = new scenes(&scene1);
    display1->setBackgroundBrush(QPixmap("C:/Users/Sohaib/Desktop/images/display.gif"));
    display1->resize(640,480);
    display1->show();

    //button = new playbutton;

    //QObject:: connect(button,SIGNAL(clicked()),display1,SLOT(hideMenu()));
}

