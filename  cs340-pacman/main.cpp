/*****************************************************
  File Name: main.cpp
  Description: Creates, loads the scene and add items
  Created by: Riddhi Kapasi
  Modified by:
******************************************************/

#include "wall.h"
#include "maploader.h"
#include "enemy.h"
#include <QtGui>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    QGraphicsScene scene;
    scene.setSceneRect(0,0,550,470);

    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    //Maploader entry point

    MapLoader *mp = new MapLoader;
    mp->FileRead();

    if (mp->map.isEmpty()) {
        QErrorMessage *msg = new QErrorMessage();
        msg->setModal(true);
        msg->showMessage("List size zero in map. Please check the file.");
    }

    Wall *wallblock = new Wall[mp->map.size()]; //Wall w = new Wall[10]

    int i =0;
    for(QMap<QString, CoordChar>::const_iterator it = mp->map.constBegin(); it != mp->map.constEnd(); it++)
    {
         wallblock[i].setPos(it.value().xcoord*WIDTH,it.value().ycoord*HEIGHT);
         scene.addItem(&wallblock[i]);
         i++;
    }

   //create an enemy
//    Enemy *e = new Enemy(1, 1, Character::DIR_DOWN);
//    scene.addItem(e);
//
//    e->moveForward();
//    e->moveForward();
//    e->moveForward();


    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setBackgroundBrush(QColor(0,0,0,255));

    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    //view.setDragMode(QGraphicsView::ScrollHandDrag);

    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Wall Test"));
    //view.resize(400, 300);
    view.show();

    return app.exec();
}
//! [6]
