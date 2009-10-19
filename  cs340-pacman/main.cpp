
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
#include "displayMenu.h"
#include "msgBox.h"
#include "playbutton.h"
#include <QObject>
#include "test.h"



int main(int argc, char *argv[])

{
    QApplication app(argc, argv);
    QGraphicsScene *scene = new QGraphicsScene();
    displayMap *map = new displayMap;
    //map->hide();
    //map->show();

    //DISPLAYING SCREEN(will be transfered to the other class)
    //QGraphicsScene *scene1 = new QGraphicsScene();
    displayMenu *map1 = new displayMenu;

    //msgBox *yoyo = new msgBox;

    //playbutton *button = new playbutton;
    //button->show();

    //QObject:: connect(button,SIGNAL(clicked()),&app,SLOT(quit()));
    //test *tester = new test;

    return app.exec();

    //making a maneger class who will

}
