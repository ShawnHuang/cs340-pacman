
#include <QGraphicsScene>/*****************************************************
  File Name: main.cpp
  Description: Creates, loads the scene and add items
  Created by: Riddhi Kapasi
  Modified by:
******************************************************/

#include <QApplication>
#include <vector>
#include "Menu.h"
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
    display.show();
    QObject:: connect(display.quitButton,SIGNAL(clicked()),&app,SLOT(quit()));
    return app.exec();
}

