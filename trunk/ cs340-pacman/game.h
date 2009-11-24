#ifndef GAME_H
#define GAME_H

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

#include "state.h"
#include "fsm.h"

#include  <QTimerEvent>

#define GAME_INIT 0
#define GAME_PLAY 1
#define GAME_OUTRO 2
#define GAME_MENU 3
class Game : public QGraphicsView
{
protected:
    FSM gamefsm;
    int gameOver; //flag that determines this
    int score;
    int level;
    int lives;
    int ghostIsBlue;
    QGraphicsScene *scene;
    //Timer timer;
    Player pac;
    void setScore(TopBar* stats);
    Player *pacman;
    Enemy *e;
    Enemy *e1;
    Enemy *e2;
    Enemy *e3;
    //void resetPosition(TopLevel* viewScreen);
    //void handlePacGhostCol(Enemy* ghost, TopLevel* viewScreen,TopBar stats);

    //void init(TopLevel* gameScreen, TopBar* statBar);
    //TopLevel *toplevelObject;
    QString currState ;
    bool changeState;


public:
    Game(QGraphicsScene *);
    ~Game();
    QTimer *mainTimer;
    QTimer *getReadyTimer;
    void setAndAddStates();
    void incrementStat();
    int remainLives;
    TopBar statBar;
    int isGameOver();       //check if end of game
    virtual void timerEvent( QTimerEvent * );
    void update();

};




#endif // GAME_H
