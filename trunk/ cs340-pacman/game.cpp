#include "game.h"
#include "loadsound.h"

#include <QPainter>

Game::Game(QGraphicsScene *s) :  QGraphicsView(s)
{
    //setRenderHint(QPainter::Antialiasing);
    setBackgroundBrush(QColor(0,0,0,255));
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

    setOptimizationFlags(QGraphicsView::DontClipPainter
                              | QGraphicsView::DontSavePainterState
                              | QGraphicsView::DontAdjustForAntialiasing);
    setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Pac-Man"));

    setAndAddStates();
    scene = s;
    //toplevelObject = new TopLevel(scene);
    //toplevelObject->hide();

    scene->setSceneRect(0,-35,570,515);
    scene->setFocus();

    level = 0;
    totalScore = 0;

    // create the scene elements
    QPalette p;
    p.setColor(QPalette::Background,Qt::yellow);

    TopBar *stat= new TopBar();
    stat->setPalette(p);
    stat->setGeometry(0,-35,570,30);
    scene->addWidget(stat);

    initMap(level);

    startTimer( 50 );
}

Game::~Game()
   {
   }

void Game::clearScene()
{
    QList<QGraphicsItem*> items = scene->items();
    QList<QGraphicsItem *>::iterator it;

    for (it = items.begin(); it != items.end(); it++ )
    {
        switch((*it)->type()) {
            case ID_WALL:
            case ID_DOT:
            case ID_BIGDOT:
            case Enemy::ID_ENEMY:
            case Player::ID_PLAYER:
                scene->removeItem(*it);
                break;
        }
    }
}

void Game::gameOverClearScene()
{
    QList<QGraphicsItem*> items = scene->items();
    QList<QGraphicsItem *>::iterator it;

    for (it = items.begin(); it != items.end(); it++ )
    {
        switch((*it)->type()) {
            case Enemy::ID_ENEMY:
            case Player::ID_PLAYER:
                scene->removeItem(*it);
                break;
        }
    }
    scene->update(0, 0, 600, 600);
}

void Game::initMap(int level) {

    TopBar::updateLevel(level);
    QString filename("level");
    filename.append(QString::number(level)).append(".txt");

    //Maploader entry point
    mp = new MapLoader;
    mp->fileRead(filename);

    //If there are no characters in the map, send an error message.
    if ((mp->map.isEmpty())) {
        QErrorMessage *msg = new QErrorMessage();
        msg->setModal(true);
        msg->showMessage("List size zero in map. Please check the file.");
    }

    initTimer = new QTimer( this );
    connect(initTimer, SIGNAL(timeout()), this, SLOT(initTimeOut()));

    powerdotTimer = new QTimer( this );
    connect(powerdotTimer, SIGNAL(timeout()), this, SLOT(powerdotTimeOut()));

    isPowerdotTimeOut = true;

    Dot *allDots = new Dot[mp->dotmap.size()];//try n catch memory allocation exception
    Wall *wallblock = new Wall[mp->map.size()];
    BigDot *powerDots = new BigDot[mp->powerdotmap.size()];

    totalScore = mp->dotmap.size() * 10 + mp->powerdotmap.size() * 50;

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

    Enemy::resetEnemyCount();
    e = new Enemy(27, 20, Character::DIR_DOWN, mp);
     scene->addItem(e);

     e1 = new Enemy(24, 24, Character::DIR_DOWN, mp);
     scene->addItem(e1);

     e2 = new Enemy(29, 24, Character::DIR_DOWN, mp);
     scene->addItem(e2);

     e3 = new Enemy(21, 24, Character::DIR_DOWN, mp);
     scene->addItem(e3);

     //create a pacman object and add it to scene.
     pacman = new Player(270, 360, mp, scene);

     isPlay = false;
     timerStarted = false;
     isPacmanDying = false;
     isGameOver = false;

     scene->addItem(pacman);

     lives = NUMBER_OF_LIVES;
     getReadySprite = new QGraphicsPixmapItem( QPixmap("../images/getready.png"), 0, scene);
     getReadySprite->setPos(220, 280);
     getReadySprite->hide();
     gameOverSprite = new QGraphicsPixmapItem( QPixmap("../images/gameover.png"), 0, scene);
     gameOverSprite->setPos(220, 200);
     gameOverSprite->hide();
}

