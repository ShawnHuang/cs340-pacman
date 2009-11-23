#include "game.h"
#include "animatedsprites.h"

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

    scene->setSceneRect(0,-35,570,525);
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

     e = new Enemy(1, 4, Character::DIR_DOWN, mp);
     scene->addItem(e);

     e1 = new Enemy(4, 4, Character::DIR_DOWN, mp);
     scene->addItem(e1);

     e2 = new Enemy(10, 10, Character::DIR_DOWN, mp);
     scene->addItem(e2);

     e3 = new Enemy(20, 20, Character::DIR_DOWN, mp);
     scene->addItem(e3);

    QString path = QString("./images/pacman/pacman*.png");
    AnimatedSprites *pacmanSprite = new AnimatedSprites(path);

     //create a pacman object and add it to scene.
     pacman = new Player(270, 290, mp, scene, pacmanSprite->getSpriteList());

     scene->addItem(pacman);
    startTimer( 75 );

}
void Game::setAndAddStates(){
    State gMenu("MENU",GAME_MENU);
    gMenu.addEventAndNextState("menu_timeout","INTRO");

    State gIntro("INTRO",GAME_INIT);
    gIntro.addEventAndNextState("intro_timeout","PLAY");
    //set property here

    State gPlay("PLAY", GAME_PLAY);
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

 void Game::setInitState()
 {
    gamefsm.setInitialState("INTRO");
 }

 void Game::update(){
      if(gamefsm.getStateIndex() == GAME_INIT){
           //display menu screen with buttons
           //if play button clicked, then switch to PLAY state
            //if quit button clicked, exit game

          //toplevelObject->show();

          //toplevelObject->start(100);
           gamefsm.handleEvent("intro_timeout");
        }

       if(gamefsm.getStateIndex()== GAME_PLAY){
            //display map, character and enemies
            //display topbar and initial all values of topbar
           //check if all dots has been eaten
            //advance to next level if necessary
            //increment statbar including lives, score, and current level
            //if enemy kill->200 points for 1st enemy
                             //400 points for 2nd enemy
                             //600 points for 3rd enemy
            //if #oflives remaining is 0, go to OUTRO state
       }
       if(gamefsm.getStateIndex()==GAME_OUTRO){
             //display score and if he/she is winner or loser
            //if any key is pressed, go to INTRO state
       }
      // gamefsm.update();

  }

void Game::timerEvent(QTimerEvent *){
    gamefsm.update();
    update();
    pacman->update();
    e->update();
    e1->update();
    e2->update();
    e3->update();

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
