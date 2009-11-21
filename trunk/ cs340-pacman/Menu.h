#ifndef MENU_H
#define MENU_H




#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMessageBox>
#include <QPushButton>
#include "toplevel.h"
#include "sprites.h"
#include <QGraphicsItem>
#include "ghost.h"

class Menu : public QGraphicsView
{
    Q_OBJECT

    public:
    QGraphicsScene *scene;
    Menu(QGraphicsScene *scene);
    //void showHelp(QGraphicsScene *scene);

        QGraphicsScene toplevelScene;;
        QGraphicsScene scene49;


        QPushButton *playButton;
        QPushButton *helpButton;
        QPushButton *quitButton;
        QTimer *timer;
        int counter;
        sprites *object;
        ghost *object1;
        //create a topevel object
        TopLevel *toplevelObject;
    public slots:
        void showMap();
        void showHelp();
    };




#endif // MENU_H
