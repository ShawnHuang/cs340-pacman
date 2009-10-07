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
    EnemyThread(MapLoader*);
    void run();
};

#endif // ENEMYTHREAD_H
