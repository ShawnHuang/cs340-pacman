/*****************************************************
  File Name: main.cpp
  Description: Creates, loads the scene and add items
  Created by: Riddhi Kapasi
  Modified by:
******************************************************/

#include "wall.h"
#include "maploader.h"
#include <QtGui>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    QGraphicsScene scene;
    scene.setSceneRect(0,0,560,500);

    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    //Maploader entry point

    MapLoader *mp = new MapLoader;
    mp->FileRead();

    if (mp->list.size() == 0) {
        QErrorMessage *msg = new QErrorMessage();
        msg->setModal(true);
        msg->showMessage("List size zero in map. Please check the file.");
    }

    Wall *wallblock = new Wall[mp->list.size()]; //Wall w = new Wall[10]

    //Creating block of walls using coordinated from list
    for(int i =0; i < mp->list.size(); i++)
    {
         wallblock[i].setPos(mp->list.at(i).xcoord*WIDTH,mp->list.at(i).ycoord*HEIGHT);
         scene.addItem(&wallblock[i]);
     }

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