void Game::initTimeOut()
{
    isPlay = true;
}

void Game::setAndAddStates()
{
    State gMenu("MENU",GAME_MENU);
    gMenu.addEventAndNextState("menu_timeout","INTRO");

    State gIntro("INTRO",GAME_INIT);
    gIntro.addEventAndNextState("game_over", "OUTRO");
    gIntro.addEventAndNextState("intro_timeout","PLAY");
    //set property here

    State gPlay("PLAY", GAME_PLAY);
    gPlay.addEventAndNextState("callInit", "INTRO");
    gPlay.addEventAndNextState("game_over", "OUTRO");
    gPlay.addEventAndNextState("press_q", "OUTRO");
    //set property here

    State gOutro("OUTRO", GAME_OUTRO);
    gOutro.addEventAndNextState("outro_timeout", "INTRO");
    //set property here

    gamefsm.addState(gMenu);
    gamefsm.addState(gIntro);
    gamefsm.addState(gPlay);
    gamefsm.addState(gOutro);

    gamefsm.setInitialState("INTRO");
}

 void Game::update()
 {
     switch(gamefsm.getStateIndex())
     {
        case (GAME_INIT):
                      if(gamefsm.inENTRY())
                      {
                        pacman->show();
                        e->show();
                        e1->show();
                        e2->show();
                        e3->show();
                        initTimer->start(4500);
                        start->play();
                        isPlay = false;
                        getReadySprite->show();
                      }

                      if(isPlay && !isGameOver)
                      {
                            initTimer->stop();
                            gamefsm.handleEvent("intro_timeout");
                            getReadySprite->hide();
                      }
         break;

         case(GAME_PLAY):
                 if(pacman->eatenPowerDot())
                   {
                       blueSound.play();
                       isPowerdotTimeOut = false;
                       powerdotTimer->start(10000);
                   }

                   if(pacman->isEnemyCollided())
                   {
                       if(isPowerdotTimeOut)
                       {
                            isPacmanDying = true;
                            lives--;
                            pacman->handleEvent(QString("ghost_hits_pacman"));
                       }
                       else
                       {
                           eatGhost->play();
                       }
                   }
                   TopBar::updateLives(lives);
                   TopBar::updateScore(pacman->getDotScore());
                   TopBar::updateLevel(level);
        break;
        
        case(GAME_OUTRO):

                   if(gamefsm.inENTRY())
                   {
                        gameOverClearScene();
                        gameOverSound->play();
                   }                   
                   gameOverSprite->show();
                   isGameOver = true;
      }
  gamefsm.update();

  }

 void Game::powerdotTimeOut()
{
    isPowerdotTimeOut = true;
}

void Game::timerEvent(QTimerEvent *)
{
    if(!isGameOver)
    {

        if (pacman->getDotScore() == totalScore) {
            clearScene();

            initMap(++level);
            QMessageBox::information(this->nativeParentWidget(), "Congratualtions!!",
                                     "Congratulations, you have finished this level!!", QMessageBox::Ok);

            gamefsm.handleEvent("callInit");
            //pacman->handleEvent("reset");
            gamefsm.update();
            update();
        }
    }

    scene->advance();
    if(!isPacmanDying)
        update();
    if(isPlay && !isGameOver)
    {
        pacman->update();
        if( !isPacmanDying )
        {
            e->update();
            e1->update();
            e2->update();
            e3->update();
        }
        else
        {
            e->hide();
            e1->hide();
            e2->hide();
            e3->hide();
            if(pacman->isPacmanInInit())
            {
                if(lives == 0)
                {
                    pacman->hide();
                    gamefsm.handleEvent("game_over");
                }
                else
                    gamefsm.handleEvent("callInit");
                isPacmanDying = false;
            }
        }
    }
}


