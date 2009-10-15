
#include <QGraphicsScene>/*****************************************************
  File Name: main.cpp
  Description: makes the objects of the scene classes and show the scenes
  Created by:  Riddhi Kapasi
  Modified by: Rafe Choudhry
******************************************************/

#include <QApplication>
#include "toplevel.h"
//#include <windows.h>
#include <vector>
#include "scenes.h"
#include "displayMap.h"






int main(int argc, char *argv[])

{
    QApplication app(argc, argv);

    QGraphicsScene *scene = new QGraphicsScene();


    displayMap *map = new displayMap;
    //map->hide();
    //map->show();



    //DISPLAYING SCREEN(will be transfered to the other class)
    QGraphicsScene *scene1 = new QGraphicsScene();
    scenes display1(scene1);
    display1.setBackgroundBrush(QPixmap("C:/Users/Sohaib/Desktop/images/display.gif"));
    display1.resize(640,480);
    display1.show();

    return app.exec();

    //making a maneger class who will

}
