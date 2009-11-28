#include "game.h"
#include "animatedsprites.h"
#include "loadsound.h"

Game::Game(QGraphicsScene *s) :  QGraphicsView(s)
{
    setRenderHint(QPainter::Antialiasing);
    setBackgroundBrush(QColor(0,0,0,255));
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Pac-Man"));

    setAndAddStates();
    scene = s;
    //toplevelObject = new TopLevel(scene);
    //toplevelObject->hide();

    scene->setSceneRect(0,-35,570,515);
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

    initTimer = new QTimer( this );
    connect(initTimer, SIGNAL(timeout()), this, SLOT(initTimeOut()));

    powerdotTimer = new QTimer( this );
    connect(powerdotTimer, SIGNAL(timeout()), this, SLOT(powerdotTimeOut()));

    isPowerdotTimeOut = true;

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

     e = new Enemy(27, 20, Character::DIR_DOWN, mp);
     scene->addItem(e);

     e1 = new Enemy(24, 24, Character::DIR_DOWN, mp);
     scene->addItem(e1);

     e2 = new Enemy(30, 24, Character::DIR_DOWN, mp);
     scene->addItem(e2);

     e3 = new Enemy(21, 24, Character::DIR_DOWN, mp);
     scene->addItem(e3);

     //create a pacman object and add it to scene.
     pacman = new Player(270, 360, mp, scene);

     isPlay = false;
     timerStarted = false;
     isPacmanDying = false;

     scene->addItem(pacman);
     startTimer( 100 );
}

void Game::initTimeOut()
{
   // qDebug() << "initTimeOut";
    isPlay = true;
}

void Game::setAndAddStates(){
    State gMenu("MENU",GAME_MENU);
    gMenu.addEventAndNextState("menu_timeout","INTRO");

    State gIntro("INTRO",GAME_INIT);
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
//-------------------------------------
 Game::~Game(){
       //delete all pieces on board, including pacman, enemy
       //, fruits, and whatever else is there
   }

 void Game::update(){
      if(gamefsm.getStateIndex() == GAME_INIT){

          if(gamefsm.inENTRY()) // Timmer for init state
          {
            qDebug() << "Timer Started";
            e->show();
            e1->show();
            e2->show();
            e3->show();
            initTimer->start(4500);
            start->play();
            isPlay = false;

          }
          //qDebug() << isPlay;

          if(isPlay)
          {
                //qDebug() << "---isPlay " << isPlay;
                initTimer->stop();
                gamefsm.handleEvent("intro_timeout");
          }
        }

       if(gamefsm.getStateIndex()== GAME_PLAY){
           //qDebug() << "in play state";
            //display map, character and enemies
            //display topbar and initial all values of topbar
           //check if all dots has been eaten
            //advance to next level if necessary
            //increment statbar including lives, score, and current level
            //if enemy kill->200 points for 1st enemy
                             //400 points for 2nd enemy
                             //600 points for 3rd enemy
            //if #oflives remaining is 0, go to OUTRO state
           if(pacman->isEnemyCollided() && isPowerdotTimeOut)
           {
                if(!pacman->eatenPowerDot())
                {
                    isPacmanDying = true;
                    pacman->handleEvent(QString("ghost_hits_pacman"));

                }
                else
                {
                    isPowerdotTimeOut = false;
                    powerdotTimer->start(5000);
                }
           }

       }
       if(gamefsm.getStateIndex()==GAME_OUTRO){
             //display score and if he/she is winner or loser
            //if any key is pressed, go to INTRO state
       }
        gamefsm.update();

  }

 void Game::powerdotTimeOut()
{
    isPowerdotTimeOut = true;
}

void Game::timerEvent(QTimerEvent *){
    scene->advance();
    if(!isPacmanDying)
        update();
    if(isPlay)
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
                gamefsm.handleEvent("callInit");
                isPacmanDying = false;
            }

        }

    }


  // this->start();
}


   /*
   this->setAndAddStates();
   if(this->currState == "INITPLAY"){
       //three second pause before game begins
       //Update points
            }
   if(this->currState == "PLAY"){
        /
    }
}
*/

/*
void Game::dotHit( int size )
{
    switch ( size )
    {
        case 0:
            score += 10;
             break;

        case 1:
            score += 20;
            break;

        default:
            score += 10;
      }
    scoreLCD->display( score );
}

void Game::allDotsRemoved()
{


    if ( level < MAX_LEVELS ){
        level++;
        levelLCD->display( level+1 )

    }
    else
        cout<<"Congradulations, You have won the Game!;

*/

/*
   void Game::init(TopLevel* gameScreen, TopBar* statBar){
       gamefsm.setInitialState("ready");
       statBar->initStat();
        gameScreen= new TopLevel;
        lives = NUMBER_OF_LIVES;
   }
*/
/*
  */
