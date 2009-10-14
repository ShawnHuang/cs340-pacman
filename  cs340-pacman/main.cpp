
#include <QGraphicsScene>/*****************************************************
  File Name: main.cpp
  Description: Creates, loads the scene and add items
  Created by: Riddhi Kapasi
  Modified by:
******************************************************/

#include <QApplication>
#include "toplevel.h"
//#include <windows.h>
#include <vector>






int main(int argc, char *argv[])

{
    QApplication app(argc, argv);

    QGraphicsScene *scene = new QGraphicsScene();
    TopLevel display(scene);
    display.show();
    display.start(100);

    return app.exec();

}
