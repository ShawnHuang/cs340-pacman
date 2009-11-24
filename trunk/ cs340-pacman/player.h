#ifndef PLAYER_H
#define PLAYER_H

#include "state.h"
#include "fsm.h"
#include "maploader.h"
#include "dot.h"
#include "bigdot.h"
#include "enemy.h"

#include <QGraphicsItem>
#include <QPainter>
#include <QRectF>
#include <QKeyEvent>
#include <QTimer>
#include <QTimerEvent>
#include <QSound>

#define PACMAN_INIT 0
#define PACMAN_READY 1
#define PACMAN_PLAY 2
#define PACMAN_DYING 3

#define RIGHT_ANIM 0
#define DOWN_ANIM 1
#define UP_ANIM 2
#define LEFT_ANIM 3

class Player: public QGraphicsItem
{
private:
    int xCoord;
    int yCoord;
    int initXCoord;
    int initYCoord;
    int xdir;
    int ydir;
    int xPrev;
    int yPrev;
    int xNext;
    int yNext;

    FSM pacmanfsm;
    void setAndAddStates();
    MapLoader* ml;
    int dir;
    int prevDir;
    int nextDir;
    int mode;
    bool powerdot;
    bool enemyCollision;
    void init();
    int currentAnim;
    int currentFrame;
    bool keySetFlag;

    QString *key;
    QString *key1;
    QString *key2;
    QString *key3;

    QList<QPixmap> pacmanAnim[4];
    int playSound;

    int keyGeneration(int);
    void changeCurrentAnim();
    int step;
    bool isTimeOut;
    void loadAnimations();

public:
    int whichDot;

    Player();
    Player(int ,int, MapLoader*, QGraphicsScene *scene = 0);
    static const int ID_PLAYER = 4;
    virtual int type() const;
    int getDotType();
    void update();
    void advance(int);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    void keyPressEvent(QKeyEvent * event );
    void enterTunnel();
    void colWithOtherItems();
    bool checkCollWithPrevDir();
    void checkCollWithNextDir(bool);
    bool eatenPowerDot();
    QTimer *init_timer;

    enum Action {Up = 1, Down, Left, Right};
    QMap< int, Action > actionmap;

public slots:
     void setTimeOut();

};

#endif // PLAYER_H


