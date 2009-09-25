#include "displayPacman.h"

#include <QtGui/QApplication>
//#include "mainwindow.h"
#include "pacman.h"
#include <QtGui>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;

    QGraphicsScene scene;
    QGraphicsView view(&scene);
    scene.setSceneRect(-300, -300, 600, 600);
    scene.setBackgroundBrush(QColor(0,0,0,255));
    Pacman *pac= new Pacman;

    scene.addItem(pac);
    view.setRenderHint(QPainter::Antialiasing);
    //pac->moveXdirection(30);
    view.show();
    return a.exec();
}
