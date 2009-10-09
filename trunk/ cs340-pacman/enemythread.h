//****************************
//   File Name:enemythread.h
//   Created by:Usha Sanaga
//   ***************************

#ifndef ENEMYTHREAD_H
#define ENEMYTHREAD_H

#include <QThread>
#include "maploader.h"
#include "enemy.h"


class EnemyThread : public QThread
{

private:
    MapLoader *ml;
    Enemy *e;
public:
    EnemyThread(MapLoader*,int,int);
    void run();
};

#endif // ENEMYTHREAD_H
