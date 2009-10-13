#include "toplevel.h"
#include <QApplication>
//#include "MyButtons.h"
#include <QSplashScreen>
#include <QtGui>
#include "player.h"
#include "dot.h"
#include "maploader.h"
#include "wall.h"
#include "player.h"
#include "enemy.h"
#include "topbar.h"
#include "dot.h"
#include "bigdot.h"
#include <windows.h>
#include <vector>

TopLevel :: TopLevel()
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    TopBar *stat= new TopBar();
    QPalette p;
    p.setColor(QPalette::Background,Qt::magenta);
    stat->setPalette(p);


    scene->setSceneRect(0,0,550,550);
    scene->setFocus();
    setScene(scene);
    setRenderHint(QPainter::Antialiasing);
    setBackgroundBrush(QColor(0,0,0,255));
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Pac-Man"));

    //Maploader entry point
    MapLoader *mp = new MapLoader;
    mp->FileRead();

    //If there are no characters in the map, send an error message.
    if ((mp->map.isEmpty())) {
        QErrorMessage *msg = new QErrorMessage();
        msg->setModal(true);
        msg->showMessage("List size zero in map. Please check the file.");
    }

        Dot *allDots = new Dot[mp->dotmap.size()];
        Wall *wallblock = new Wall[mp->map.size()];
        BigDot *powerDots = new BigDot[mp->powerdotmap.size()];


     int i =0;
     for(QMap<QString, CoordChar>::const_iterator it = mp->powerdotmap.constBegin(); it != mp->powerdotmap.constEnd(); it++)
    {
         powerDots[i].setPos(it.value().xcoord*WIDTH,it.value().ycoord*HEIGHT);
         scene->addItem(&powerDots[i]);
         i++;
    }


      i =0;
     for(QMap<QString, CoordChar>::const_iterator it = mp->dotmap.constBegin(); it != mp->dotmap.constEnd(); it++)
    {
         allDots[i].setPos(it.value().xcoord*WIDTH,it.value().ycoord*HEIGHT);
         scene->addItem(&allDots[i]);
         i++;
    }

     i=0;
     for(QMap<QString, CoordChar>::const_iterator it = mp->map.constBegin(); it != mp->map.constEnd(); it++)
    {
         wallblock[i].setPos(it.value().xcoord*WIDTH,it.value().ycoord*HEIGHT);
         scene->addItem(&wallblock[i]);
         i++;
    }

     scene->addWidget(stat);
     stat->setGeometry(0,-20,500,30);

}


