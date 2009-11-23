
#include <QGraphicsScene>/*****************************************************
  File Name: main.cpp
  Description: Creates, loads the scene and add items
  Created by: Riddhi Kapasi
  Modified by:
******************************************************/

#include <QApplication>
#include "toplevel.h"
#include <vector>
#include "Menu.h"
#include "toplevel.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QLabel>
#include <QTimer>

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    QGraphicsScene *scene = new QGraphicsScene();
    Menu display(scene);
    //TopLevel display(scene);
    display.show();
    //display.start(50);

    return app.exec();
}

