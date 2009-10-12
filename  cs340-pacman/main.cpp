
#include <QGraphicsScene>/*****************************************************
  File Name: main.cpp
  Description: Creates, loads the scene and add items
  Created by: Riddhi Kapasi
  Modified by:
******************************************************/

#include <QApplication>
//#include "MyButtons.h"
#include <QSplashScreen>
#include <QtGui>


#include "dot.h"
#include "maploader.h"
#include "wall.h"
#include "character.h"
#include "enemy.h"


static const int EnemyCount = 4;

//#include <windows.h>
#include <vector>


int main(int argc, char *argv[])

{
        QApplication app(argc, argv);

        QGraphicsScene scene;
        scene.setSceneRect(0,0,550,550);


       /**
        //MyButtons *menu = new MyButtons;
        QPixmap pix("C:/Users/Ali/Desktop/pacman.png");
        //make an instance of the splash screen
        QSplashScreen *splash =  new QSplashScreen(pix);
       //Set the splash screen to our picture
        splash->setPixmap(pix);
        //show picture
        splash->show();
        //topRight is the variable used to align the messae
        Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
        //showMessage with desired parameters to acheive a nice message
        splash->showMessage(QObject::tr("Loading Processes..."),topRight,Qt::black);

        app.processEvents();
        Sleep(1000);
**/


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

    int i =0;
     for(QMap<QString, CoordChar>::const_iterator it = mp->dotmap.constBegin(); it != mp->dotmap.constEnd(); it++)
    {
         allDots[i].setPos(it.value().xcoord*WIDTH,it.value().ycoord*HEIGHT);
         scene.addItem(&allDots[i]);
         i++;
    }


    i=0;
     for(QMap<QString, CoordChar>::const_iterator it = mp->map.constBegin(); it != mp->map.constEnd(); it++)
    {
         wallblock[i].setPos(it.value().xcoord*WIDTH,it.value().ycoord*HEIGHT);
         scene.addItem(&wallblock[i]);
         i++;
    }
   //create an enemy

      Enemy *e = new Enemy(1,1,Character::DIR_DOWN, mp);

      scene.addItem(e);
//    e->moveForward();
//    e->makeTurn(1);
//    e->moveForward();
//    e->moveForward();


    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setBackgroundBrush(QColor(0,0,0,255));

    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    //view.setDragMode(QGraphicsView::ScrollHandDrag);

    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Pac-Man"));
    //view.resize(400, 300);
    view.show();
//    EnemyThread *enemyThread = new EnemyThread(mp, 0, 0);


    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
    timer.start(100);


    /**
        //scene->setSceneRect(-300,-300,600,600);
        MyButtons buttons;
        buttons.setGeometry(100,100,500,300);
        QPalette something;
        //something.setColor(Qt::darkBlue);
        buttons.setBackgroundRole(QPalette::Highlight);
        buttons.show();
        QMainWindow window;
        QWidget ql(&window);
        //ql.setPixmap(pix);
        window.setCentralWidget(&ql);
        //ql.show();
       //Sleep(10000);
    //splash->finish(&window);
   //QGraphicsProxyWidget *proxy = scene->addWidget(buttons);
   //menu->show();
//>>>>>>> .r51
        **/

    return app.exec();

}
