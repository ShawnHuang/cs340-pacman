#ifndef TOPLEVEL_H
#define TOPLEVEL_H

#include <QtGui/QGraphicsView>
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
//#include <windows.h>
#include <vector>

class TopLevel : public QGraphicsView
{
    Q_OBJECT

    public:
        TopLevel(QGraphicsScene *scene);
        QTimer *timer;
        void start(int);

};


#endif // TOPLEVEL_H
