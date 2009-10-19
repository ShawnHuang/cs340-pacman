/*-------------------
Name:   Rafe "Ali" Choudhry
Course: CS 340
-------------------*/

//#include "scenes.h"
#include <QWidget>
#include "scenes.h"
#include <QFont>


scenes :: scenes(QGraphicsScene *scene) : QGraphicsView(scene)
       //:QWidget(parent)
            //: public QGraphicsScene
        //(QWidget *parent)
        //:QWidget(parent)
{//start method



    helpbutton *Help = new helpbutton; //widget that displays Help
    Help->backgroundRole();


    playbutton *Play = new playbutton; //widget that display Play
    //Play->addText("HEYYYY",QFont("Arial",25,QFont::Bold));
    //Play->show();//test

    quitbutton *Quit = new quitbutton;//widget that displays Quit
    //Quit->show();//test

    //QGraphicsScene scene;
    scene->setSceneRect(0,0,600,480);
    scene->setFocus();

    scene->addWidget(Play);
    Play->setGeometry(200,300,200,50);
    scene->addWidget(Help);
    Help->setGeometry(200,350,200,50);
    scene->addWidget(Quit);
    Quit->setGeometry(200,400,200,50);

    //quit_game->setFont(QFont("Arial", 25, QFont::Bold));


    //scene->addText("hey this is pacman");
    //scene->setBackgroundBrush(

    //QGraphicsView view(&scene);
    //view.show();
}//end method


