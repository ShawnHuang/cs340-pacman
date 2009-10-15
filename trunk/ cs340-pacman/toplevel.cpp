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
    scene->setSceneRect(0,-5,550,505);
    scene->setFocus();


    // create the scene elements
    QPalette p;
    p.setColor(QPalette::Background,Qt::magenta);

    TopBar *stat= new TopBar();
    stat->setPalette(p);
    stat->setGeometry(0,-5,500,30);

    scene->addWidget(stat);

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

     //create an enemy
     Enemy *e = new Enemy(1,1,Character::DIR_DOWN,mp);
     scene->addItem(e);

     Player *pacman = new Player(0, 0, scene);
     scene->addItem(pacman);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
}

void TopLevel::start(int msec)
{
    timer->start(msec);
}



