#include "toplevel.h"

TopLevel :: TopLevel(QGraphicsScene *scene) : QGraphicsView(scene)
{
    // set the view properties
    setRenderHint(QPainter::Antialiasing);
    setBackgroundBrush(QColor(0,0,0,255));
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Pac-Man"));

    // set the scene properties

    scene->setSceneRect(0,-35,570,525);
    scene->setFocus();

    // create the scene elements
    QPalette p;
    p.setColor(QPalette::Background,Qt::yellow);

    TopBar *stat= new TopBar();
    stat->setPalette(p);
    stat->setGeometry(0,-35,570,30);
    scene->addWidget(stat);

    //Maploader entry point
    MapLoader *mp = new MapLoader;
    mp->fileRead();


    //If there are no characters in the map, send an error message.
    if ((mp->map.isEmpty())) {
        QErrorMessage *msg = new QErrorMessage();
        msg->setModal(true);
        msg->showMessage("List size zero in map. Please check the file.");
    }

    Dot *allDots = new Dot[mp->dotmap.size()];//try n catch memory allocation exception
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

     //create an enemy
     Enemy *e = new Enemy(1, 4, Character::DIR_DOWN, mp);
     scene->addItem(e);

     Enemy *e1 = new Enemy(4, 4, Character::DIR_DOWN, mp);
     scene->addItem(e1);

     Enemy *e2 = new Enemy(10, 10, Character::DIR_DOWN, mp);
     scene->addItem(e2);

     Enemy *e3 = new Enemy(20, 20, Character::DIR_DOWN, mp);
     scene->addItem(e3);

     Enemy *e4 = new Enemy(40, 40, Character::DIR_DOWN, mp);
     scene->addItem(e4);

     //create a pacman object and add it to scene.
     Player *pacman = new Player(270, 290, mp, scene);
     scene->addItem(pacman);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
}

void TopLevel::start(int msec)
{
    timer->start(msec);
}



